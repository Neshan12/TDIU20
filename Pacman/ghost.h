#ifndef GHOST_H
#define GHOST_H

#include "given.h"
#include <string>

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

// -- Komplettering: Ni bör spara en referens till pacman så att ni inte behöver uppdatera pacmans position manuellt
// -- Komplettering: Parameteröverföring av sammansatta datatyper ska om möjligt ske som konstant referens.

class Ghost
{
public:
    Ghost(Pacman &pacman, Point const& start_pos, Point const& scat_point);
    virtual ~Ghost();

    void check_pos(Point const& pos);
    virtual Point get_chase_point() const = 0;
    virtual Point get_scatter_point() const;
    virtual std::string get_color() const = 0;
    void set_position(Point const& new_pos);
    Point get_position() const;

protected:
    Pacman &pacman;
    Point pos;
    Point scat_pos;
};

class Blinky : public Ghost
{
public:
    Blinky(Pacman &pacman, Point const& start_pos, Point const& scat_pos);
    Point get_chase_point() const override;
    Point get_scatter_point() const override;
    std::string get_color() const override;

    bool is_angry() const;
    void set_angry(bool const angry);

private:
    bool angry;
};

class Pinky : public Ghost
{
public:
    Pinky(Pacman &pacman, Point const& start_pos, Point const& scat_pos);
    Point get_chase_point() const override;
    std::string get_color() const override;
};

class Clyde : public Ghost
{
public:
    Clyde(Pacman &pacman, Point const& start_pos, Point const& scat_pos, int n);

    Point get_chase_point() const override;
    std::string get_color() const override;

private:
    int n;
};

#endif