#ifndef MAIN_H
#define MAIN_H

#include "ghost.h"
#include <string>
#include <vector>

class Ghost_Tester
{
public:
    Ghost_Tester();
    void run();
    
private:
    void check_pos(Point & pos);
    bool is_scat() const;
    void set_scat(bool const arg);
    std::string to_draw(Point const& curr_pos);
    void draw_map();

    Pacman pacman;
    std::vector<Ghost*> ghost_list;
    bool scat;
};
#endif