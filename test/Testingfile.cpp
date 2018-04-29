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
unsigned char arr2 [] = {255, 55, 0, 10, 255, 100};
unsigned char arr2_thresh [] = {255, 0, 0, 0, 255, 25};
unsigned char test_arr[12];
unsigned char arr_1[12];

void init_arr() {
    for (int i = 0; i < 12; ++i) {
        arr[i] = i + 1;
        arr_1[i] = (12 - i);
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
    REQUIRE(*it2 != arr[5]);

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
    Image image(3, 4, test_arr), image2(3, 4, arr_1);

    SECTION("Adding images") {
        vector<unsigned char> expected_results; // vector to be used to test the add operator
        int count = 0;
        Image::iterator beg1 = image.begin(), beg2 = image2.begin();
        while (count < 10) {
            int temp_result = (*beg1++)+ (*beg2++);
            expected_results.push_back((unsigned char) (temp_result > 255 ? 255 : temp_result));
            ++count;
        }
        count = 0;
        bool add_true = true;
        Image result = image + image2;
        Image::iterator it = result.begin();
        while (count < 10) {
            if ((*it++) != expected_results[count]) {
                add_true = false;
                break;
            }
            ++count;
        }
        REQUIRE(add_true);
    }

    SECTION("Subtracting images") {
        vector<unsigned char> expected_results; // vector to be used to test the add operator
        int count = 0;
        Image::iterator beg1 = image.begin(), beg2 = image2.begin();
        while (count < 10) {
            unsigned char temp_result = (*beg1++)- (*beg2++);
            expected_results.push_back(temp_result);
            ++count;
        }
        count = 0;
        bool add_true = true;
        Image result = image - image2;
        Image::iterator it = result.begin();
        while (count < 10) {
            if ((*it++) != expected_results[count]) {
                add_true = false;
                break;
            }
            ++count;
        }
        REQUIRE(add_true);
    }

    SECTION("Inverting images") {
        Image i(2, 3, arr2);
        Image t = !i;
        Image::iterator it = t.begin();
        REQUIRE(*it++ == (255 - arr2[0]));
        REQUIRE(*it++ == (255 - arr2[1]));
        REQUIRE(*it == (255 - arr2[2]));
    }

    SECTION("Masking images") {
        Image im1(2, 3, arr);
        Image im2(2, 3, arr2);
        Image result = im1 / im2;
        Image::iterator it = result.begin();
        REQUIRE(*it == arr[0]);
        it = it + 4;
        REQUIRE(*it == arr[4]);
    }

    SECTION("Threshing images") {
        Image im1(2, 3, arr);
        Image result = im1 * 60;
        int count = 0;
        Image::iterator it = result.begin();
        bool changed = true;
        while (count) {
            if ((*it++) == arr2_thresh[count]) {
                changed = false;
                break;
            }
            ++count;
        }
        REQUIRE(changed);
    }
}