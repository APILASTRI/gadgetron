#pragma once

#include "Gadget.h"
#include "hoNDArray.h"
#include "GadgetContainerMessage.h"
#include "GadgetReference.h"
#include "gadgetronpython_export.h"

#include <ace/Singleton.h>
#include <ace/Synch.h>

#include <boost/thread/mutex.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <complex>

namespace Gadgetron{

class EXPORTGADGETSPYTHON PythonCommunicator
{

 public:
  PythonCommunicator();
  ~PythonCommunicator();

  int addPath(std::string path);

  int registerGadget(Gadget* g, std::string mod, 
		     std::string ref, std::string conf,
		     std::string process);

  int processConfig(Gadget* g, ACE_Message_Block* mb);

  template<class T> int process(Gadget* g, 
				GadgetContainerMessage<T>* m1,
				GadgetContainerMessage< hoNDArray< std::complex<float> > >* m2);

    boost::mutex mutex_;

 private:
  std::map<Gadget*, boost::python::object> module_;
  std::map<Gadget*, boost::python::object> gadget_ref_fnc_;
  std::map<Gadget*, boost::python::object> config_fnc_;
  std::map<Gadget*, boost::python::object> process_fnc_;
  std::map<Gadget*, boost::shared_ptr<GadgetReference> > gadget_ref_;

};

typedef ACE_Singleton<PythonCommunicator, ACE_Thread_Mutex> PythonCommunicatorSingleton;
}
