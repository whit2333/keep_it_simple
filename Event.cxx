#include "Event.h"

//___________________________________________________________________

DetectorEvent::DetectorEvent() : fRunNumber(0), fEventNumber(0), 
   fSimple_Hits(10), fNTDC_Hits(0), fNADC_Hits(0), fNDC_Hits(0),
   fTDC_Hits(0), fADC_Hits(0), fDC_Hits(0)
{
   fTDC_Hits = new TClonesArray("TDCHit"               ,10);
   fADC_Hits = new TClonesArray("ADCHit"               ,10);
   fDC_Hits  = new TClonesArray("SimpleDriftChamberHit",10);
}
//___________________________________________________________________

DetectorEvent::~DetectorEvent() {
   delete fTDC_Hits;
   delete fADC_Hits;
   delete fDC_Hits;
}
//___________________________________________________________________


