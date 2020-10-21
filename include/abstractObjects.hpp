#include <unordered_map>
#include "usefulDefines.hpp"

namespace kudry {

class Drawable;

class UniqueObject {
public:
    typedef unsigned int uid_t;

    UniqueObject();

    NON_COPYBLE(UniqueObject)

    static uid_t genUID();

    virtual uid_t getId() const;

private:
    const uid_t id;
    static uid_t curFree;
};

class compareUniqueObjects {
public:
    bool operator()(UniqueObject* first, UniqueObject* second);
};

class Canvas : public UniqueObject {
public:
    virtual void drawAll() = 0;
    virtual void Quit() = 0;
    virtual void eventLoop() = 0; // цикл снаружи

    void newElement(Drawable* inner);

    Drawable* searchElem(uid_t id);

private:
    std::unordered_map<uid_t, Drawable*> innerElems;
};

class Drawable : public UniqueObject {
public:
    Drawable(Canvas& canvas);

    // NON_COPYBLE by default? Seems so.

    virtual void draw() = 0;

private:
    std::unordered_map<uid_t, Drawable*> innerElems;
    Canvas* canvas;
};

};