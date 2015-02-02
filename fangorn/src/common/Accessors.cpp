#include "Accessors.hpp"
#include <iostream>
#include <sstream>

TLeafAccessor::TLeafAccessor( TTree* t, const std::string& name ) :
fLeafName(name) {
    fLeaf = t->GetLeaf(fLeafName.c_str());
}

TLeafAccessor::~TLeafAccessor() {}

void
TLeafAccessor::enable( bool enable ) {
    fLeaf->GetBranch()->SetStatus(enable);
}

const char * 
TLeafAccessor::GetName() const {
    return fLeafName.c_str();
}