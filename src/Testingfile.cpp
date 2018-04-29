/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#define CATCH_CONFIG_MAIN // his defines main
#include "../includes/Image.h"
#include "../includes/catch.hpp"
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
TEST_CASE("Test operators for the iterator"){
    
}
TEST_CASE("Testing the iterator") {
    Image im1(2, 3, arr);
    Image i;
    Image im2(im1);
    Image::iterator it1 = im1.begin();
    Image::iterator it2 = im2.begin();
    REQUIRE(*it1 == 12);
    REQUIRE(*it1 == *it2);
    REQUIRE(*(it1 + 3) == *(it2 + 3));
}

TEST_CASE("Testing constructors and assignment operators") {
    Image im1(2, 3, arr);
    Image im2(im1);

    SECTION("Copy construct") {
        Image::iterator it1 = im1.begin();
        Image::iterator it2 = im2.begin();
        REQUIRE(*it1 == 12);
        REQUIRE(*it1 == *it2);
        REQUIRE(*(it1 + 3) == *(it2 + 3));
    }

    SECTION("Move constructor") {
        Image im3(im1);
        Image im4(move(im3));
        Image::iterator beg = im1.begin();
        Image::iterator end = im1.end();
        REQUIRE(beg != end);
    }

    SECTION("Copy assignment") {

    }

    SECTION("Move assignment") {

    }
}

TEST_CASE("load image") {
    Image image, image2;
    filter g("filter.txt");
    image2.load_image("res/Lenna_standard");
    image = image2 % g;
    image.save_image("res/resu");
}
