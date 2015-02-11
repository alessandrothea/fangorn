#include "TSelector.h"
#include "TChain.h"
#include "TTreePlayer.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TVector3.h"
#include "TFile.h"

bool CheckEntry( TTreeReader::EEntryStatus status) {
      if (status == TTreeReader::kEntryValid) {
         return true;
      } else {
         switch (status) {
         case TTreeReader::kEntryValid:
            // Handled above.
            break;
         case TTreeReader::kEntryNotLoaded:
            std::cerr << "Error: TTreeReader has not loaded any data yet!\n";
            break;
         case TTreeReader::kEntryNoTree:
            std::cerr << "Error: TTreeReader cannot find a tree names \"MyTree\"!\n";
            break;
         case TTreeReader::kEntryNotFound:
            // Can't really happen as TTreeReader::Next() knows when to stop.
            std::cerr << "Error: The entry number does not exist\n";
            break;
         case TTreeReader::kEntryChainSetupError:
            std::cerr << "Error: TTreeReader cannot access a chain element, e.g. file without the tree\n";
            break;
         case TTreeReader::kEntryChainFileError:
            std::cerr << "Error: TTreeReader cannot open a chain element, e.g. missing file\n";
            break;
         case TTreeReader::kEntryDictionaryError:
            std::cerr << "Error: TTreeReader cannot find the dictionary for some data\n";
            break;
         }
         return false;
      }
}

void simpleTree( Long64_t entry = -1 ) {
    TFile f("tree3.root");
    TTree* t3 = static_cast<TTree*>(f.Get("t3"));

    TTreeReader reader(t3);

    TTreeReaderValue<Int_t> nTrack(reader, "ntrack");

    std::cout << "Get entries " << reader.GetEntries(true) << std::endl;


    if ( entry == -1)
        reader.Next();
    else 
        reader.SetEntry(entry);


    if ( !CheckEntry(reader.GetEntryStatus()) )
        return;
    else
        std::cout << "Loaded entry " << reader.GetCurrentEntry() << '\n';

    f.Close();


}

void readerTest( Long64_t entry = -1 ) {
    TChain* c = new TChain("t3");
    c->Add("tree3.root");
    c->Add("tree3.root");


    TTreeReader reader(c);
    TTreeReaderValue<Int_t> nTrack(reader, "ntrack");
    // TTreeReaderValue<TVector3> pos(reader, "pos");
    TTreeReaderValue< std::vector<double> > vec(reader, "vec");

    std::cout << "Get entries " << reader.GetEntries(true) << std::endl;

    if ( entry > (reader.GetEntries(false)-1) ) {
        std::cerr << "Error: Requested event is not available: requested=" << entry << "  max=" << reader.GetEntries(false)-1 << std::endl;
        return;
    }

    if ( entry == -1)
        reader.Next();
    else 
        reader.SetEntry(entry);
    
    std::cout << "Entry " << reader.GetCurrentEntry() << ": status " << reader.GetEntryStatus() << std::endl;
      
    if ( !CheckEntry(reader.GetEntryStatus()) )
        return;
    else
        std::cout << "Loaded entry " << reader.GetCurrentEntry() << '\n';

    std::cout << "ntrack status " << nTrack.GetReadStatus() << " value " << *nTrack << std::endl;
    // std::cout << "pos status " << pos.GetReadStatus() << " pointer " << pos.Get() << std::endl;
    std::cout << "vec status " << vec.GetReadStatus() << " size " << vec->size() << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << "----" << std::endl;
    simpleTree(9);
    std::cout << "----" << std::endl;
    readerTest(10);
    std::cout << "----" << std::endl;


    return 0;
}