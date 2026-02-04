#ifndef LIST_H
#define LIST_H

#include <string>
#include <initializer_list>
#include <vector>

class List
{
public:
    List();
    List(std::initializer_list<int> l);
    ~List();
    List(List const& other);
    List(List && other);
    List& operator=(List const& rhs);
    List& operator=(List && rhs);
    
    void insert(int const value);
    void remove(int const value);
    

    int length() const;
    bool empty() const;
    int at(int const value) const;
    std::string to_string() const;
    
    List sub(const std::vector<int> l) const;

private:
    class Node
    {
    public:
        int value;
        Node* next;
        Node* previous;

        Node(int value, Node* next, Node* previous); // Node
        Node();
    };

    Node* sentinel;
};

std::ostream &operator<<(std::ostream& os,List const & list);
#endif
