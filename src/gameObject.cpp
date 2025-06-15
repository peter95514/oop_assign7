// TODO implementation
#include "gameObject.h"
#include "unit.h"
#include <pstl/pstl_config.h>
#include <string>

GameObject::GameObject () : _pos(Vec2(0, 0)){
}

Position GameObject::getPosition() const {
    return _pos;
}

void GameObject::changeIconColor(Color color)  {
    _icon[0][0] = Cell(color, "█");
}

void GameObject::changetype (std::string type) {
    _type = type;
}

GameObject::~GameObject(){

}

void GameObject::update(std::vector<std::vector<bool>>& visible) { 
    
}

void GameObject::move(int input) { 
}

std::string GameObject::gettype() const {
    return _type;
}

void GameObject::changespeed(bool inverse, int x, int y) {
    std::cout << "wrong" << std::endl;
}

Vec2 GameObject::getspeed() {
    return Vec2(0, 0);
}
