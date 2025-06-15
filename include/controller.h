#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "gameObject.h"

class Controller{

public:
       
    Controller(View&);
    void run();
    void update(GameObject* input);
    bool check();
    void next();
    void reset();
    bool checklose();

private:

    void handleInput(int);

    // Model
    std::vector<GameObject*> _objs;

    GameObject* _player;

    // View
    View& _view; 
    std::vector<std::vector<bool>> latest_vis_con;

};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();
long long ran();
bool isWithin45Degrees(int fx, int fy, int dx, int dy);
bool hasLineOfSight(int ex, int ey, int tx, int ty);  

#endif
