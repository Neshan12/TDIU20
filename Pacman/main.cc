#include "main.h"
#include <string>
#include <iostream>
#include <iomanip>

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

// --Komplettering: Kodupprepning i kommandona för pos, dir och flytta spöken.
// --Komplettering: Vi kan inte anta ordningen för spökena i listan


Ghost_Tester::Ghost_Tester()
    : pacman {}, ghost_list {new Blinky{pacman, Point{1, 5}, Point{WIDTH-1, HEIGHT-1}},
                             new Pinky {pacman, Point{3, 4}, Point{0, HEIGHT-1}},
                             new Clyde{pacman,  Point{4, 2}, Point{0, 0}, 6}}, scat{false}
{
    pacman.set_position(Point{1, 1});
    pacman.set_direction(Point{1, 0});
}

Ghost_Tester::~Ghost_Tester()
{
    for (Ghost* const& ghost : ghost_list)
    {
        delete ghost;
    }
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

        if (command == "pos" || command == "dir")
        {
            update_pacman(command, iss);
        }
        else if (command == "scatter" || command == "chase")
        {
            set_scat(command == "scatter");
        }
        else if (command == "anger" || command == "unanger")
        {
            Ghost* blinky = get_ghost_by_color("red");
            if (blinky)
            {
                static_cast<Blinky*>(blinky)->set_angry(command == "anger");
            }
        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            ghost_commands(iss, command);
        }
    }
}

Ghost* Ghost_Tester::get_ghost_by_color(std::string const& color)
{
    for (Ghost* const& ghost : ghost_list)
    {
        if (ghost->get_color() == color)
        {
            return ghost;
        }
    }
    return nullptr;
}

void Ghost_Tester::update_pacman(const string& command, istringstream& iss)
{
    Point new_value{};
    iss >> new_value.x >> new_value.y;
    
    if (command == "pos")
    {
        pacman.set_position(new_value);
    }
    else if (command == "dir")
    {
        pacman.set_direction(new_value);
    }
}


void Ghost_Tester::ghost_commands(istringstream & iss, string const& command)
{
    for (Ghost* const& ghost : ghost_list)
    {
        if (command == ghost->get_color())
        {
            Point new_pos {};
            iss >> new_pos.x >> new_pos.y;
            ghost->set_position(new_pos);
        }
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

string Ghost_Tester::to_draw(Point const& curr_pos)
{
    string to_draw{"  "};
    for (Ghost* const& ghost : ghost_list)
    {
        if (ghost->get_position() == curr_pos)
        {
            to_draw[0] = toupper(ghost->get_color()[0]); 
        }

        if (ghost->get_chase_point() == curr_pos && is_scat() == false)
        {
            to_draw[0] = tolower(ghost->get_color()[0]); 
        }
        else if (ghost->get_scatter_point() == curr_pos && is_scat() == true)
        {
            to_draw[0] = tolower(ghost->get_color()[0]); 
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