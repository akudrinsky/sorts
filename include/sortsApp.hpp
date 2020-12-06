#pragma once

#include <SFML/Graphics.hpp>
#include "abstractObjects.hpp"
#include "button.hpp"
#include "graph.hpp"
#include "usefulDefines.hpp"

#include <vector>

template<typename Adaptor>
class SortsApp : public kudry::WindowManager<Adaptor> {
public:
    virtual bool EmplaceWindow(RenderWindow<Adaptor>* newWindow) override;

    Event* GetEvent() override;

    virtual bool SaveTo(std::string filename) override;

    virtual bool LoadFrom(std::string filename) override;

    virtual void Render() override;

    void SetBackground(kudry::RenderWindow<Adaptor>* newBackground);

private:
    kudry::RenderWindow<Adaptor>* backgroundImage;
    
    std::vector<kudry::RenderWindow<Adaptor>*> subwindows;
};

