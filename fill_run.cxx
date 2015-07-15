#include "Event.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TTree.h"

int fill_run(int run_number = 1)
{

   TRandom3 rand;
   // Create output file
   TFile * f = new TFile(Form("run%d.root",run_number),"UPDATE");

   // Create the tree
   TTree * t = new TTree("simpleTree","keep it simple");

   // Add the event branch
   DetectorEvent * event = new DetectorEvent();
   t->Branch("aDetectorEvent",&event,32000,2);


   event->fRunNumber = run_number;

   for(int ievent = 0; ievent < 500 ; ievent ++ ) {

      event->Clear();

      event->fEventNumber = ievent;

      int nFill = rand.Integer(10);
      while( nFill != 0 ) {
         event->fSimple_Hits.push_back(rand.PoissonD(4.0));
         nFill--;
      }

      nFill = rand.Integer(10);
      while( nFill != 0 ) {
         TDCHit * aTDC_hit  = event->AddTDCHit();
         aTDC_hit->fChannel = rand.Integer(10);
         aTDC_hit->fTime    = rand.Gaus(0.0,1.0);
         aTDC_hit->fTDC     = 200*aTDC_hit->fTime;
         nFill--;
      }

      nFill = rand.Integer(10);
      while( nFill != 0 ) {
         ADCHit * aADC_hit  = event->AddADCHit();
         aADC_hit->fChannel = rand.Integer(10);
         aADC_hit->fCharge  = rand.Gaus(0.0,1.0);
         aADC_hit->fADC     = 200*aADC_hit->fCharge;
         nFill--;
      }

      nFill = rand.Integer(10);
      while( nFill != 0 ) {
         double x,y,z;
         rand.Sphere(x,y,z,1.0);
         SimpleDriftChamberHit * aDC_hit  = event->AddDCHit();
         aDC_hit->fStepLength = rand.PoissonD(10.0);
         aDC_hit->fPDGCode    = 11;
         aDC_hit->fPosition.SetXYZT(x,y,z, rand.Gaus(3.0,2.0));

         nFill--;
      }

      t->Fill();

   }

   t->Write();

   f->Close();

   return 0;
}
