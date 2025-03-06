#include "ghost.h"
#include <string>
#include <cmath>

using namespace std;


// Ghost general
Ghost::Ghost(Pacman pacman, Point start_pos, Point scat_pos)
    :   pacman{pacman}, pos{start_pos}, scat_pos{scat_pos}
{}

Ghost::~Ghost() {}

Point Ghost::get_scatter_point() const
{
    return scat_pos;
}

void Ghost::set_position(Point const& new_pos)
{
    pos = new_pos;
}

Point Ghost::get_position() const
{
    return pos;
}

void Ghost::update_pacman(Pacman const& pac)
{
    pacman = pac;
}
// --------------------------------------------------------------------------
// Blinky
Blinky::Blinky(Pacman pacman, Point start_pos, Point scat_pos)
    : Ghost(pacman, start_pos, scat_pos), angry{false} {}

Point Blinky::get_chase_point() const
{
    return pacman.get_position();
}

Point Blinky::get_scatter_point() const
{
    if (is_angry())
    {
        return get_chase_point();
    }
    else
    {
        return scat_pos;
    }
}

string Blinky::get_color() const
{
    return "red";
}

bool Blinky::is_angry() const
{
    return angry;
}

void Blinky::set_angry(bool const arg)
{
    angry = arg;
}

// --------------------------------------------------------------------------
// Pinky
Pinky::Pinky(Pacman pacman, Point start_pos, Point scat_pos)
    : Ghost(pacman, start_pos, scat_pos) {}

Point Pinky::get_chase_point() const
{
    Point tmp{};

    if (pacman.get_direction().x == 0 && pacman.get_direction().y == 0) // Stilla
    {
        return pacman.get_position(); // Om pacman still => Pacmans pos = chase
    }
    else if (pacman.get_direction().x == -1 && pacman.get_direction().y == 0) // Vänster
    {
        tmp.x = pacman.get_position().x - 2;
        tmp.y = pacman.get_position().y;
    }
    else if (pacman.get_direction().x == 1 && pacman.get_direction().y == 0) // Höger
    {
        tmp.x = pacman.get_position().x + 2;
        tmp.y = pacman.get_position().y;
    }
    else if (pacman.get_direction().y == -1 && pacman.get_direction().x == 0) // Ner
    {
        tmp.y = pacman.get_position().y - 2;
        tmp.x = pacman.get_position().x;
    }
    else if (pacman.get_direction().y == 1 && pacman.get_direction().x == 0) // Upp
    {
        tmp.y = pacman.get_position().y + 2;
        tmp.x = pacman.get_position().x;
    }
    else
    {
        throw invalid_argument("Invalid direction!");
    }
    return tmp;
}

string Pinky::get_color() const
{
    return "pink";
}

// --------------------------------------------------------------------------
// Clyde

Clyde::Clyde(Pacman pacman, Point start_pos, Point scat_pos, int n)
    :   Ghost(pacman, start_pos, scat_pos), n{n}
{}

Point Clyde::get_chase_point() const
{
    int dist_x{abs(pacman.get_position().x-pos.x)};
    int dist_y{abs(pacman.get_position().y-pos.y)};

    if (sqrt(pow(dist_x, 2)*pow(dist_y, 2)) > n) // Längre bort 
    {
        return pacman.get_position();     
    }
    return scat_pos;  
}

string Clyde::get_color() const
{
    return "orange";
}