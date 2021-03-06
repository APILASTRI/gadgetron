/*
 * FloatToUShortGadget.cpp
 *
 *  Created on: Nov 26, 2011
 *      Author: hansenms
 */

#include "GadgetIsmrmrdReadWrite.h"
#include "FloatToUShortGadget.h"
namespace Gadgetron{
FloatToUShortGadget::FloatToUShortGadget()
{
}



FloatToUShortGadget::~FloatToUShortGadget()
{
}



int FloatToUShortGadget::process(GadgetContainerMessage<ISMRMRD::ImageHeader> *m1, GadgetContainerMessage<hoNDArray<float> > *m2)
{

	GadgetContainerMessage<hoNDArray< ACE_UINT16 > > *cm2 =
			new GadgetContainerMessage<hoNDArray< ACE_UINT16 > >();

	boost::shared_ptr< std::vector<size_t> > dims = m2->getObjectPtr()->get_dimensions();

	try {cm2->getObjectPtr()->create(dims);}
	catch (std::runtime_error &err){
		GEXCEPTION(err,"Unable to create unsigned short storage in Extract Magnitude Gadget");
		return GADGET_FAIL;
	}

	float* src = m2->getObjectPtr()->get_data_ptr();
	ACE_UINT16* dst = cm2->getObjectPtr()->get_data_ptr();

	for (unsigned long i = 0; i < cm2->getObjectPtr()->get_number_of_elements(); i++) {
		float pix_val = src[i];
		switch (m1->getObjectPtr()->image_type) {
		case ISMRMRD::ISMRMRD_IMTYPE_MAGNITUDE:
			pix_val = std::abs(pix_val);
			if (pix_val > 4095) pix_val = 4095;
			break;
		case ISMRMRD::ISMRMRD_IMTYPE_REAL:
		case ISMRMRD::ISMRMRD_IMTYPE_IMAG:
			pix_val = pix_val + 2048;
			if (pix_val < 0) pix_val = 0;
			if (pix_val > 4095) pix_val = 4095;
			break;
		case ISMRMRD::ISMRMRD_IMTYPE_PHASE:
			pix_val *= (float)(2048.0/3.14159265);
			pix_val += 2048;
			if (pix_val < 0) pix_val = 0;
			if (pix_val > 4095) pix_val = 4095;
			break;
		default:
			GDEBUG("Unknown image type %d, bailing out\n",m1->getObjectPtr()->image_type);
			m1->release();
			cm2->release();
			return GADGET_FAIL;
		}
		dst[i] = static_cast<unsigned short>(pix_val);
	}

	m1->cont(cm2);
	m2->release();
	m1->getObjectPtr()->data_type = ISMRMRD::ISMRMRD_USHORT;

	if (this->next()->putq(m1) == -1) {
		m1->release();
		GDEBUG("Unable to put unsigned short magnitude image on next gadgets queue");
		return GADGET_FAIL;
	}


	return GADGET_OK;
}

GADGET_FACTORY_DECLARE(FloatToUShortGadget)
}
