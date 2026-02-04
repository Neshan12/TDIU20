#include "catch.hpp"
#include "Time.h"
#include <sstream>

using namespace std;


TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }


   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }

}

TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   // Fill with extra corner cases!
}



TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
   }

   SECTION("24 hour format with argument")
   {
      CHECK( t0.to_string(true) == "00:00:00" );
      CHECK( t1.to_string(true) == "11:59:59" );
      CHECK( t2.to_string(true) == "12:00:00" );
      CHECK( t3.to_string(true) == "13:00:00" );
      CHECK( t4.to_string(true) == "23:59:59" );
   } 

   SECTION("12 hour format")
   {
      CHECK( t0.to_string(false) == "12:00:00 AM" );
      CHECK( t1.to_string(false) == "11:59:59 AM" );
      CHECK( t2.to_string(false) == "12:00:00 PM" );
      CHECK( t3.to_string(false) == "01:00:00 PM" );
      CHECK( t4.to_string(false) == "11:59:59 PM" );
   }
}

TEST_CASE ("Operators")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};

   SECTION("!=")
   {
      CHECK_NOTHROW( t0 = t1 );
      CHECK_NOTHROW( t2 = t3 );
      CHECK_FALSE( t0 != t1 );
      CHECK_FALSE( t2 != t3 );
      CHECK_FALSE( t4 != t4 );
   }

   SECTION("==")
   {
      CHECK_FALSE( t0 == t1 );
      CHECK_FALSE( t2 == t3 );
      CHECK_FALSE( t4 == t0 );
   }

   SECTION("<")
   {
      CHECK_NOTHROW( t0 < t0 );
      CHECK_FALSE( t1 < t0 );
      CHECK( t0 < t1 );
      CHECK( t0 < t4 );
      CHECK( t3 < t4 );
   }

   SECTION(">")
   {
      CHECK_NOTHROW( t0 > t0 );
      CHECK_FALSE( t0 > t1 );
      CHECK( t1 > t0 );
      CHECK( t4 > t0 );
      CHECK( t4 > t3 );
   }


   SECTION("++i")
   {
      CHECK_NOTHROW( ++t0 );
      CHECK( t0.to_string() == "00:00:01" );
      CHECK_NOTHROW( ++t1 );
      CHECK( t1.to_string() == "12:00:00" );
      CHECK_NOTHROW( ++t2 );
      CHECK( t2.to_string() == "12:00:01" );
      CHECK_NOTHROW( ++t3 );
      CHECK( t3.to_string() == "13:00:01" );
      CHECK_NOTHROW( ++t4 );
      CHECK( t4.to_string() == "00:00:00" );

      CHECK_NOTHROW( t3 = ++t4 );
      CHECK( t3.to_string() == "00:00:01" );
      CHECK( t4.to_string() == "00:00:01" );
   }

   SECTION("i++")
   {
      CHECK_NOTHROW( t0++ );
      CHECK( t0.to_string() == "00:00:01" );
      CHECK_NOTHROW( t1++ );
      CHECK( t1.to_string() == "12:00:00" );
      CHECK_NOTHROW( t2++ );
      CHECK( t2.to_string() == "12:00:01" );
      CHECK_NOTHROW( t3++ );
      CHECK( t3.to_string() == "13:00:01" );
      CHECK_NOTHROW( t4++ );
      CHECK( t4.to_string() == "00:00:00" );

      CHECK_NOTHROW( t3 = t4++ );
      CHECK( t3.to_string() == "00:00:00" );
      CHECK( t4.to_string() == "00:00:01" );
   }

   SECTION("--i")
   {
      CHECK_NOTHROW( --t0 );
      CHECK( t0.to_string() == "23:59:59" );
      CHECK_NOTHROW( --t1 );
      CHECK( t1.to_string() == "11:59:58" );
      CHECK_NOTHROW( --t2 );
      CHECK( t2.to_string() == "11:59:59" );
      CHECK_NOTHROW( --t3 );
      CHECK( t3.to_string() == "12:59:59" );
      CHECK_NOTHROW( --t4 );
      CHECK( t4.to_string() == "23:59:58" );

      CHECK_NOTHROW( t3 = --t4 );
      CHECK( t3.to_string() == "23:59:57" );
      CHECK( t4.to_string() == "23:59:57" );
   }

   SECTION("i--")
   {
      CHECK_NOTHROW( t0-- );
      CHECK( t0.to_string() == "23:59:59" );
      CHECK_NOTHROW( t1-- );
      CHECK( t1.to_string() == "11:59:58" );
      CHECK_NOTHROW( t2-- );
      CHECK( t2.to_string() == "11:59:59" );
      CHECK_NOTHROW (t3-- );
      CHECK( t3.to_string() == "12:59:59" );
      CHECK_NOTHROW( t4-- );
      CHECK( t4.to_string() == "23:59:58" );

      CHECK_NOTHROW(t3 = t4--);
      CHECK( t3.to_string() == "23:59:58" );
      CHECK( t4.to_string() == "23:59:57" );
   }

   SECTION("<=")
   {
      CHECK( t0 <= t1 );
      CHECK( t0 <= t4 );
      CHECK( t1 <= t3 );
      CHECK( t4 <= t4 );
   }

   SECTION(">=")
   {
      CHECK( t1 >= t0 );
      CHECK( t4 >= t0 );
      CHECK( t3 >= t1 );
      CHECK( t4 >= t4 );
   }

   SECTION("<<")
   {
      stringstream ss{};

      CHECK_NOTHROW( ss << t0 );
      CHECK( ss.str() == "00:00:00" );
      ss = {};

      CHECK_NOTHROW( ss << t1 );
      CHECK( ss.str() == "11:59:59" );
      ss = {};
      CHECK_NOTHROW( ss << t2 );
      CHECK( ss.str() == "12:00:00" );
      ss = {};

      CHECK_NOTHROW( ss << t3 );
      CHECK( ss.str() == "13:00:00" );
      ss = {};

      CHECK_NOTHROW( ss << t4 );
      CHECK( ss.str() == "23:59:59" );
      ss = {};

      CHECK_NOTHROW( ss << t0 << t1 << t2);
      CHECK( ss.str() == "00:00:0011:59:5912:00:00");
      ss = {};

      CHECK_NOTHROW( ss << t0 << ' ' << t1);
      CHECK( ss.str() == "00:00:00 11:59:59");
   }

   SECTION(">>")
   {
      istringstream is{"00:01:00"};
      t0 = {};
      is >> t0;

      CHECK( t0.to_string() == "00:01:00");

      CHECK_NOTHROW( t0 >> "10:00:00" );
      CHECK( t0.to_string() == "10:00:00" );

      CHECK_NOTHROW( t1 >> "00:00:00" );
      CHECK( t1.to_string() == "00:00:00" );

      CHECK_NOTHROW( t0 >> t1 );
      CHECK( t0.to_string() == "00:00:00" );


   }

   SECTION("+")
   {
      CHECK_NOTHROW( t0 = t0 + 10 );
      CHECK( t0.to_string() == "00:00:10" );

      CHECK_NOTHROW( t1 = t1 + 10 );
      CHECK( t1.to_string() == "12:00:09" );

      CHECK_NOTHROW( t4 = t4 +(-5) );
      CHECK( t4.to_string() == "23:59:54");

      CHECK_NOTHROW( t0 = 10 + t0 );
      CHECK( t0.to_string() == "00:00:20");
   }

   SECTION("+=")
   {
      t0 = {};

      CHECK_NOTHROW( t0 += 10 );
      CHECK( t0.to_string() == "00:00:10" );
   }

   SECTION("-");
   {
      t1 = {11, 59, 59};
      t3 = {13, 0, 0};

      CHECK_NOTHROW( t1 = (t1-5) );
      CHECK( t1.to_string() == "11:59:54");

      CHECK_NOTHROW( t3 = t3 -(-5) );
      CHECK( t3.to_string() == "13:00:05");
   }

   SECTION("-=");
   {
      t1 = {11, 59, 59};
      CHECK_NOTHROW( t1 -= 10 );
      CHECK( t1.to_string() == "11:59:49");

      t0 = {};
      CHECK_NOTHROW( t0 -= 20 );
      CHECK( t0.to_string() == "23:59:40" );
   }
}
