#include "Gadget.h"
#include "GadgetReference.h"
#include "GadgetContainerMessage.h"
#include "hoNDArray.h"
#include "ismrmrd/ismrmrd.h"
#include <boost/preprocessor/stringize.hpp>
#include <boost/python.hpp>
#include <numpy/numpyconfig.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/ndarrayobject.h>

#include <complex>

namespace Gadgetron{

  GadgetReference::GadgetReference()
    : gadget_(0)
  {
    //_import_array();
  }

  GadgetReference::~GadgetReference()
  {

  }

  template<class T>
  int GadgetReference::return_data(T header, boost::python::object arr)
  {

    PyArrayObject* arrPtr = PyArray_GETCONTIGUOUS((PyArrayObject*)arr.ptr());//PyArray_FromObject(arr.ptr(),NPY_COMPLEX64,1,5); //So.... this is probably really really really bad.
    int ndims = PyArray_NDIM(arrPtr);
    npy_intp* dims = PyArray_DIMS(arrPtr);
    std::vector<size_t> dimensions(ndims);
    for (int i = 0; i < ndims; i++) dimensions[ndims-i-1] = static_cast<unsigned int>(dims[i]);

    GadgetContainerMessage< T >*         m1 = new GadgetContainerMessage< T >;
    memcpy(m1->getObjectPtr(), &header, sizeof(T));

    GadgetContainerMessage< hoNDArray< std::complex<float> > >* m2 = new GadgetContainerMessage< hoNDArray< std::complex<float> > >;
    m1->cont(m2);

    try{m2->getObjectPtr()->create(&dimensions);}
    catch (std::runtime_error &err){
      GEXCEPTION(err,"Failed to create data storage for data returning from Python");
      return GADGET_FAIL;
    
    }

    memcpy(m2->getObjectPtr()->get_data_ptr(), PyArray_DATA(arrPtr), m2->getObjectPtr()->get_number_of_elements()*sizeof(std::complex<float>));

    if (gadget_) {
      //ACE_Time_Value wait = ACE_OS::gettimeofday() + ACE_Time_Value(0,1000); //1ms from now
      ACE_Time_Value nowait (ACE_OS::gettimeofday ());
      //GDEBUG("Returning data (%s)\n", gadget_->module()->name());
      if (gadget_->next()->putq(m1,&nowait) == -1) {
	m1->release();
	//if (gadget_->next()->putq(m1) == -1) {
	/*
	  GDEBUG("Putting message on Queue failed (%s)\n", gadget_->module()->name());
	  GDEBUG("Message Q: low mark %d, high mark %d, message bytes %d, message count %d\n",
	  gadget_->next()->msg_queue()->low_water_mark(), gadget_->next()->msg_queue()->high_water_mark(),
	  gadget_->next()->msg_queue()->message_bytes(),gadget_->next()->msg_queue()->message_count());
	*/
	//GDEBUG("FAIL Returning data (%s)\n", gadget_->module()->name());
	return GADGET_FAIL;
      } else {
	//GDEBUG("SUCCESS Returning data (%s)\n", gadget_->module()->name());

	return GADGET_OK;
      }
      //return gadget_->next()->putq(m1);
    } else {
      GDEBUG("Data received from python, but no Gadget registered for output\n");
      m1->release();
      return GADGET_OK;
    }

    return GADGET_OK;

  }

  int GadgetReference::return_acquisition(ISMRMRD::AcquisitionHeader acq, boost::python::object arr)
  {
    return return_data<ISMRMRD::AcquisitionHeader>(acq, arr);
  }

  int GadgetReference::return_image(ISMRMRD::ImageHeader img, boost::python::object arr)
  {
    return return_data<ISMRMRD::ImageHeader>(img, arr);
  }

  template int GadgetReference::return_data<ISMRMRD::AcquisitionHeader>(ISMRMRD::AcquisitionHeader, boost::python::object);
  template int GadgetReference::return_data<ISMRMRD::ImageHeader>(ISMRMRD::ImageHeader, boost::python::object);
}
