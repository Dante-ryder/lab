#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string type;

public:
    Player();
    void setType(std::string type);
    ~Player();
};

#endif