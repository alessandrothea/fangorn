#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TLeaf.h"
#include "TVector3.h"
#include "TLorentzVector.h"

void create() {
    const Int_t kMaxTrack = 500;
    Int_t ntrack, mtrack;
    Int_t sign[kMaxTrack];
    Float_t px[kMaxTrack];
    Double_t sumstat;
    TVector3* pos = 0x0;
    std::vector<double> *vec = new std::vector<double>;
    
    TFile f("tree3.root","recreate");
    TTree *t3 = new TTree("t3","Reconst ntuple");
    t3->Branch("ntrack",&ntrack,"ntrack/I");
    t3->Branch("mtrack",&mtrack,"mtrack/I");
    t3->Branch("sign",sign,"sign[ntrack]/I");
    t3->Branch("px",px,"px[ntrack]/F");
    t3->Branch("sumstat",&sumstat,"sumstat/D");
    t3->Branch("pos", &pos);
    t3->Branch("vec", &vec);


    for (Int_t i=0;i<10;++i) {
        vec->clear();
        ntrack = i;
        mtrack = i;
        for ( Int_t j=0; j<i; ++j) {
            sign[j] = ((i+j)%2)*2-1;
            px[j] = i+j;
        }
        sumstat = i/2.;
        pos->SetXYZ(i,i+1,i+2);
        vec->push_back(i);
        t3->Fill();

    }
    t3->Write();
    f.Close();
}




int main(int argc, char const *argv[])
{
    create();
    /* code */
    return 0;
}