#include "catch.hpp"
#include "list.h"
#include <sstream>

using namespace std;

TEST_CASE ("Default")
{
    List l0{};
    List l1{2};
    List l2{2, 5, 7};

    SECTION("Empty")
    {
        CHECK( l0.empty() );
    }

    SECTION("Not Empty")
    {
        CHECK_FALSE( l1.empty() );
    }

    SECTION("Multiple")
    {
        CHECK( l2.empty() == false );
    }
}

TEST_CASE ("Length")
{
    List l0{};
    List l1{2};
    List l2{2, 5};
    List l3{2, 5, 7};

    SECTION("Length")
    {
        CHECK( l0.length() == 0);
        CHECK( l1.length() == 1);
        CHECK( l2.length() == 2);
        CHECK( l3.length() == 3);
    }
}

TEST_CASE ("Remove")
{  
    List l0{2};
    List l1{2, 5};
    List l2{2, 5, 7};
    List l4{2, 4, 5, 7};
    List l5{};

    SECTION("First")
    {
        CHECK_NOTHROW( l0.remove(0) );
        CHECK( l0.empty() == true );
        CHECK_NOTHROW( l1.remove(0) );
        CHECK( l1.length() == 1 );
        CHECK_NOTHROW( l2.remove(0) );
        CHECK( l2.length() == 2 );
    } 
    SECTION("In between")
    {
        CHECK_NOTHROW( l2.remove(1) );
        CHECK( l2.length() == 2 );
        CHECK_NOTHROW( l4.remove(2) );
        CHECK( l4.length() == 3 );
    }
    SECTION("Last")
    {
        CHECK_NOTHROW( l1.remove(1) );
        CHECK( l1.length() == 1 );
        CHECK_NOTHROW( l2.remove(2) );
        CHECK( l2.length() == 2 );
        CHECK_NOTHROW( l4.remove(3) );
        CHECK( l4.length() == 3 );
    } 
    SECTION("Extra")
    {
        CHECK_THROWS( l5.remove(0) );
        CHECK_THROWS( l4.remove(10) );
    }
}

TEST_CASE("at")
{
    List l0{};
    List l1{2};
    List l2{2, 5};
    List l3{2, 5, 7};

    SECTION("at")
    {
        CHECK_THROWS( l0.at(0) );
        CHECK_THROWS( l3.at(27) );

        CHECK( l1.at(0) == 2);
        CHECK( l2.at(0) == 2);
        CHECK( l2.at(1) == 5);
        CHECK( l3.at(2) == 7);
    }
}

TEST_CASE("to_string()")
{
    List l0{};
    List l1{2};
    List l2{2, 5};
    List l3{2, 5, 7};

    SECTION("to_string()")
    {
        CHECK_THROWS(l0.to_string());
        CHECK( l1.to_string() == "2" );
        CHECK( l2.to_string() == "2, 5" );
        CHECK( l3.to_string() == "2, 5, 7" );
    }
}

TEST_CASE("Stream")
{
    List l0{};
    List l1{2};
    List l2{2, 5};
    List l3{2, 5, 7};
    stringstream ss{};

    CHECK_THROWS( ss << l0 );
    ss = {};

    CHECK_NOTHROW( ss << l1 );
    CHECK( ss.str() == "2" );
    ss = {};

    CHECK_NOTHROW( ss << l2 );
    CHECK( ss.str() == "2, 5" );
    ss = {};

    CHECK_NOTHROW( ss << l3 );
    CHECK( ss.str() == "2, 5, 7" );
    ss = {};
}

TEST_CASE("Specifika Medlemsfunktioner")
{
    SECTION("Kopieringskonstruktorn")
    {
        List l1{2, 4, 6};
        List copy{l1};

        CHECK(copy.empty() == false);

        CHECK(copy.to_string() == "2, 4, 6");  
        CHECK(l1.to_string() == "2, 4, 6");  // Originalet ska vara samma

        copy.remove(1); // Ändra kopian och kolla om nåt händer med originalet
        CHECK(copy.to_string() == "2, 6");
        CHECK(l1.to_string() == "2, 4, 6");  // Originalet ska vara samma
    }

    SECTION("Flyttkonstruktorn")
    {
        List l1{2};
        List l2{std::move(l1)};
        CHECK( l2.empty() == false );
        CHECK( l2.to_string() == "2" );
        CHECK( l1.empty() == true );   
    }

    SECTION("Kopieringstilldelningsoperator")
    {
        List l1{2};
        List l2{5, 7};
        l2 = l1;
        CHECK( l1.to_string() == "2");
        CHECK( l2.to_string() == "2" );
    }

    SECTION("Kopieringstilldelningsoperator")
    {
        List l1{2, 4, 6};
        List l2{5, 7, 9};
        l2 = l1;

        CHECK(l1.to_string() == "2, 4, 6");
        CHECK(l2.to_string() == "2, 4, 6");

        l2.remove(1); // Ändra ena och kolla ifall andra e samma
        CHECK(l2.to_string() == "2, 6");
        CHECK(l1.to_string() == "2, 4, 6");  // Originalet ska vara samma
    }
}