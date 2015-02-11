#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TLeaf.h"
#include "TVector3.h"

#include <iostream>

class TreeRoller {
public:
    TreeRoller( TTree* t ) : _tree(t) {}
    virtual ~TreeRoller() {}

    void var( const std::string& name, const std::string& vartype = "F", float def=-9999 ) {}
private:
    TTree* _tree;
};


/**
 * Class to hold the buffer branch.
 */
class Proxy
{
public:
    Proxy( TTree* tree, const std::string& name );
    ~Proxy();
    const std::string& type() const { return _typename; }
    void* buffer() { return _buffer; }
private:
    enum ProxyType {
        kSimple,
        kArray,
        kObject
    } ;

    std::string _name;
    std::string _typename;
    char *_buffer;
    ProxyType _type;

};

Proxy::Proxy( TTree* tree, const std::string& name ) :
_name(name),
_buffer(0x0) {

    std::cout << "-ctor--- " << name << std::endl;

    TLeaf* leaf = tree->GetLeaf(name.c_str());
    if ( !leaf ) {
        std::cout << "Leaf " << name << " not found!" << std::endl;
        return;
    }
    _typename = leaf->GetTypeName();

    std::cout << "Leaf type: " << leaf->GetTypeName() << std::endl;


    TBranch* branch = tree->GetBranch(name.c_str());
    std::cout << "Branch type: " << branch->IsA()->GetName() << std::endl;
    

    std::cout << "Proxy " <<  name << " before " << (void*)_buffer << std::endl;

    /*
    Copied from TTree

    In principle the template is not necessary
    TClass can be retrieved from the leaf typename
    Instead the datatype can only be retrieved via typeid.

    */

    std::map<std::string, const std::type_info*> types;

    // Don't forget
    // - C : a character string terminated by the 0 character
    types["Char_t"] = &typeid(Char_t);
    types["UChar_t"] = &typeid(UChar_t);
    types["Short_t"] = &typeid(Short_t);
    types["UShort_t"] = &typeid(UShort_t);
    types["Int_t"] = &typeid(Int_t);
    types["UInt_t"] = &typeid(UInt_t);
    types["Float_t"] = &typeid(Float_t);
    types["Double_t"] = &typeid(Double_t);
    types["Long64_t"] = &typeid(Long64_t);
    types["ULong64_t"] = &typeid(ULong64_t);
    types["Bool_t"] = &typeid(Bool_t);

    /*
    TBranch** ptr = 0x0; // No idea what this is for
    TClass *cl = TClass::GetClass(typeid(T));
    EDataType type = kOther_t;
    if (cl==0) type = TDataType::GetType(typeid(T));
    */

    TBranch** ptr = 0x0; // No idea what this is for
    TClass *cl = TClass::GetClass(_typename.c_str());
    EDataType type = kOther_t;
    if (cl==0) type = TDataType::GetType(*types[_typename]);

    std::cout << "cl = " << cl << "  " << type << std::endl;

    /*
    Detect arrays. Check the array max size using TLeaf methods.
    It requires to run TTree::GetMaximum/Minimum on the leaf that holds the size, for variable arrays
    */

    if ( cl == 0x0 && type != kOther_t ) {
        _type = kSimple;
        // 8 is the size of a double
        _buffer = new char[8];
        tree->SetBranchAddress(name.c_str(),_buffer,ptr,cl,type,true);
    } else if ( cl != 0 ) {
        _type = kObject;
        tree->SetBranchAddress(name.c_str(),&_buffer,ptr,cl,type,true);
    }

    std::cout << "Proxy " << name << " after  " << (void*)_buffer << std::endl;
    // std::cout << "Leaf " << name << "ptr " << leaf->GetValuePointer() << std::endl;

    std::cout << "-------" << std::endl;

}

Proxy::~Proxy()  {
    if ( _buffer ) 
        switch ( _type ) {
            case kSimple:
            case kArray:
                delete [] _buffer; 
                break;
            case kObject:
                delete _buffer;
                break;
            };
}


int main(int argc, char const *argv[])
{

    TChain* c = new TChain("t3");
    c->Add("tree3.root");
    // c->Add("tree3.root");

    //------------------
    // c->Scan("*","");

    //------------------
    // Branching here and there
    Proxy ntraks_b(c, "ntrack");
    Proxy px_b(c, "px");
    Proxy sum_b(c, "sumstat");
    Proxy pos_b(c, "pos");

    std::cout << ntraks_b.type() << std::flush;
    std::cout <<  " " << ntraks_b.buffer() << std::endl;

    
    Long64_t entries = c->GetEntries();
    for ( Long64_t i(0); i < entries; ++i ) {
        std::cout << "--------" << std::endl;
        c->GetEntry(i);
        std::cout << "ntrack ptr " << ntraks_b.buffer() << " value " << *static_cast<int*>(ntraks_b.buffer() ) << std::endl; 
        // std::cout << "px ptr " << px_b.buffer() << " value " << static_cast<float*>(px_b.buffer() )[0] << std::endl; 
        std::cout << "sum ptr " << sum_b.buffer() << " value " << *static_cast<double*>(sum_b.buffer() ) << std::endl; 
        TVector3* pos_o = (static_cast<TVector3*>(pos_b.buffer() ));
        std::cout << "pos ptr " << pos_b.buffer() << " value " << pos_o->x() << "," << pos_o->y() << "," << pos_o->z() << std::endl; 
    }
    
    delete c;
    /* code */
    return 0;
}