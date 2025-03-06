#include "main.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

/*
  Ledning och Tips:

  - *Modifiera stukturen till en header-fil och en implementationsfil
  - Ut�ka 'run()' och 'draw_map()' med �vrig funktionalitet.
  - L�gg alla sp�ken i en l�mplig beh�llare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Anv�nd hj�lpfunktioner f�r att undvika duplicering av kod.
  - T�nk p� att varje funktion inte borde vara l�ngre �n 25 rader.
 */


Ghost_Tester::Ghost_Tester()
    : pacman {}, ghost_list {new Blinky{pacman, Point{1, 5}, Point{WIDTH-1, HEIGHT-1}},
                             new Pinky {pacman, Point{3, 4}, Point{0, HEIGHT-1}},
                             new Clyde{pacman,  Point{4, 2}, Point{0, 0}, 6}}, scat{false}
{
    Point tmp{1, 1};
    pacman.set_position(tmp);
    tmp = {1, 0};
    pacman.set_direction(tmp);
}

void Ghost_Tester::run()
{
    while(true)
    {
        draw_map();
        cout << "> ";

        string line {};
        getline(cin, line);
        istringstream iss {line};
    
        string command {};
        iss >> command;

        if (command == "pos")
        {
            Point new_pos {};
            iss >> new_pos.x >> new_pos.y;
            check_pos(new_pos);
            pacman.set_position(new_pos);

        }
        else if (command == "dir")
        {
        }
        else if (command == "scatter")
        {
            set_scat(true);
        }
        else if (command == "red")
        {
            Point new_pos {};
            iss >> new_pos.x >> new_pos.y;
            check_pos(new_pos);
            ghost_list.at(0)->set_position(new_pos);
        }
        else if (command == "pink")
        {
            Point new_pos {};
            iss >> new_pos.x >> new_pos.y;
            check_pos(new_pos);
            ghost_list.at(1)->set_position(new_pos);
        }
        else if (command == "orange")
        {
            Point new_pos {};
            iss >> new_pos.x >> new_pos.y;
            check_pos(new_pos);
            ghost_list.at(2)->set_position(new_pos);
        }
        else if (command == "quit")
        {
            break;
        }
    }
}

void Ghost_Tester::check_pos(Point & pos)
{
    if (pos.x >= WIDTH)
    {
        pos.x = WIDTH-1;
    }
    if (pos.y >= HEIGHT)
    {
        pos.y = HEIGHT-1;
    }
}

bool Ghost_Tester::is_scat() const
{
    return scat;
}
void Ghost_Tester::set_scat(bool const arg)
{
    scat = arg;
}
/*
    En hj�lpfunktion som avg�r vilka tv� tecken som ska ritas ut f�r en given position p�
    spelplanen.
*/
string Ghost_Tester::to_draw(Point const& curr_pos)
{
    string to_draw{"  "};
    for (Ghost* const& ghost : ghost_list)
    {
        ghost->update_pacman(pacman);

        if (ghost->get_position() == curr_pos)
        {
            if (ghost->get_color() == "red")
            {
                to_draw[1] = 'R';
            }
            else if (ghost->get_color() == "pink")
            {
                to_draw[1] = 'P';
            }
            else if (ghost->get_color() == "orange")
            {
                to_draw[1] = 'O';
            }
        }

        // Target
        if (ghost->get_chase_point() == curr_pos && is_scat() == false)
        {
            if (ghost->get_color() == "red")
            {
                to_draw[0] = 'r';
            }
            else if (ghost->get_color() == "pink")
            {
                to_draw[1] = 'p';
            }
            else if (ghost->get_color() == "orange")
            {
                to_draw[1] = 'o';
            }
        }
        else if (ghost->get_scatter_point() == curr_pos && is_scat() == true)
        {
            if (ghost->get_color() == "red")
            {
                to_draw[0] = 'r';
            }
            else if (ghost->get_color() == "pink")
            {
                to_draw[1] = 'p';
            }
            else if (ghost->get_color() == "orange")
            {
                to_draw[1] = 'o';
            }
        }
    }

    if (pacman.get_position() == curr_pos)
    {
        to_draw[1] = '@';
    }
    return to_draw;
}
    
/*
    En hj�lpfunktion f�r att rita ut spelplanen f�r testprogrammet.
    
    Itererar �ver varje rad och column i kartan. Index f�r raderna �r flippade f�r att placera
    y = 0 l�ngst ned.
    
    Varje punkt i kartan ritas som tv� tecken eftersom ett tecken i terminalen �r ca dubbelt s�
    h�gt som det �r brett.
*/
void Ghost_Tester::draw_map()
{
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

    for (int y {HEIGHT - 1}; y >= 0; --y) 
    {
        cout << "|";
        for (int x {}; x < WIDTH; ++x) 
        {
            cout << to_draw( Point{x,y} );
        }
        cout << "|\n";
    }

    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
}




int main()
{
    Ghost_Tester gt {};
    gt.run();
    return 0;
}
