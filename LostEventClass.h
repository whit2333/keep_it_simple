//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 15 00:10:01 2015 by ROOT version 6.04/00
// from TTree simpleTree/keep it simple
// found on file: run2.root
//////////////////////////////////////////////////////////

#ifndef LostEventClass_h
#define LostEventClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"

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

#endif

#ifdef LostEventClass_cxx
LostEventClass::LostEventClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run2.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("run2.root");
      }
      f->GetObject("simpleTree",tree);

   }
   Init(tree);
}

LostEventClass::~LostEventClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t LostEventClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t LostEventClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void LostEventClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fRunNumber", &fRunNumber, &b_aDetectorEvent_fRunNumber);
   fChain->SetBranchAddress("fEventNumber", &fEventNumber, &b_aDetectorEvent_fEventNumber);
   fChain->SetBranchAddress("fSimple_Hits", &fSimple_Hits, &b_aDetectorEvent_fSimple_Hits);
   fChain->SetBranchAddress("fNTDC_Hits", &fNTDC_Hits, &b_aDetectorEvent_fNTDC_Hits);
   fChain->SetBranchAddress("fNADC_Hits", &fNADC_Hits, &b_aDetectorEvent_fNADC_Hits);
   fChain->SetBranchAddress("fNDC_Hits", &fNDC_Hits, &b_aDetectorEvent_fNDC_Hits);
   fChain->SetBranchAddress("fTDC_Hits", &fTDC_Hits_, &b_aDetectorEvent_fTDC_Hits_);
   fChain->SetBranchAddress("fTDC_Hits.fUniqueID", fTDC_Hits_fUniqueID, &b_fTDC_Hits_fUniqueID);
   fChain->SetBranchAddress("fTDC_Hits.fBits", fTDC_Hits_fBits, &b_fTDC_Hits_fBits);
   fChain->SetBranchAddress("fTDC_Hits.fChannel", fTDC_Hits_fChannel, &b_fTDC_Hits_fChannel);
   fChain->SetBranchAddress("fTDC_Hits.fTDC", fTDC_Hits_fTDC, &b_fTDC_Hits_fTDC);
   fChain->SetBranchAddress("fTDC_Hits.fTime", fTDC_Hits_fTime, &b_fTDC_Hits_fTime);
   fChain->SetBranchAddress("fADC_Hits", &fADC_Hits_, &b_aDetectorEvent_fADC_Hits_);
   fChain->SetBranchAddress("fADC_Hits.fUniqueID", fADC_Hits_fUniqueID, &b_fADC_Hits_fUniqueID);
   fChain->SetBranchAddress("fADC_Hits.fBits", fADC_Hits_fBits, &b_fADC_Hits_fBits);
   fChain->SetBranchAddress("fADC_Hits.fChannel", fADC_Hits_fChannel, &b_fADC_Hits_fChannel);
   fChain->SetBranchAddress("fADC_Hits.fADC", fADC_Hits_fADC, &b_fADC_Hits_fADC);
   fChain->SetBranchAddress("fADC_Hits.fCharge", fADC_Hits_fCharge, &b_fADC_Hits_fCharge);
   fChain->SetBranchAddress("fDC_Hits", &fDC_Hits_, &b_aDetectorEvent_fDC_Hits_);
   fChain->SetBranchAddress("fDC_Hits.fUniqueID", fDC_Hits_fUniqueID, &b_fDC_Hits_fUniqueID);
   fChain->SetBranchAddress("fDC_Hits.fBits", fDC_Hits_fBits, &b_fDC_Hits_fBits);
   fChain->SetBranchAddress("fDC_Hits.fStepLength", fDC_Hits_fStepLength, &b_fDC_Hits_fStepLength);
   fChain->SetBranchAddress("fDC_Hits.fPDGCode", fDC_Hits_fPDGCode, &b_fDC_Hits_fPDGCode);
   fChain->SetBranchAddress("fDC_Hits.fPosition", fDC_Hits_fPosition, &b_fDC_Hits_fPosition);
   Notify();
}

Bool_t LostEventClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void LostEventClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t LostEventClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef LostEventClass_cxx
