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
        REQUIRE(beg!=end);
    }

    SECTION("Copy assignment") {

    }

    SECTION("Move assignment") {

    }
}

TEST_CASE("load image"){
    Image image, image2;
    image2.load_image("res/Lenna_standard");
    image=image2*100;
    image.save_image("res/mask_result");
}
