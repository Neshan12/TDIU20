#include "ghost.h"
#include <string>
#include <cmath>

using namespace std;


// Information om komplettering:
//   Siffrorna hänvisar till rättningsprotokollet som finns på
//   kurshemsidan -> läsning -> Literatur -> "Uppgruppens bedömningsprotokoll"
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig.

// -- Komplettering: konstruktorn behöver kontrollera att den inskickade positionen är inom spelplanen och informera anropande kod.

// Kommentar: Pinky::get_chase_point() går att implementera utan if-satser.

// Ghost general
Ghost::Ghost(Pacman &pacman, Point const& start_pos, Point const& scat_point)
    :   pacman{pacman}, pos{}, scat_pos{}
{
    set_position(start_pos);
    check_pos(scat_point);
    scat_pos = scat_point;
}

Ghost::~Ghost() {}

void Ghost::check_pos(Point const& pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= WIDTH || pos.y >= HEIGHT)
    {
        throw std::runtime_error("position outside valid range");
    }
}

Point Ghost::get_scatter_point() const
{
    return scat_pos;
}

void Ghost::set_position(Point const& new_pos)
{
    check_pos(new_pos);
    pos = new_pos;
}

Point Ghost::get_position() const
{
    return pos;
}

// --------------------------------------------------------------------------
// Blinky
Blinky::Blinky(Pacman &pacman, Point const& start_pos, Point const& scat_pos)
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
Pinky::Pinky(Pacman &pacman, Point const& start_pos, Point const& scat_pos)
    : Ghost(pacman, start_pos, scat_pos) {}

Point Pinky::get_chase_point() const
{
    Point tmp = pacman.get_position();

    // Om Pacman rör sig i X-led
    if (pacman.get_direction().x != 0)
    {
        if (pacman.get_direction().x == 1)  // Höger
        {
            tmp.x += 2;
        }
        else if (pacman.get_direction().x == -1)  // Vänster
        {
            tmp.x -= 2;
        }
    }
    // Om Pacman rör sig i Y-led
    else if (pacman.get_direction().y != 0)
    {
        if (pacman.get_direction().y == 1)  // Upp
        {
            tmp.y += 2;
        }
        else if (pacman.get_direction().y == -1)  // Ner
        {
            tmp.y -= 2;
        }
    }
    return tmp;
}

string Pinky::get_color() const
{
    return "pink";
}

// --------------------------------------------------------------------------
// Clyde
Clyde::Clyde(Pacman &pacman, Point const& start_pos, Point const& scat_pos, int n)
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