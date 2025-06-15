// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 
#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "gameObject.h"
#include "unit.h"
#include <cstdlib>
#include <string>
#include "controller.h"

class Player : public GameObject {

    public:
        Player (int x = 10, int y = 10, int width = 1, int height = 1, Color color = Color::BLUE, std::string ascii = "█", std::string type = "Player");
        void update(std::vector<std::vector<bool>>& visible) override;
        void move(int input) override;
        
};

class Block : public GameObject {
    
    public:
        Block (int x = (rand() % 48) + 1, int y = (((rand() % 10) + rand() % 25) % 48) + 1, Vec2 speed = Vec2(0, 0), int width = 1, int height = 1, Color color = Color::RED, std::string ascii = "█", std::string type = "Block");
        void update(std::vector<std::vector<bool>>& visible) override;
        void move(int input) override;
        void changespeed(bool inverse = true, int x = 999, int y = 999) override;
        Vec2 getspeed() override;
    private:
        Vec2 _speed;

};
class Sight : public GameObject {
    public:
};

class Enemy : public GameObject {

    public:
        Enemy (int x, int y, int width = 1, int height = 1,int face_x = 1, int face_y = 1, Color color = Color::RED, std::string ascii = "█", std::string type = "Enemy", Sight* sight = nullptr);
        void update(std::vector<std::vector<bool>>& visible) override;
        void normalmove();
        void move();
        void change_sight(std::vector<std::vector<bool>>& visible);
    private:
        Vec2 _face;
        Sight* _sight;
        int _radius;

};

#endif
