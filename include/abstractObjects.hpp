#include "usefulDefines.hpp"
#include <type_traits>
#include <queue>
#include <initializer_list>

/*
    ПЛАН:
    1. Глянуть ncurses | MFC | OpenGL | WTL
    2. Доделать архитектуру
    3. Написать SFML-адаптор к ней
    4. Переписать сортировку
*/

namespace kudry {

template <typename Adaptor>
class RenderWindow;

class Event;

template <typename Adaptor>
class WindowManager {
public:
    virtual bool EmplaceWindow(RenderWindow* newWindow) = 0;

    Event* GetEvent();

    virtual bool SaveTo(std::string filename) = 0;

    virtual bool LoadFrom(std::string filename) = 0;

    virtual void Render() = 0;

protected:
    std::queue<Event*> eventQueue;
};

template <typename Adaptor>
class RenderWindow {
public:
    virtual void Draw() = 0;

    virtual void HandleEvent(Event* event) = 0;

protected:
    //std::queue<Event*> eventQueue;

};

class Event {
public:
    virtual void* ClassID();
    /*
    {
        return classID;
    }
    */
};

template <typename Adaptor>
class KeyboardEvent : public Event {};

template <typename Adaptor>
class CloseEvent : public Event {};

template <typename Adaptor>
class MouseEvent : public Event {};

};