/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#define CATCH_CONFIG_MAIN // his defines main
#include "../include/Image.h"
#include "../include/catch.hpp"
using namespace DBXMEL004;
using namespace std;
unsigned char arr [] = {12, 13, 14, 15, 16, 17};
unsigned char test_arr[12];

void init_arr() {
    for (int i = 0; i < 12; ++i) {
        arr[i] = i + 1;
    }
}
float a[3][3] = {
    {.25, .125, .25},
    {.25, .125, .25},
    {.25, .125, .25}
};

TEST_CASE("Testing the iterator") {
    Image im1(2, 3, arr);
    Image i;
    Image im2(im1);
    Image::iterator it1 = im1.begin();
    Image::iterator it2 = im2.end();
    REQUIRE(*it1 == arr[0]);
    REQUIRE(*it2 == arr[6]); // one past the last element is arr[6]  

    WHEN("You add a integer to an iterator") {
        Image::iterator temp_it = it1 + 3;

        THEN("original iterator should not be changed") {
            REQUIRE(*it1 == arr[0]);
            REQUIRE(*temp_it == arr[3]);
        }
    }

    SECTION("Post add is called or pre increment") {

        WHEN("Post fix is used") {
            Image::iterator temp_it = it1++;

            THEN("Returned value is not updated") {
                REQUIRE(temp_it != it1);
                REQUIRE(*temp_it == arr[0]);
                REQUIRE(*it1 == arr[1]);
            }
            it1 = im1.begin();
        }

        WHEN("prefix is used") {
            Image::iterator temp_it = ++it1;

            THEN("Returned value is equal to the incremented iterator") {
                REQUIRE(!(temp_it != it1));
                REQUIRE(*temp_it == arr[1]);
            }
        }
    }
}

TEST_CASE("Testing constructors and assignment operators") {
    Image im1(2, 3, arr);

    SECTION("Copy construct") {

        WHEN("Copy constructed") {
            Image im2(im1);

            THEN("The two images are now equal as a deep copy was done") {
                Image::iterator it1 = im1.begin();
                Image::iterator it2 = im2.begin();
                REQUIRE(*it1 == 12);
                REQUIRE(*it1 == *it2);
                REQUIRE(*(it1 + 3) == *(it2 + 3));
                REQUIRE(it2 != it1); // Check if deep copy was done hence 2 images are not stored in same memory
            }
        }
    }

    SECTION("Move constructor") {
        Image im3(im1); // COPY CONSTRUCTING im1 TO im3 SO WE CAN USE im3 here

        WHEN("Move constructed") {
            Image im4(move(im3));

            THEN("The new image has all contents from the previous") {
                bool contain_same = true;
                Image::iterator beg = im1.begin();
                Image::iterator im4_beg = im4.begin();
                Image::iterator end = im1.end();
                while (beg != end) { // to test if all items are transfered to the 
                    if (*(beg++) != *(im4_beg++)) {
                        contain_same = false;
                        break;
                    }
                }
                REQUIRE(contain_same);
            }

            THEN("The moved object is transfered over to this one") {
                Image::iterator beg = im3.begin();
                Image::iterator e = im3.end();
                REQUIRE(im3.get_image_size() == 0);
                REQUIRE(beg == e);
            }
        }
    }

    SECTION("Copy assignment") {

        WHEN("Copy assigned") {
            Image im2;
            im2 = im1;

            THEN("The two images are now equal as a deep copy was done") {
                Image::iterator it1 = im1.begin();
                Image::iterator it2 = im2.begin();
                REQUIRE(*it1 == 12);
                REQUIRE(*it1 == *it2);
                REQUIRE(*(it1 + 3) == *(it2 + 3));
                REQUIRE(it2 != it1); // Check if deep copy was done hence 2 images are not stored in same memory
            }
        }
    }

    SECTION("Move assigned") {
        Image im3(im1); // COPY CONSTRUCTING im1 TO im3 SO WE CAN USE im3 here

        WHEN("Move assigned") {
            Image im4;
            im4 = move(im3);

            THEN("The new image has all contents from the previous") {
                bool contain_same = true;
                Image::iterator beg = im1.begin();
                Image::iterator im4_beg = im4.begin();
                Image::iterator end = im1.end();
                while (beg != end) { // to test if all items are transfered to the 
                    if (*(beg++) != *(im4_beg++)) {
                        contain_same = false;
                        break;
                    }
                }
                REQUIRE(contain_same);
            }

            THEN("The moved object is transfered over to this one") {
                Image::iterator beg = im3.begin();
                Image::iterator e = im3.end();
                REQUIRE(im3.get_image_size() == 0);
                REQUIRE(beg == e);
            }
        }
    }
}

TEST_CASE("Image operators") {

    SECTION("Adding images") {
        Image image, image2;
    }
    SECTION("Subtracting images"){
        
    }
    SECTION("Inverting images"){
        
    }
    SECTION("Masking images"){
        
    }
    SECTION("Threshing images"){
        
    }
    SECTION("Filter images"){
        
    }
}