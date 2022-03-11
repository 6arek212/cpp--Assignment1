/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Gilad Livshitz
 * 
 * Date: 2022-03-07
 */

#include "doctest.h"
#include "mat.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string gl_nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

/**
 * @brief generates a random number between the range of [min, max]
 * 
 * @param min 
 * @param max 
 * @return int the random number
 */
int rand_range(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}

TEST_CASE("Good input")
{
    
	CHECK(gl_nospaces(mat(1, 15, '@', '-')) == gl_nospaces("@\n@\n@\n@\n@\n@\n@\n@\n@\n@\n@\n@\n@\n@\n@"));
    
    CHECK(gl_nospaces(mat(17, 5, '&', '*')) == gl_nospaces("&&&&&&&&&&&&&&&&&\n"
                                                     "&***************&\n"
                                                     "&*&&&&&&&&&&&&&*&\n"
                                                     "&***************&\n"
                                                     "&&&&&&&&&&&&&&&&&"));
    
    CHECK(gl_nospaces(mat(13, 11, '+', '-')) == gl_nospaces("+++++++++++++\n"
                                                      "+-----------+\n"
                                                      "+-+++++++++-+\n"
                                                      "+-+-------+-+\n"
                                                      "+-+-+++++-+-+\n"
                                                      "+-+-+---+-+-+\n"
                                                      "+-+-+++++-+-+\n"
                                                      "+-+-------+-+\n"
                                                      "+-+++++++++-+\n"
                                                      "+-----------+\n"
                                                      "+++++++++++++"));
    
    CHECK(gl_nospaces(mat(9, 9, 'G', 'L')) == gl_nospaces("GGGGGGGGG\n"
                                                    "GLLLLLLLG\n"
                                                    "GLGGGGGLG\n"
                                                    "GLGLLLGLG\n"
                                                    "GLGLGLGLG\n"
                                                    "GLGLLLGLG\n"
                                                    "GLGGGGGLG\n"
                                                    "GLLLLLLLG\n"
                                                    "GGGGGGGGG"));
}

TEST_CASE("Good Letters")
{
    string str_format = "\t\t\t\t\t\t\t\t\t\n"      // this is the sample of 7x9
                        "\t\r\r\r\r\r\r\r\t\n"      // the letters are the ones who won't be good for the input
                        "\t\r\t\t\t\t\t\r\t\n"      // that why i chose them
                        "\t\r\t\r\r\r\t\r\t\n"
                        "\t\r\t\t\t\t\t\r\t\n"
                        "\t\r\r\r\r\r\r\r\t\n"
                        "\t\t\t\t\t\t\t\t\t";       // i took the regular case and then i changed to the letters
    
    string test;
    
    // according to the ascii table
    // the range of every the good letters (printable) are from 33-126

    srand(time(nullptr));       // setting the random by clock
    char a = '\0', b = '\0';
    

    for (int i = 0; i < 5; i++)
    {
        a = rand_range(33, 126);        // generates a random char from the good range
        
        for (int j = 0; j < 5; j++)
        {
            b = rand_range(33, 126);    // generates a random char from the good range
            
            test = str_format;
            replace(test.begin(), test.end(), '\t', a);     // replace the char '\t' with the good char a
            replace(test.begin(), test.end(), '\r', b);     // replace the char '\t' with the good char b
            
            CHECK(gl_nospaces(mat(9, 7, a, b)) == gl_nospaces(test));
        }

        replace(test.begin(), test.end(), b, a);     // make that the letter will be the same    
        CHECK(gl_nospaces(mat(9, 7, a, a)) == gl_nospaces(test));
    }

}

TEST_CASE("Bad numbers")
{
	CHECK_THROWS(mat(1, 2, '@', '-'));          // right is even
    CHECK_THROWS(mat(4, 5, '&', '*'));          // left is even
    CHECK_THROWS(mat(122, 144, '=', '^'));      // both are even
    
    CHECK_THROWS(mat(-1, 3, '@', '-'));         // right is negative
    CHECK_THROWS(mat(4, -5, '&', '*'));         // left is negative
    CHECK_THROWS(mat(-122, -144, '=', '^'));    // both are negative
    CHECK_THROWS(mat(-11, -13, '=', '^'));      // both are negative

    CHECK_THROWS(mat(0, 3, '+', '-'));          // right is 0
    CHECK_THROWS(mat(4, 0, '/', '*'));          // left is 0
    CHECK_THROWS(mat(0, 0, '#', '%'));          // both are 0
    CHECK_THROWS(mat(-2, 0, 'G', 'L'));         // both are 0
}

TEST_CASE("Bad Letters")
{
    // the range of every the good letters (printable) are from 33-126
    // it means that (< 33) or (126 <) are the bad letters
    char a = '\0', b = '\0';
    for (int i = -150; i < 256; i++)
    {
        if (i < 33 || 126 < i)
        {
            a = i;
            for (int j = -64; j < 256; j++)
            {
                if (j < 33 || 126 < j)
                {
                    b = j;
                    CHECK_THROWS(mat(9, 7, a, b));
                }
            }
        }
    }

}
