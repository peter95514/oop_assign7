// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller. 
#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include <string>
#include "icon.h"
#include "unit.h"

namespace IconFactory {

    Icon Block_icon (int width = 1, int height = 1, Color color = Color::RED, std::string ascii = "█");
    Icon Player_icon (int width = 1, int height = 1, Color color = Color::BLUE, std::string ascii = "█");

}

#endif
