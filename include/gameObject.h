#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <vector>
#include "iconFactory.h"
#include "unit.h"
#include "icon.h"
#include <iostream>
class GameObject{

public:
    
    GameObject();
    Position getPosition() const;
    void changeIconColor(Color Color);
    Icon getIcon() const {
        return _icon;
    }
    std::string gettype() const;
    void changetype(std::string type);
    virtual bool update(std::vector<std::vector<bool>>& visible);
    virtual void move(int input);
    virtual ~GameObject();
    virtual void changespeed(bool inverse = true, int x = 999, int y = 999);
    virtual Vec2 getspeed();

protected:

    Position _pos;
    Icon _icon;
    std::string _type;
    bool _mv;
    int _hp;

};

#endif
