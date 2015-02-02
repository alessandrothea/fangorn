#ifndef FANGORN_ACCESSORS
#define FANGORN_ACCESSORS


#include "TTree.h"
#include "TLeaf.h"

class TLeafAccessor : public TObject {
public:
    TLeafAccessor( TTree* t, const std::string& name );
    virtual ~TLeafAccessor();

    void enable( bool enable=true);

    virtual const char *GetName() const;

    virtual size_t size() = 0;
protected:
    std::string fLeafName;
    TLeaf* fLeaf;

};


template <typename T, const char *TypeID>
class BaseTypeAccessor : public TLeafAccessor {
public:
    BaseTypeAccessor( TTree* t, const std::string& name );
    virtual ~BaseTypeAccessor();

    const T& operator[](size_t i) const; 

    operator T() const { return fLeaf->GetValue(); }

    virtual size_t size() { return fLeaf->GetLen(); }

};

const char kIntType[] = "Int_t";
const char kFloatType[] = "Float_t";
const char kDoubleType[] = "Double_t";

typedef BaseTypeAccessor<int,kIntType> IntAccessor;
typedef BaseTypeAccessor<float, kFloatType> FloatAccessor;
typedef BaseTypeAccessor<double,kDoubleType> DoubleAccessor;

#include "Accessors.hxx"

#endif
