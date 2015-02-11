#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "Accessors.hpp"
#include <iostream>
#include <sstream>

/*
Warning: This example doesn't work for with TChains
*/

int main(int argc, char const *argv[])
{
    // TChain c("DMTreesDumper/ttDM600__noSyst");
    // c.Add("/Users/ale/Development/ttree/treesTTBar_DM600_v2_A.root");
    // c.Add("/Users/ale/Development/ttree/treesTTBar_DM600_v2_B.root");
    TFile f("/Users/ale/Development/ttree/treesTTBar_DM600_v2.root");

    TTree* t = static_cast<TTree*>( f.Get("DMTreesDumper/ttDM600__noSyst") );
    // TTree* t= &c;
    std::cout << "TTree " << t << std::endl;


    t->Scan("jetE:elE:Iteration$","","",1);

    std::cout << "Entries: " << t->GetEntries() << std::endl;

    FloatAccessor jetE(t,"jetE");
    IntAccessor jetsSize(t,"jets_size");

    for ( Long64_t e = 0; e<t->GetEntriesFast(); ++e) {
        t->GetEntry(e);
        for ( size_t i(0); i<jetsSize; ++i) {
            if ( e == 0 )
                std::cout << i << " " << jetE[i] << std::endl;
        }
    }
    std::cout << "First Loop done" << std::endl;

    t->SetBranchStatus("*", false);

    jetE.enable();
    jetsSize.enable();

    for ( Long64_t e = 0; e<t->GetEntriesFast(); ++e) {
        t->GetEntry(e);
        for ( size_t i(0); i<jetsSize; ++i) {
            if ( e == 0 )
                std::cout << i << " " << jetE[i] << std::endl;
        }
    }

    std::cout << "Second Loop done" << std::endl;

    return 0;


}