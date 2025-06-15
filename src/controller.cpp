#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <typeinfo>
#include <iomanip>
#include <math.h>

#include "environment.h"
#include "controller.h"
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "iconFactory.h"
#include "unit.h"
#include "icon.h"


long long ran() {
    long long temp = rand();
    srand(temp % 500000000);
    return temp;
}

bool hasLineOfSight(int ex, int ey, int tx, int ty) {
    int dx = abs(tx - ex);
    int dy = abs(ty - ey);
    int sx = (ex < tx) ? 1 : -1;
    int sy = (ey < ty) ? 1 : -1;
    int err = dx - dy;

    int x = ex;
    int y = ey;

    while (true) {
        if (x == tx && y == ty) {
            return true;
        }

        if (!(x == ex && y == ey) && initmap[y][x] == '#') {
            return false;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

bool isWithin45Degrees(int fx, int fy, int dx, int dy) {
    double len1 = std::sqrt(fx*fx + fy*fy);
    double len2 = std::sqrt(dx*dx + dy*dy);
    if (len1 == 0 || len2 == 0) return false;

    double dot = fx * dx + fy * dy;
    double cosTheta = dot / (len1 * len2);

    return cosTheta >= std::cos(M_PI / 4);
}

Controller::Controller(View& view): _view(view){
    for(int i = 0; i < GAME_WINDOW_HEIGHT; i ++) {
        for (int k = 0; k < GAME_WINDOW_WIDTH; k ++) {
            if(initmap[i][k] == '#') {
                update(new Block(k, i,Vec2(0, 0), 1, 1, Color::PINK, "█", "Block"));
            }
            if(initmap[i][k] == 'O') {
                update(new Block(k, i,Vec2(0, 0), 1, 1, Color::BLUE, "█", "Win"));
            }
            if(initmap[i][k] == 'X') {
                update(new Enemy(k, i, 1, 1, 1, 0, Color::RED, "█", "Enemy"));
            }
        }
    }
    update(new Player(25, 47, 1, 1, Color::GREEN, "█"));
    for(auto obj : _objs) {
        if(obj->gettype() == "Player") {
            _player = obj;
        }
    }
    std::cout << "Controller initialized" << std::endl;
}

void Controller::reset() {
    auto make_vis_buf = [] {
        return std::vector<std::vector<bool>>(
            GAME_WINDOW_HEIGHT, std::vector<bool>(GAME_WINDOW_WIDTH, false));
    };
    latest_vis_con = make_vis_buf();
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    // init state
    int input = -1;
    clock_t start, end;
    
    // Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27)break;

        this->handleInput(input);

        reset();
        _view.resetLatest();
        if(this->check()) {
            std::cout << "you win!!" << std::endl;
            break;
        }
        
        for(GameObject* obj : _objs) 
        {
            obj->update(latest_vis_con);
            _view.updateGameObject(obj);
        }
        _view.changevis(latest_vis_con);

        _view.render();
        if(this->checklose()) {
            std::cout << "you lose!!" << std::endl;
            break;
        }


        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 40); // 0.1 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

}

bool Controller::checklose() {
    auto[x,y] = _player->getPosition();
    if(latest_vis_con[y][x] == 1) {
        return true;
    }
    return false;
}

bool Controller::check() {
    for(int i = 0; i < _objs.size(); i ++) {
        if(_player == _objs[i]) continue;
        if(_player->getPosition() == _objs[i]->getPosition() && _objs[i]->gettype() == "Win") return true;
    }
    return false;
}

void Controller::handleInput(int keyInput){

    // If there is no input, do nothing.
    if(keyInput==-1)return;
    // TODO 
    // handle key events.
    _player->move(keyInput);

}

void Controller::update(GameObject* input){

    _objs.push_back(input);

}
void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}

int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}


