Keep it Simple : GEANT4, ROOT, and JAVA
=======================================

Introduction
------------

###Don't reinvent wheels.

ROOT is 2 decades old and works great. It is under active development and is 
very well maintained and documented.

Take a look at this event class.

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

          ...

    };

###So what?

Before running the script fill_run.cxx, lets take a look at how 
<code>DetectorEvent</code> is used.

    TFile * f = new TFile(Form("run1.root",run_number),"UPDATE");
    TTree * t = new TTree("simpleTree","keep it simple");

    DetectorEvent * event = new DetectorEvent();
    t->Branch("aDetectorEvent",&event);

    event->fRunNumber = run_number;
 
    for(int ievent = 0; ievent < 500 ; ievent ++ ) {
 
       event->Clear();
       event->fEventNumber = ievent;
       event->fSimple_Hits.push_back(2.1);
       event->fSimple_Hits.push_back(1.8);
 
       TDCHit * aTDC_hit  = event->AddTDCHit();
       aTDC_hit->fChannel = 5;
       aTDC_hit->fTime    = 0.34;
       aTDC_hit->fTDC     = 247;

       ...

       t->Fill();
    }

**That is it!**
All the complication of creating the event structures falls into the classes.  
These are the same objects used in various analyses! 

###Run the example

To run compile and run this example do the following in root:

    .L Event.cxx+
    .L fill_run.cxx+
    fill_run(1)
    .q

This compiles the Event class and fill`_run function, the runs fill`_run.

Looking at the output file in a TBrowser:

![Image of Tree](https://octodex.github.com/images/yaktocat.png)


###Using in Geant4


GEANT4 is also under active development and is well maintained and documented.  
Let's look at [how we can use 
hits](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch04s04.html).
Pretending the [existing concrete sensitive detector 
class](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch04s04.html#sect.Hits.G4VPrim) 
are of no use to us, we implement our own sensitive detector class. One of the 
[http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch04s04.html#sect.Hits.SensDet](user 
hooks for the sensitive detector) is ProcessEvent:

    G4bool MyDetector::ProcessHits(G4Step * step, G4TouchableHistory *history )
    {
       if( StepCreatesIonPair( step->GetStepLength ) ) {
          SimpleDriftChamberHit * ahit   = events->AddDCHit();
          G4TouchableHistory* touchable  = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
          ahit->fChannel  = touchable->GetReplicaNumber(1);
          ahit->fPosition = step->GetPreStepPoint()->GetPosition();
          ahit->fPosition.SetT(step->GetPreStepPoint()->GetGlobalTime());
          ahit->fPDGCode  = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
       }
    }

Super simple!

###What about Evio?

The idea is that the geant4/gemc output can be run through another program 
which generates the appropriate structure for the clas12 reconstruction. This 
program creates all the desired signals from the gemc output. It can be fast 
and crude or slow and detailed. It depends on what your needs are.

Either way, when the banks change, you just need update this program. No need 
to re-run the geant4 simulation part!


###What about Java?

The clas12 reconstruction developers have done a nice job and are making 
significant progress. There is one question that should be seriously thought 
about. 

**Why are we using EVIO for the output?**

If we never actually ran experiments it would seem like a very pointless 
exercise. The only reason we use EVIO is because that is what the DAQ outputs.  
Right? There is nothing special about the EVIO file format. 

Since we are "offline" software, let us ignore how the real data EVIO was 
produced. We only write EVIO to emulate the data structures of the real data so 
we can use the same reconstruction and analysis code.

The wonderful reconstruction software reads in the EVIO file analyzes it and 
then ...  dumps it back into the crude EVIO file format. Womp womp.

It should be accepted by everyone that the physics analysis done by students 
will be done in ROOT.  Coatjava can never replace that. So again... 

**Why are we using EVIO for the output?**

Honestly, is it worth it? Is this a classic case of we have a hammer so 
everything is nail?

###Java to ROOT

It needs to happen...

Here is a small project called 
[javaROOT](https://confluence.slac.stanford.edu/display/ilc/javaROOT).  It 
works and is a nice template for how to use 
[SWIG](http://www.swig.org/Doc1.3/Java.html).

Now we can write classes that can be saved to ROOT files and done in JAVA. 



###Oh, no! I lost the Event class...

Say some time in the future some one wants to read one of these root files. But 
the source files, headers, and libraries were all lost. It is OK. ROOT will 
remember for you.

    TFile * f = new TFile("run1.root","UPDATE");
    f->ls();
    TTree * t = (TTree*)gROOT->FindObject("simpleTree");
    if(t) t->MakeClass("LostEventClass");

This creates the files <code>LostEventClass.C</code> and 
<code>LostEventClass.h</code>. Looking at some of the header we find all the 
data. We did lose our member functions, but all the data is there.  We can do 
the same analysis.

    class LostEventClass {
    public :
       TTree          *fChain;   //!pointer to the analyzed TTree or TChain
       Int_t           fCurrent; //!current Tree number in a TChain
    
    // Fixed size dimensions of array or collections stored in the TTree if any.
       const Int_t kMaxfTDC_Hits = 9;
       const Int_t kMaxfADC_Hits = 9;
       const Int_t kMaxfDC_Hits = 9;
    
       // Declaration of leaf types
     //DetectorEvent   *aDetectorEvent;
       Double_t        fRunNumber;
       Double_t        fEventNumber;
       vector<double>  fSimple_Hits;
       Int_t           fNTDC_Hits;
       Int_t           fNADC_Hits;
       Int_t           fNDC_Hits;
       Int_t           fTDC_Hits_;
       UInt_t          fTDC_Hits_fUniqueID[kMaxfTDC_Hits];   //[fTDC_Hits_]
       UInt_t          fTDC_Hits_fBits[kMaxfTDC_Hits];   //[fTDC_Hits_]
       Int_t           fTDC_Hits_fChannel[kMaxfTDC_Hits];   //[fTDC_Hits_]
       Int_t           fTDC_Hits_fTDC[kMaxfTDC_Hits];   //[fTDC_Hits_]
       Double_t        fTDC_Hits_fTime[kMaxfTDC_Hits];   //[fTDC_Hits_]
       Int_t           fADC_Hits_;
       UInt_t          fADC_Hits_fUniqueID[kMaxfADC_Hits];   //[fADC_Hits_]
       UInt_t          fADC_Hits_fBits[kMaxfADC_Hits];   //[fADC_Hits_]
       Int_t           fADC_Hits_fChannel[kMaxfADC_Hits];   //[fADC_Hits_]
       Int_t           fADC_Hits_fADC[kMaxfADC_Hits];   //[fADC_Hits_]
       Double_t        fADC_Hits_fCharge[kMaxfADC_Hits];   //[fADC_Hits_]
       Int_t           fDC_Hits_;
       UInt_t          fDC_Hits_fUniqueID[kMaxfDC_Hits];   //[fDC_Hits_]
       UInt_t          fDC_Hits_fBits[kMaxfDC_Hits];   //[fDC_Hits_]
       Double_t        fDC_Hits_fStepLength[kMaxfDC_Hits];   //[fDC_Hits_]
       Int_t           fDC_Hits_fPDGCode[kMaxfDC_Hits];   //[fDC_Hits_]
       TLorentzVector  fDC_Hits_fPosition[kMaxfDC_Hits];
       ...
    };

