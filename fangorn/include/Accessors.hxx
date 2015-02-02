#include <iostream>
#include <sstream>

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
BaseTypeAccessor<T,TypeID>::~BaseTypeAccessor() {
}

template <typename T, const char *TypeID>
const T&
BaseTypeAccessor<T,TypeID>::operator[](size_t i) const {
    T* array = static_cast<T*>(fLeaf->GetValuePointer());

    // Add boundary check here
    return array[i];
}