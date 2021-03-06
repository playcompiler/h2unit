#include "h2unit.h"
#include <stdlib.h>

extern "C" {
#include "demo_clanguage.h"
}


H2UNIT(getEven)
{
};

H2CASE(getEven, "getEvent with odd value")
{
   H2EQ_MATH(4, getEven(7));
}

H2CASE(getEven, "getEven with even value")
{
   H2EQ_MATH(6, getEven(6));
   H2NE_MATH(6, getEven(6));
}

H2UNIT_CASE("different type math")
{
   unsigned char e_unsigned_char = 2;
   unsigned char a_unsigned_char = 2;
   H2EQ_MATH(e_unsigned_char, a_unsigned_char);

   char e_char = 2;
   char a_char = 2;
   H2EQ_MATH(e_char, a_char);

   short e_short = 2;
   short a_short = 2;
   H2EQ_MATH(e_short, a_short);

   unsigned short e_unsigned_short = 2;
   unsigned short a_unsigned_short = 2;
   H2EQ_MATH(e_unsigned_short, a_unsigned_short);

   long e_int = 2;
   long a_int = 2;
   H2EQ_MATH(e_int, a_int);

   unsigned long e_unsigned_int = 2;
   unsigned long a_unsigned_int = 2;
   H2EQ_MATH(e_unsigned_int, a_unsigned_int);

   long e_long = 2;
   long a_long = 2;
   H2EQ_MATH(e_long, a_long);

   unsigned long e_unsigned_long = 2;
   unsigned long a_unsigned_long = 2;
   H2EQ_MATH(e_unsigned_long, a_unsigned_long);

   unsigned long long e_unsigned_long_long = 0x12345678900ULL;
   unsigned long long a_unsigned_long_long = 0x12345678900ULL;
   H2EQ_MATH(e_unsigned_long_long, a_unsigned_long_long);

   long long e_long_long = 0x1234567890LL;
   long long a_long_long = 0x1234567890LL;
   H2EQ_MATH(e_long_long, a_long_long);

   char * e_char_pointer = (char*) 0;
   char * a_char_pointer = (char*) 0;
   H2EQ_MATH(e_char_pointer, a_char_pointer);

   int * e_int_pointer = (int*) 0;
   int * a_int_pointer = (int*) 0;
   H2EQ_MATH(e_int_pointer, a_int_pointer);

   double * e_double_pointer = (double*) 0;
   double * a_double_pointer = (double*) 0;
   H2EQ_MATH(e_double_pointer, a_double_pointer);

   void * e_void_pointer = (void*) 0x12345678;
   void * a_void_pointer = (void*) 0x12345678;
   H2EQ_MATH(e_void_pointer, a_void_pointer);

   enum {
      EE_A1 = 1,
      EE_B2,
      EE_C3,
      EE_D4
   };

   H2EQ_MATH(2, EE_B2);
   H2EQ_MATH(EE_D4, 4);
}

H2UNIT(getCeil)
{
   /*
    * setup() and teardown() can be omitted. The default is doing nothing
    */
};

H2CASE(getCeil, "test for float type number")
{
   H2EQ_MATH(6.0, getCeil(6.2));
   H2EQ_MATH(6.0, getCeil(6.4));
   H2EQ_MATH(3.14159, 2.34159);
}

H2CASE(getCeil, "test for number in range")
{
   H2EQ_RANGE(6, 7, getCeil(6.8));
   H2EQ_RANGE(7, 8, getCeil(6.8));
}

H2CASE(getCeil, "test for number not in range")
{
   H2NE_RANGE(7, 8, getCeil(6.8));
   H2NE_RANGE(6, 7, getCeil(6.8));
}

H2CASE(getCeil, "test for number in set")
{
   double t[] = {
      1.0, 2.0, 3.0
   };
   H2EQ_INSET(t, 3, getCeil(2.8));
   H2EQ_INSET(t, 3, getCeil(6.8));
}

H2CASE(getCeil, "test for number not in set")
{
   double t[] = {
      1.0, 2.0, 3.0
   };
   H2NE_INSET(t, 3, getCeil(6.8));
   H2NE_INSET(t, 3, getCeil(2.8));
}

H2UNIT(Point)
{
};

/*
 * h2unit H2EQ_STRCMP can be used to verify Case sensitive String.
 */
H2CASE(Point, "string equal")
{
   Point p1 = {0, 0};
   H2EQ_STRCMP("Point(0, 0)", Point_toString(&p1));
   Point p2 = {1, 2};
   H2EQ_STRCMP("Point(1, 3)", Point_toString(&p2));
}
/*
 * h2unit H2NE_STRCMP can be used to verify Case sensitive String.
 */
