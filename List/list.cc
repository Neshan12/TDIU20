#include "list.h"
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;

List::Node::Node(int value, Node* next, Node* previous)
    : value{value}, next{next}, previous{previous} {}

List::Node::Node()
    : value{0}, next{nullptr}, previous{nullptr}// Sentinel
{

}

List::List() // default med sentinel config
    : sentinel{new Node(0, nullptr, nullptr)}
{
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
}

List::List(std::initializer_list<int> l)
    : List()
{
    for (int data : l) 
    {
        insert(data);
    }
}

// Specifika medlemmar
List::~List()
{
    Node* current = sentinel->next;
    while (current != sentinel)
    {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    delete sentinel;
}

List::List(List const& other)
    : List()
{
    Node* current {other.sentinel->next};

    while(current != other.sentinel)
    {
        insert(current->value);
        current = current->next;
    }
}

List::List(List && other)
    : sentinel{other.sentinel}
{
    other.sentinel = new Node();
    other.sentinel->next = other.sentinel;
    other.sentinel->previous = other.sentinel;
}

List& List::operator=(List const& rhs)
{
    List tmp {rhs};
    swap(tmp.sentinel, sentinel);
    return *this;
}

List& List::operator=(List && rhs)
{
    swap(rhs.sentinel, sentinel);
    return *this;
}

bool List::empty() const
{
    return sentinel->next == sentinel;
}

void List::insert(int const value)
{
    Node* current = sentinel->next;

    while (value > current->value && current != sentinel)
    {
        current = current->next;
    }    

    Node* tmp = new Node{value, current, current->previous};
    current->previous->next = tmp;
    current->previous = tmp;
}

int List::length() const
{
    Node* current = sentinel->next;
    int count{};

    while (current != sentinel)
    {
        count++;
        current = current->next;
    }

    return count;
}

void List::remove(int const value)
{
    Node* current = sentinel->next;

    if (value < 0 || value > length() || empty())
    {
        throw out_of_range("Index out of range!");
    }

    for (int i{}; i < value; ++i)
    {
        current = current->next;
    }

    current->previous->next = current->next;
    current->next->previous = current->previous;
    delete current;
}  

int List::at(int const value) const
{
    Node* current = sentinel->next;

    if (value < 0 || value > length() || empty())
    {
        throw out_of_range("Index out of range!");
    }

    for (int i{}; i < value; ++i)
    {
        current = current->next;
    }

    return current->value;
}

string List::to_string() const
{
    stringstream ss{};

    if (empty())
    {
        throw out_of_range("List empty!");
    }

    for (int i{}; i < length(); ++i)
    {  
        if (i != 0)
        {
            ss << ", ";
        }

        ss << at(i);
    }

    return ss.str();
}

List List::sub(const vector<int> list) const
{
    List tmp{};
    int last_value{};

    for (size_t i; i < list.size(); ++i) 
    {
        if (list.at(i) < last_value)
        {
            throw invalid_argument("Wrong order");
        }

        tmp.insert(at(list.at(i)));
        last_value = list.at(i);
    }

    return tmp;
}


std::ostream &operator<<(std::ostream& os, List const & list)
{
    return os << list.to_string();
}
