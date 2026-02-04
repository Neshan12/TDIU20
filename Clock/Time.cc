#include "Time.h"
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// Constructors
Time::Time()
    : hour{0}, minute{0}, second{0}
{}

Time::Time(int h, int m, int s)
    : hour{h}, minute{m}, second{s}
{
    if (!is_valid())
    {
        throw invalid_argument("Felaktigt format!");
    }
}

Time::Time(const std::string& time)
{
    stringstream ss{};
    char trash{};

    if (time.size() !=8 || time.at(2) != ':' || time.at(5) != ':')
    {
        throw invalid_argument("Felaktigt format!");
    }
    
    ss << time;
    ss >> hour >> trash >> minute >> trash >> second;
    
    if (!is_valid())
    {
        throw invalid_argument("Felaktigt format!");
    } 
}

bool Time::is_valid() const
{
    if (hour >= 24 || hour < 0)
    {
        return false;
    }
    if (minute >= 60 || minute < 0)
    {
        return false;
    }
    if (second >= 60 || second < 0)
    {
        return false;
    }

    return true;
}


// Read time
int Time::get_hour() const
{
    return hour;
}

int Time::get_minute() const
{
    return minute;
}

int Time::get_second() const
{
    return minute;
}


// String output
bool Time::is_am() const
{
    return hour < 12 && hour >= 0;
}

string Time::add_zero(const int arg) const
{
    if (arg < 10)
    {
        return '0' + std::to_string(arg);
    }
    return std::to_string(arg);
}

string Time::to_string(bool const arg) const
{
    ostringstream new_string{};
    int display_hour{(hour % 12)};

    if (arg)
    {
        new_string << add_zero(hour) << ':' << add_zero(minute) << ':' << add_zero(second);
    }
    else
    {
        if (display_hour == 0)
        {
            display_hour = 12;
        }
        new_string << add_zero(display_hour) << ':' << add_zero(minute) << ':' << add_zero(second) << (is_am() ? " AM" : " PM");
    }

    return new_string.str();
}


// OPERATORS

// Logic
bool Time::operator!=(Time const & rhs) const
{
    return hour != rhs.hour || minute != rhs.minute || second != rhs.second; 
}

bool Time::operator==(Time const & rhs) const
{
    return !(*this != rhs);
}

bool Time::operator> (Time const & rhs) const
{
    return rhs < *this;
}

bool Time::operator< (Time const & rhs) const
{
    return hour < rhs.hour || (hour == rhs.hour && (minute < rhs.minute || (minute == rhs.minute && second < rhs.second)));
}

bool Time::operator>=(Time const & rhs) const
{
    return rhs <= *this;
}

bool Time::operator<=(Time const & rhs) const
{
    return *this < rhs || *this == rhs;
}



// Increase/Decrease
Time& Time::operator++()
{
    return *this = *this + 1;
}

Time Time::operator++(int)
{
    Time tmp{*this};
    ++(*this);
    return tmp;
}

Time& Time::operator--()
{
    return *this = *this - 1;
}

Time Time::operator--(int)
{
    Time tmp{*this};
    --(*this);
    return tmp;
}

// Increase/Decrease with n
Time Time::operator+(int const& n)
{
    second += n;

    while (second >= 60)
    {
        if (second >= 60)
        {
            minute += 1;
            second -= 60;
        }
        if (minute >= 60)
        {
            hour += 1;
            minute -= 60;
        }
        if (hour >= 24)
        {
            hour -= 24;
        }
    }
    
    return *this;
}

Time Time::operator-(int const& n)
{
    second -= n;

    while (second < 0)
    {
        if (second < 0)
        {
            second += 60;
            minute -= 1;
        }
        if (minute < 0)
        {
            minute += 60;
            hour -= 1;
        }
        if (hour < 0)
        {
            hour += 24;
        }
    }
    
    return *this;
}

Time Time::operator+=(int const& n)
{
    return *this + n;
}

Time Time::operator-=(int const& n)
{
    return *this - n;
}


// Streams
Time Time::operator>>(string const& time)
{
    Time tmp{time};
    return *this = tmp;
} 

Time Time::operator>>(Time const& time)
{
    Time tmp{time};
    return *this = tmp;
}

ostream &operator<<(ostream& os, Time const & time)
{
    return os << time.to_string();
}

istream &operator>>(istream& is, Time & time)
{
    int hour{}, minute{}, second{};
    char c1{}, c2{};

    if (is >> hour >> c1 >> minute >> c2 >> second && c1 == ':' && c2 == ':')
    {
        try
        {
            time = Time{hour, minute, second};
        }
        catch(invalid_argument const& e)
        {
            is.setstate(ios_base::failbit);
        }
    }
    else
    {
        is.setstate(ios_base::failbit);
    }
    return is;
}

Time operator+(int const n, Time & time) {
    return time + n;
}