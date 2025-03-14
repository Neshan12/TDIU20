#ifndef MAIN_H
#define MAIN_H

#include "ghost.h"
#include <string>
#include <vector>
#include <sstream>

class Ghost_Tester
{
public:
    Ghost_Tester();
    ~Ghost_Tester();
    void run();
    
private:
    Ghost* get_ghost_by_color(std::string const& color);
    void update_pacman(const std::string& command, std::istringstream& iss);
    void ghost_commands(std::istringstream & iss, std::string const& command);
    bool is_scat() const;
    void set_scat(bool const arg);
    std::string to_draw(Point const& curr_pos);
    void draw_map();

    Pacman pacman;
    std::vector<Ghost*> ghost_list;
    bool scat;
};
#endif