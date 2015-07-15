Keep it Simple : GEANT4, ROOT, and JAVA
=======================================

Introduction
------------

Rule 1. Don't reinvent wheels.

ROOT is 2 decades old and works great. It is under active development and is 
very well maintained. 

Take a look at the event class.

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

**So what?**

Well, this how it is used.

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
 




Oh, no! I lost the Event class...
---------------------------------

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
    
       // List of branches
       TBranch        *b_aDetectorEvent_fRunNumber;   //!
       TBranch        *b_aDetectorEvent_fEventNumber;   //!
       TBranch        *b_aDetectorEvent_fSimple_Hits;   //!
       TBranch        *b_aDetectorEvent_fNTDC_Hits;   //!
       TBranch        *b_aDetectorEvent_fNADC_Hits;   //!
       TBranch        *b_aDetectorEvent_fNDC_Hits;   //!
       TBranch        *b_aDetectorEvent_fTDC_Hits_;   //!
       TBranch        *b_fTDC_Hits_fUniqueID;   //!
       TBranch        *b_fTDC_Hits_fBits;   //!
       TBranch        *b_fTDC_Hits_fChannel;   //!
       TBranch        *b_fTDC_Hits_fTDC;   //!
       TBranch        *b_fTDC_Hits_fTime;   //!
       TBranch        *b_aDetectorEvent_fADC_Hits_;   //!
       TBranch        *b_fADC_Hits_fUniqueID;   //!
       TBranch        *b_fADC_Hits_fBits;   //!
       TBranch        *b_fADC_Hits_fChannel;   //!
       TBranch        *b_fADC_Hits_fADC;   //!
       TBranch        *b_fADC_Hits_fCharge;   //!
       TBranch        *b_aDetectorEvent_fDC_Hits_;   //!
       TBranch        *b_fDC_Hits_fUniqueID;   //!
       TBranch        *b_fDC_Hits_fBits;   //!
       TBranch        *b_fDC_Hits_fStepLength;   //!
       TBranch        *b_fDC_Hits_fPDGCode;   //!
       TBranch        *b_fDC_Hits_fPosition;   //!
    
       LostEventClass(TTree *tree=0);
       virtual ~LostEventClass();
       virtual Int_t    Cut(Long64_t entry);
       virtual Int_t    GetEntry(Long64_t entry);
       virtual Long64_t LoadTree(Long64_t entry);
       virtual void     Init(TTree *tree);
       virtual void     Loop();
       virtual Bool_t   Notify();
       virtual void     Show(Long64_t entry = -1);
    };

