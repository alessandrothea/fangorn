#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include <iostream>
#include <sstream>


class TLeafAccessor {
public:
    TLeafAccessor( TTree* t, const std::string& name );
    virtual ~TLeafAccessor() {}
protected:
    TLeaf* fLeaf;

};

TLeafAccessor::TLeafAccessor( TTree* t, const std::string& name ) {
    fLeaf = t->GetLeaf(name.c_str());
}


template <typename T, const char *TypeID>
class BaseTypeAccessor : public TLeafAccessor {
public:
    BaseTypeAccessor( TTree* t, const std::string& name );
    virtual ~BaseTypeAccessor() {}

    const T& operator[](size_t i) const; 

    operator T() const { return fLeaf->GetValue(); }

    size_t size() { return fLeaf->GetLen(); }

};


template <typename T, const char *TypeID>
BaseTypeAccessor<T,TypeID>::BaseTypeAccessor( TTree* t, const std::string& name) :
TLeafAccessor(t,name) {

    // Let's have a look inside
    std::cout << "Name: " << fLeaf->GetName() << std::endl;
    std::cout << "Type: " << fLeaf->GetTypeName() << std::endl;
    std::cout << "Size: " << fLeaf->GetLen() << std::endl;
    std::cout << "Ptr: " << fLeaf->GetValuePointer() << std::endl;

    if ( strcmp (fLeaf->GetTypeName(),TypeID) != 0 ) {
        std::ostringstream oss;
        oss << "Type != " << TypeID << " (type found " << fLeaf->GetTypeName() << ")";
        throw std::runtime_error(oss.str());
    }
}

template <typename T, const char *TypeID>
const T&
BaseTypeAccessor<T,TypeID>::operator[](size_t i) const {
    T* array = static_cast<T*>(fLeaf->GetValuePointer());

    // Add boundary check here
    return array[i];
}


const char kFloatType[] = "Float_t";
const char kIntType[] = "Int_t";
const char kDoubleType[] = "Double_t";

typedef BaseTypeAccessor<int,kIntType> IntAccessor;
typedef BaseTypeAccessor<float, kFloatType> FloatAccessor;
typedef BaseTypeAccessor<double,kDoubleType> DoubleAccessor;

// class FloatAccessor : public TLeafAccessor {
// public:
//     FloatAccessor( TTree* t, const std::string& name );
//     virtual ~FloatAccessor() {}

//     const float& operator[](size_t i) const; 

//     size_t size() { return fLeaf->GetLen(); }

// };




// FloatAccessor::FloatAccessor( TTree* t, const std::string& name) :
// TLeafAccessor(t,name) {

//     // Let's have a look inside
//     std::cout << "Name: " << fLeaf->GetName() << std::endl;
//     std::cout << "Type: " << fLeaf->GetTypeName() << std::endl;
//     std::cout << "Size: " << fLeaf->GetLen() << std::endl;
//     std::cout << "Ptr: " << fLeaf->GetValuePointer() << std::endl;

//     if ( strcmp (fLeaf->GetTypeName(),"Float_t") != 0 ) {
//         std::ostringstream oss;
//         oss << "Type != Float_t (type found " << fLeaf->GetTypeName() << ")";
//         throw std::runtime_error(oss.str());
//     }
// }

// const float&
// FloatAccessor::operator[](size_t i) const {
//     float* array = static_cast<float*>(fLeaf->GetValuePointer());

//     return array[i];
// }



int main(int argc, char const *argv[])
{
    
    TFile f("/Users/ale/Development/ttree/treesTTBar_DM600_v2.root");

    TTree* t = static_cast<TTree*>( f.Get("DMTreesDumper/ttDM600__noSyst") );

    std::cout << "TTree " << t << std::endl;


    t->Scan("jetE:elE:Iteration$","","",1);


    t->GetEntry(0);
    FloatAccessor jetE(t,"jetE");
    IntAccessor jetsSize(t,"jets_size");

    for ( size_t i(0); i<jetsSize; ++i) {
        std::cout << i << " " << jetE[i] << std::endl;
    }


    return 0;


}