H2CASE(Point, "string not equal")
{
   Point p1 = {0, 0};
   H2NE_STRCMP("Point(1, 0)", Point_toString(&p1));
   Point p2 = {1, 2};
   H2NE_STRCMP("Point(1, 2)", Point_toString(&p2));
}

/*
 * h2unit H2EQ_WILDCARD can be used to verify string by WildCard. support:
 *  -- ? any one char
 *  -- * any char(s)
 *  -- [] specified char(s)
 *     -- [abc] a or b or c
 *     -- [a-z] a or b or ... or z
 *     -- [!abc] any char except a and b and c
 *     -- [^abc] any char except a and b and c
 */
H2CASE(Point, "wildcard string")
{
   Point p1 = {0, 0};
   H2EQ_WILDCARD("Point(0, ?)", Point_toString(&p1));
   Point p2 = {1, 2};
   H2EQ_WILDCARD("Point(*)", Point_toString(&p2));
   Point p3 = {3, 4};
   H2EQ_WILDCARD("Point([123], [0-9])", Point_toString(&p3));
   Point p4 = {6, 12};
   H2EQ_WILDCARD("Point([!a-zA-Z], [^a-z][^a-z])", Point_toString(&p4));

   H2EQ_WILDCARD("Point\\*Point\\?\\[1,2\\]", "Point*Point?[1,2]");
}

/*
 * h2unit H2EQ_REGEX can be used to verify string by Regular express. support:
 *    (?i)    Must be at the beginning of the regex. Makes match case-insensitive
 *    ^       Match beginning of a buffer
 *    $       Match end of a buffer
 *    ()      Grouping and substring capturing
 *    \s      Match whitespace
 *    \S      Match non-whitespace
 *    \d      Match decimal digit
 *    \n      Match new line character
 *    \r      Match line feed character
 *    \f      Match form feed character
 *    \v      Match vertical tab character
 *    \t      Match horizontal tab character
 *    \b      Match backspace character
 *    +       Match one or more times (greedy)
 *    +?      Match one or more times (non-greedy)
 *    *       Match zero or more times (greedy)
 *    *?      Match zero or more times (non-greedy)
 *    ?       Match zero or once (non-greedy)
 *    x|y     Match x or y (alternation operator)
 *    \meta   Match one of the meta character: ^$().[]*+?|\
 *    \xHH    Match byte with hex value 0xHH, e.g. \x4a
 *    [...]   Match any character from set. Ranges like [a-z] are supported
 *    [^...]  Match any character but ones from set
 */
H2CASE(Point, "regex string")
{
   Point p1 = {0, 0};
   H2EQ_REGEX("Point\\(0, 0\\)", Point_toString(&p1));
   Point p2 = {1, 2};
   H2EQ_REGEX("Point\\(.", Point_toString(&p2));
   Point p3 = {3, 4};
   H2EQ_REGEX("Point\\(.*\\)", Point_toString(&p3));
   Point p4 = {5, 6};
   H2EQ_REGEX("^Point\\(.*\\)$", Point_toString(&p4));
   Point p5 = {7, 8};
   H2EQ_REGEX("Point\\([789], [0-9]\\)", Point_toString(&p5));
   Point p6 = {11, 88};
   H2EQ_REGEX("Point\\([0-9]*, [^0-5]*\\)", Point_toString(&p6));
   Point p7 = {11, 88};
   H2EQ_REGEX("Point\\([0-9]+, [0-9]+\\)", Point_toString(&p7));
}

H2CASE(Point, "json")
{
   Point p1 = {0, 0};
   H2EQ_JSON("{'x': 0, 'y': 0}", Point_tojson(&p1));

   Point p2 = {0, 1};
   H2EQ_JSON("{'x': 0, 'y': [{}]}", Point_tojson(&p2));
}

H2CASE(Point, "json 2")
{
   H2EQ_JSON("{'x': 0, 'y': /he*/}", "{'x': 0, 'y': 'he110'}");
   H2EQ_JSON("{'x': 0, 'y': /he[4-9]+/}", "{'x': 0, 'y': 'he110'}");
}

/*
 * Case-Less strcmp
 */

H2CASE(Point, "caseless string equal")
{
   Point p1 = {0, 0};
   H2EQ_STRCMP_NOCASE("point(0, 0)", Point_toString(&p1));
   Point p2 = {1, 2};
   H2EQ_STRCMP_NOCASE("POINT(1, 2)", Point_toString(&p2));
}

/*
 * h2unit H2EQ_MEMCMP can be used to verify memory block.
 */
H2CASE(Point, "memory equal")
{
   Point p1 = {0, 0};
   H2EQ_MEMCMP("Point(0, 0)", Point_toString(&p1), sizeof("Point(0, 0)"));
   H2EQ_MEMCMP("Point(1, 0)", Point_toString(&p1), sizeof("Point(1, 0)"));
}




