#ifndef CLAS12_EVENT_HH
#define CLAS12_EVENT_HH

#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TObject.h"

class TDCHit : public TObject {
   public : 
      int      fChannel;    // channel number associated with this hit
      int      fTDC;        // TDC value 
      double   fTime;       // Some Time in ns relative to reference.

      TDCHit() : fChannel(0), fTDC(0), fTime(0.0) { }
      virtual ~TDCHit() { }
      ClassDef(TDCHit,1)
};

class ADCHit : public TObject {
   public : 
      int      fChannel;    // channel number associated with this hit
      int      fADC;        // ADC value 
      double   fCharge;     // Some charge associated with this hit 

      ADCHit() : fChannel(0), fADC(0), fCharge(0.0) { }
      virtual ~ADCHit() { }
      ClassDef(ADCHit,1)
};

class SimpleDriftChamberHit : public TObject {
   public : 
      double          fStepLength;   // Step length used to determine ion pair probabilty
      int             fPDGCode;      // PDG code of particle.
      TLorentzVector  fPosition;      // Location where ion pair was produced position and time 

      SimpleDriftChamberHit() : fStepLength(0.0), fPDGCode(0) { }
      virtual ~SimpleDriftChamberHit() { }
      ClassDef(SimpleDriftChamberHit,1)
};

class DetectorEvent {

   public:

      double                 fRunNumber;     // Run Number
      double                 fEventNumber;   // Event Number

      std::vector<double>    fSimple_Hits;   // some simple hits

      int                    fNTDC_Hits;     // Number of TDC hits, size of fTDC_Hits
      int                    fNADC_Hits;     // Number of ADC hits, size of fADC_Hits
      int                    fNDC_Hits;      // Number of DC hits, size of fDC_Hits

      TClonesArray *         fTDC_Hits;      //-> TDC hit array 
      TClonesArray *         fADC_Hits;      //-> ADC hit array 
      TClonesArray *         fDC_Hits;       //-> Drift Chamber hit array 

      DetectorEvent();
      virtual ~DetectorEvent();

      // These methods simplify adding hits to TClonesArray
      TDCHit * AddTDCHit() {
         TDCHit * aHit = new((*fTDC_Hits)[fNTDC_Hits]) TDCHit();
         fNTDC_Hits++;
         return aHit;
      }
      ADCHit * AddADCHit() {
         ADCHit * aHit = new((*fADC_Hits)[fNADC_Hits]) ADCHit();
         fNADC_Hits++;
         return aHit;
      }
      SimpleDriftChamberHit * AddDCHit() {
         SimpleDriftChamberHit * aHit = new((*fDC_Hits)[fNDC_Hits]) SimpleDriftChamberHit();
         fNDC_Hits++;
         return aHit;
      }

      void Clear(){
         fSimple_Hits.clear();
         fNTDC_Hits = 0;
         fNADC_Hits = 0;
         fNDC_Hits  = 0;      
         fTDC_Hits->Clear();
         fADC_Hits->Clear();
         fDC_Hits->Clear();      
      }


      ClassDef(DetectorEvent,1)
};


#endif

