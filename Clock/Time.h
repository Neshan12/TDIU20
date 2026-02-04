#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
public:
    Time();
    Time(int h, int m, int s);
    Time(const std::string & time);

    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    bool is_am() const;

    std::string to_string(bool const arg = true) const;

    // Operators
    bool operator!=(Time const & rhs) const;
    bool operator==(Time const & rhs) const;
    bool operator> (Time const & rhs) const;
    bool operator< (Time const & rhs) const;
    bool operator>=(Time const & rhs) const;
    bool operator<=(Time const & rhs) const;

    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    Time operator+ (int const& n);
    Time operator- (int const& n);
    Time operator+=(int const& n);
    Time operator-=(int const& n);

    Time operator>>(std::string const& time);
    Time operator>>(Time const& time);
 
private:
    int hour;
    int minute;
    int second;

    std::string add_zero(const int arg) const;
    bool is_valid() const;
};

std::ostream &operator<<(std::ostream& os, Time const & arg);
std::istream &operator>>(std::istream& is, Time & time);
Time operator+(int const n, Time & time);

#endif
