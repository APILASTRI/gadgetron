#include "PythonCommunicator.h"
#include "../mri_core/GadgetMRIHeaders.h"
#include "gadgetron_paths.h"
#include "gadgetron_config.h"

#include <numpy/numpyconfig.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <boost/algorithm/string.hpp>
#include <ismrmrd/ismrmrd.h>

namespace Gadgetron{
PythonCommunicator::PythonCommunicator()
{
	Py_Initialize();
	_import_array();

	PyEval_InitThreads();

	//Swap out and return current thread state and release the GIL
	//Must be done, otherwise subsequent calls to PyGILState_Ensure() will not be guaranteed to acuire lock
	PyThreadState* tstate = PyEval_SaveThread();
	if (!tstate) {
		GDEBUG("Error occurred returning lock to Python\n");
	}


	//Let's first get the path set for the library folder
	std::string  gadgetron_home = get_gadgetron_home();
	std::string path_name = gadgetron_home + std::string("/") + std::string(GADGETRON_PYTHON_PATH);

	if (gadgetron_home.size() != 0) {
		if (addPath(path_name) == GADGET_FAIL) {
			GDEBUG("PythonCommunicator (constructor) failed to add path %s\n", path_name.c_str());
		}
	}

}

PythonCommunicator::~PythonCommunicator()
{

}

int PythonCommunicator::addPath(std::string path)
{

	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();

	std::string path_cmd;
	if (path.size() > 0) {
		std::vector<std::string> paths;
		boost::split(paths, path, boost::is_any_of(";"));
		for (unsigned int i = 0; i < paths.size(); i++) {
			path_cmd = std::string("import sys;\nif (sys.path.count(\"") + paths[i] +
					std::string("\") == 0):\n\tsys.path.append(\"") + paths[i] + std::string("\")\n");
			//GDEBUG("Executing path command:\n%s\n", path_cmd.c_str());
			boost::python::exec(path_cmd.c_str(),boost::python::import("__main__").attr("__dict__"));
		}
	}

	PyGILState_Release(gstate);
	return GADGET_OK;
}

int PythonCommunicator::registerGadget(Gadget* g, std::string mod, 
		std::string ref, std::string conf,
		std::string process)
{

	PyGILState_STATE gstate;

	if (!g) {
		GDEBUG("PythonCommunicator::registerGadget: Received null gadget\n");
		return GADGET_FAIL;
	}

	gstate = PyGILState_Ensure();
	try {

		if (mod.size() != 0) {
			module_[g] = boost::python::import(mod.c_str());

			/* We will try t force a reload of the module */
			boost::python::import("__main__").attr("__dict__")[mod.c_str()] = module_[g];
			std::string tmp = std::string("reload(") + std::string(mod.c_str()) + std::string(")\n");

			//GDEBUG("Reloading with command: %s\n", tmp.c_str());
			boost::python::exec(tmp.c_str(),boost::python::import("__main__").attr("__dict__"));

		} else {
			PyGILState_Release(gstate);
			GDEBUG("PythonCommunicator::registerGadget: Null module received\n");
			return GADGET_FAIL;
		}

		if (ref.size() != 0) {
			gadget_ref_fnc_[g]  = module_[g].attr(ref.c_str());
			gadget_ref_[g] = boost::shared_ptr<GadgetReference>(new GadgetReference());
			gadget_ref_[g]->set_gadget(g);
			gadget_ref_fnc_[g](*gadget_ref_[g].get());
		}

		if (conf.size() != 0) {
			config_fnc_[g] =  module_[g].attr(conf.c_str());
		}

		if (process.size() != 0) {
			process_fnc_[g] = module_[g].attr(process.c_str());
		}

	} catch(boost::python::error_already_set const &) {
		GDEBUG("Error loading python modules\n");
		PyErr_Print();
		PyGILState_Release(gstate);
		return GADGET_FAIL;
	}
	PyGILState_Release(gstate);

	return GADGET_OK;
}

int PythonCommunicator::processConfig(Gadget* g, ACE_Message_Block* mb)
{
	PyGILState_STATE gstate;
	std::map< Gadget*, boost::python::object >::iterator it;

	if (!g) {
		GDEBUG("Null Gadget received");
		return GADGET_FAIL;
	}

	it = config_fnc_.find(g);
	if (it != config_fnc_.end()) {
		gstate = PyGILState_Ensure();
		try {
			boost::python::object ignored = it->second(boost::python::object(std::string(mb->rd_ptr())));
		}  catch(boost::python::error_already_set const &) {
			GDEBUG("Error calling process config function for Gadget %s\n", g->module()->name());
			PyErr_Print();
			PyGILState_Release(gstate);
			return GADGET_FAIL;
		}
		PyGILState_Release(gstate);
	} else {
		GDEBUG("No registered process function found for Gadget %s\n", g->module()->name());
		return GADGET_FAIL;
	}

	return GADGET_OK;
}

template<class T> int PythonCommunicator::process(Gadget* g, 
		GadgetContainerMessage<T>* m1,
		GadgetContainerMessage< hoNDArray< std::complex<float> > >* m2)
{

	PyGILState_STATE gstate;

	std::map< Gadget*, boost::python::object >::iterator it;

	if (!g) {
		GDEBUG("Null Gadget received");
		return GADGET_FAIL;
	}


	it = process_fnc_.find(g);
	if (it != process_fnc_.end()) {
                mutex_.lock();
		gstate = PyGILState_Ensure();
		try {
			std::vector<size_t> dims = (*(m2->getObjectPtr()->get_dimensions().get()));
			std::vector<int> dims2(dims.size());
			for (unsigned int i = 0; i < dims.size(); i++) dims2[dims.size()-i-1] = static_cast<int>(dims[i]);

			boost::python::object obj(boost::python::handle<>(PyArray_FromDims(dims2.size(), &dims2[0], NPY_COMPLEX64)));
			//boost::python::object data = boost::python::extract<boost::python::numeric::array>(obj);

			//Copy data
			memcpy(PyArray_DATA((PyArrayObject*)obj.ptr()), m2->getObjectPtr()->get_data_ptr(), m2->getObjectPtr()->get_number_of_elements()*sizeof(std::complex<float>));

			//Get Header
			T acq = *m1->getObjectPtr();

			if ( boost::python::extract<int>(it->second(acq, obj)) != GADGET_OK) {
				GDEBUG("Gadget (%s) Returned from python call with error\n", g->module()->name());
				PyGILState_Release(gstate);
				return GADGET_FAIL;
			}
			//Else we are done with this now.
			m1->release();
		} catch(boost::python::error_already_set const &) {
			GDEBUG("Passing data on to python module failed\n");
			PyErr_Print();
                        mutex_.unlock();
			PyGILState_Release(gstate);
			return GADGET_FAIL;
		}
		PyGILState_Release(gstate);
                mutex_.unlock();
	} else {
		GDEBUG("No registered process function found for Gadget %s\n", g->module()->name());
		return GADGET_FAIL;
	}
	return GADGET_OK;
}  


//Template Instanciations
template int PythonCommunicator::process(Gadget*, GadgetContainerMessage<ISMRMRD::AcquisitionHeader>*,
		GadgetContainerMessage< hoNDArray< std::complex<float> > >*);

template int PythonCommunicator::process(Gadget*, GadgetContainerMessage<ISMRMRD::ImageHeader>*,
		GadgetContainerMessage< hoNDArray< std::complex<float> > >*);
}
