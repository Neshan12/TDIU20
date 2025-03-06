#ifndef GHOST_H
#define GHOST_H

#include "given.h"
#include <string>

class Ghost
{
public:
    Ghost(Pacman pacman, Point start_pos, Point scat_pos);
    virtual ~Ghost();

    virtual Point get_chase_point() const = 0;
    virtual Point get_scatter_point() const;
    virtual std::string get_color() const = 0;
    void set_position(Point const& new_pos);
    Point get_position() const;
    void update_pacman(Pacman const& pac);

protected:
    Pacman pacman;
    Point pos;
    Point scat_pos;
};




class Blinky : public Ghost
{
public:
    Blinky(Pacman pacman, Point start_pos, Point scat_pos);
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
    Pinky(Pacman pacman, Point start_pos, Point scat_pos);
    Point get_chase_point() const override;
    std::string get_color() const override;
};

class Clyde : public Ghost
{
public:
    Clyde(Pacman pacman, Point start_pos, Point scat_pos, int n);

    Point get_chase_point() const override;
    std::string get_color() const override;

private:
    int n;
    // Point pos;
    // Point scat_pos;
    // Pacman pacman;
};

#endif