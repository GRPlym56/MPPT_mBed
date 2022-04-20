#ifndef _PO_H__
#define _PO_H__

	
#include "PowerTracking.h"
	
class PeturbObserb : public PowerTracking{
		public:
			PeturbObserb();
			void evaluate() override;
			bool powerGood(); //checks power within a set threshold

};


#endif
