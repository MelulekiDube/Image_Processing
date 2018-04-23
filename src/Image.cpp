/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.cpp
 * Author: Meluleki
 * 
 * Created on April 18, 2018, 2:53 PM
 */

#include <fstream>
#include <sstream>
#include <string>
#include "../includes/Image.h"
using namespace std;
using namespace DBXMEL004;

/**
 * 
 */
Image::Image() : im_witdh(0), im_height(0), image_data(nullptr) {
}

/**
 * 
 * @param w
 * @param h
 */
Image::Image(const int w, const int h) : im_witdh(h), im_height(w), image_data(new unsigned char[w*h]) {
}

/**
 * Testing constructor
 * @param a
 * @param b
 * @param arr
 */
Image::Image(const int a, const int b, unsigned char arr[]) : im_witdh(a), im_height(b), image_data(new unsigned char [a*b]) {
    for (int i = 0; i < (a * b); ++i) {
        image_data[i] = arr[i];
    }
}

/**
 * Copy constructor
 * @param orig
 */
Image::Image(const Image& orig) : im_witdh(orig.im_witdh), im_height(orig.im_height), image_data(new unsigned char[im_height*im_witdh]) {
    /**Implement copying for the image using iterators*/
    copy(orig);
}

/**
 * Copy assignment
 * @param rhs
 * @return 
 */
Image& Image::operator=(const Image& rhs) {
    im_witdh = rhs.im_witdh;
    im_height = rhs.im_height;
    image_data.reset(new unsigned char[im_witdh * im_height]);
    copy(rhs);
    return *this;
}

/**
 * Move constructor
 * @param rhs
 */
Image::Image(Image&& rhs) : im_witdh(move(rhs.im_witdh)), im_height(move(rhs.im_height)), image_data(new unsigned char[im_height*im_witdh]) {
    copy(rhs);
    rhs.image_data.reset(nullptr);
}

/**
 * Move assignment
 * @param rhs
 * @return 
 */
Image& Image::operator=(Image&& rhs) {
    im_witdh = move(rhs.im_witdh);
    im_height = move(rhs.im_height);
    image_data.reset(new unsigned char[im_height * im_witdh]);
    copy(rhs);
    rhs.image_data.reset(nullptr);
    return *this;
}

/**
 * 
 */
Image::~Image() {
    //    if(image_data.get()) image_data.reset(nullptr);
}

void Image::copy(const Image& rhs) {
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = rhs.begin();
    Image::iterator it = inStart;
    while (beg != end) {
        *beg = *it;
        ++beg;
        ++it;
    }
}

Image::iterator Image::begin() const {
    //define iterator;
    iterator t(image_data.get());
    //assign it to unique_ptr<char[]>0
    return t;
} // etc

Image::iterator Image::end() const {
    iterator t(begin() +(get_image_size()));
    return t;
}

int Image::get_image_size() const {
    return im_height*im_witdh;
}

Image& Image::operator+=(const Image& rhs) {
    Image::iterator this_beg = this->begin(), this_end = this->end();
    Image::iterator rhs_beg = rhs.begin();
    while (this_beg != this_end) {
        *(this_beg++) += *(rhs_beg++);
    }
    return *this;
}

Image Image::operator+(const Image& rhs) {
    Image temp_image(*this);
    temp_image.operator+=(rhs);
    return temp_image;
}

Image& Image::operator-=(const Image& rhs) {
    Image::iterator this_beg = this->begin(), this_end = this->end();
    Image::iterator rhs_beg = rhs.begin();
    while (this_beg != this_end) {
        *(this_beg++) -= *(rhs_beg++);
    }
    return *this;
}

Image Image::operator-(const Image& rhs) {
    Image temp_image(*this);
    temp_image.operator-=(rhs);
    return temp_image;
}

Image& Image::operator/(Image& rhs) {
    Image::iterator this_beg = this->begin(), this_end = this->end();
    Image::iterator rhs_beg = rhs.begin();
    while (this_beg != this_end) {
        if (*rhs_beg == 255) {
            *(rhs_beg) = *this_beg;
        }
        ++rhs_beg;
        ++this_beg;
    }
    return rhs;
}

Image& Image::operator!() {
    Image::iterator beg = begin(), en = end();
    while (beg != en) {
        *(beg) = 255 - (*(beg++));
    }
    return *this;
}

Image& Image::operator*(const int& f) {
    Image::iterator beg = begin(), en = end();
    while (beg != en) {
        if (*beg > f) *(beg++) = 255;
        else *(beg++) = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Image& rhs) {
    return out;
}

std::istream& operator>>(std::istream& in, Image& rhs) {
    return in;
}

/**
 * 
 * @param imageName
 */
void Image::load_image(std::string imageName) {
    ifstream input_file;
    stringstream ss, ss1, ss2;
    ss1 << imageName << ".pgm";
    input_file.open(ss1.str(), ios::binary);
    string temp_string;
    bool comments_done = false;
    std::getline(input_file, temp_string);
    comments = "";
    while (!comments_done) {
        getline(input_file, temp_string);
        if (temp_string[0] != '#') {
            comments_done = true;
            break;
        } else {
            comments += temp_string + "\n";
        }
    }
    ss << temp_string;
    cout << ss.str() << endl;
    string temps1, temps2;
    istringstream fss(ss.str());
    fss >> temps1 >> ws>>temps2;
    *this = Image(stoi(temps1), stoi(temps2));
    getline(input_file, temp_string);
    image_data.reset(new unsigned char[get_image_size()]);
    Image::iterator beg = begin();
    Image::iterator en = end();
    while (beg != en) {
        //        unsigned char c;
        *(beg++) = input_file.get();
    }
    input_file.close();
}

/**
 * method to save the image into a file
 * @param imageName
 */
void Image::save_image(string imageName) {
    ofstream out_file;
    stringstream ss;
    ss << imageName << ".pgm";
    out_file.open(ss.str(), ios::binary | ios::out | ios::trunc);
    computer_header();
    out_file << header;
    Image::iterator beg = begin();
    Image::iterator en = end();
    while (beg != en) {
        //        unsigned char c;
        out_file << *(beg++);
    }
    out_file.close();
}
