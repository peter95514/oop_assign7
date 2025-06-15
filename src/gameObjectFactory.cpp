// TODO implementation
#include <math.h>
#include "gameObjectFactory.h"
#include "environment.h"
#include "iconFactory.h"
#include "unit.h"
#include <ostream>
#include <string>
#include "controller.h"


Player::Player (int x, int y, int width, int height, Color color, std::string ascii, std::string type) {
    _pos = Vec2(x, y);
    _icon = IconFactory::Player_icon(width, height, color, ascii);
    _type = type;
}

void Player::update(std::vector<std::vector<bool>>& visible) {
}

void Player::move (int input) {
    int tempx = this->_pos.e1;
    int tempy = this->_pos.e2;
    switch (input) {
        case 97://a
            tempx -= 1;
            break;
        case 100://d
            tempx += 1;
            break;
        case 115://s 
            tempy += 1;
            break;
        case 119://w
            tempy -= 1;
            break;
    }
    if(initmap[tempy][tempx] == '#') {
        tempx = _pos.e1;
        tempy = _pos.e2;
    }
    _pos.e1 = tempx;
    _pos.e2 = tempy;

}

Block::Block (int x, int y, Vec2 speed, int width, int height, Color color, std::string ascii, std::string type) : _speed(speed) {
    _type = type;
    _pos = Vec2(x, y);
    _icon = IconFactory::Block_icon(width, height, color, ascii);
}

void Block::move(int input) {
}

void Block::changespeed(bool inverse, int x, int y) {
}

void Block::update(std::vector<std::vector<bool>>& visible){
    _pos = _pos + _speed;
}

Vec2 Block::getspeed() {
    return _speed;
}

Enemy::Enemy (int x, int y, int width, int height, int face_x, int face_y, Color color, std::string ascii, std::string type, Sight* sight) : _face(Vec2(face_x, face_y)), _sight(sight){
    _pos = Vec2(x, y);
    _icon = IconFactory::Block_icon(width, height, color, ascii);
    _type = type;
    _radius = 5;
}

void Enemy::update(std::vector<std::vector<bool>>& visible) {
    normalmove();
    change_sight(visible);
}

void Enemy::normalmove() {
    if(ran() % 20 == 1) {
        int temp = ran() % 4;
        switch (temp) {
            case 0:
                _face = Vec2(1, 0);
                break;
            case 1:
                _face = Vec2(-1, 0);
                break;
            case 2:
                _face = Vec2(0, 1);
                break;
            case 3:
                _face = Vec2(0, -1);
                break;
        }
    }
    if(ran() % 10 != 1) return;
    if(initmap[_pos.e2 + _face.e2][_pos.e1 + _face.e1] == '#') {
        return;
    }
    _pos.e1 += _face.e1;
    _pos.e2 += _face.e2;
}

void Enemy::change_sight(std::vector<std::vector<bool>>& visible) {
    for (int dy = -_radius; dy <= _radius; ++dy) {
        for (int dx = -_radius; dx <= _radius; ++dx) {
            int tx = _pos.e1 + dx;
            int ty = _pos.e2 + dy;

            if (tx < 0 || ty < 0 || tx >= GAME_WINDOW_WIDTH || ty >= GAME_WINDOW_HEIGHT)
                continue;

            int rel_dx = tx - _pos.e1;
            int rel_dy = ty - _pos.e2;

            double dist = std::sqrt(rel_dx * rel_dx + rel_dy * rel_dy);
            if (dist > _radius) continue;

            if (!isWithin45Degrees(_face.e1, _face.e2, rel_dx, rel_dy)) continue;

            if (hasLineOfSight(_pos.e1, _pos.e2, tx, ty)) {
                visible[ty][tx] = true;
            }
        }
    }
}
