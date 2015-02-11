#include "TSelector.h"
#include "TChain.h"
#include "TTreePlayer.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TVector3.h"

#include <iostream>
/*

Add a list of leaf proxy
Add a list of modules
Modules have a list of leafproxies they use 
Modules request what leaves to read
Keep them there
Update them on Notify
Use them to extract numbers and objects

*/
class AwesomeSelector : public TSelector {
public:
    AwesomeSelector() {}
    ~AwesomeSelector();
    virtual void Init(TTree*);
    virtual Bool_t Notify();
    virtual Bool_t Process(Long64_t entry);
    virtual int Version() const { return 10;};
protected:
private:
    TTreeReader reader_;
    Long64_t processed_;
    TTree* t_;

    // Temp
    TTreeReaderValue<Int_t>* testNTracks_;
    TTreeReaderArray<Float_t>* testPx_;
    TTreeReaderValue<TVector3>* testPos_;
    // List of modules
    // List of leaf proxies
};

AwesomeSelector::~AwesomeSelector() {
    delete testNTracks_;
}

void
AwesomeSelector::Init( TTree* t ) {

    std::cout << "Init awesome" << std::endl;
    reader_.SetTree(t);

    testNTracks_ = new TTreeReaderValue<Int_t>(reader_, "ntrack");
    testPx_ = new TTreeReaderArray<Float_t>(reader_, "px");
    testPos_ = new TTreeReaderValue<TVector3>(reader_, "pos");

   std::cout << "Awesome initialised" << std::endl;

}


bool
AwesomeSelector::Notify() {
    std::cout << "New tree!!" << std::endl;
    return true;
}

Bool_t
AwesomeSelector::Process(Long64_t entry) {
   // Tell the TTreeReader to get the data for
   // the entry number "entry":
   reader_.SetEntry(entry);
   std::cout << "entry " << entry << std::endl;
   std::cout << "ntrack = " << *(*testNTracks_) << std::endl;
   std::cout << "px size = " << (*testPx_).GetSize() << std::endl;
   std::cout << "pos ptr " << testPos_->GetAddress() << " value " << std::endl;
    // << (*testPos_)->x() << "," << (*testPos_)->y() << "," << (*testPos_)->z() << std::endl; 
   fStatus = 9;
   return true;
}  

int main(int argc, char const *argv[])
{

    // gDebug = 5;
    AwesomeSelector* a = new AwesomeSelector();
    std::cout <<  "Awesome status " << a->GetStatus() << std::endl;
    TChain* c = new TChain("t3");
    c->Add("tree3.root");
    // c->Add("tree3.root");
    c->LoadTree(0);

    std::cout <<  "Entries " << c->GetEntries() << std::endl;
    Long64_t s = c->Process(a);
    std::cout <<  "Status " << s << std::endl;
    std::cout <<  "Awesome status " << a->GetStatus() << std::endl;

    delete c;

    return 0;
}