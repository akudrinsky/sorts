#include "../include/abstractObjects.hpp"
#include <stdexcept>

using namespace kudry; // correct when implementing my own library?

static constexpr int maxInfoLength = 100;

UniqueObject::uid_t UniqueObject::curFree = 0;

UniqueObject::UniqueObject() : id(UniqueObject::genUID()) {}

inline UniqueObject::uid_t UniqueObject::genUID() {
    return curFree++;
}

inline UniqueObject::uid_t UniqueObject::getId() const {
    return id;
}

bool compareUniqueObjects::operator()(UniqueObject* first, UniqueObject* second) {
    return first->getId() < second->getId();
}

void Canvas::newElement(Drawable* inner) {
    auto status = innerElems.insert({inner->getId(), inner});
    if (status.second != true) {
        char info[maxInfoLength] = {};
        snprintf(info, maxInfoLength, "unable to insert new element with ID %d to element with ID %d", inner->getId(), this->getId()); 
        throw std::runtime_error(info);
    }
}

Drawable* Canvas::searchElem(uid_t id) {
    return innerElems.at(id);
}

