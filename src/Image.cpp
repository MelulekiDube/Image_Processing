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
 * Default constructor
 */
Image::Image() : im_width(0), im_height(0), image_data(nullptr) {
}

/**
 * Constructor that creates an image given width and height
 * Constructed image has nothing
 * @param w the width of the image
 * @param h the height of the image
 */
Image::Image(const int w, const int h) : im_width(h), im_height(w), image_data(new unsigned char[w*h]) {
}

/**
 * Testing constructor
 * @param w the width of the image
 * @param h the height of the image
 * @param arr a 2d array to assign to image_data
 */
Image::Image(const int w, const int h, unsigned char arr[]) : im_width(w), im_height(h), image_data(new unsigned char [w*h]) {
    for (int i = 0; i < (w * h); ++i) {
        image_data[i] = arr[i];
    }
}

/**
 * Copy constructor
 * @param orig
 */
Image::Image(const Image& orig) : im_width(orig.im_width), im_height(orig.im_height), image_data(new unsigned char[im_height*im_width]) {
    /**Implement copying for the image using iterators*/
    copy(orig);
}

/**
 * Copy assignment
 * @param rhs the lvalue reference that this is going to be assigned to
 * @return this object
 */
Image& Image::operator=(const Image& rhs) {
    im_width = rhs.im_width;
    im_height = rhs.im_height;
    image_data.reset(new unsigned char[im_width * im_height]);
    copy(rhs);
    return *this;
}

/**
 * Move constructor
 * @param rhs rvalue reference that is used to construct this object
 */
Image::Image(Image&& rhs) : im_width(move(rhs.im_width)), im_height(move(rhs.im_height)), image_data(new unsigned char[im_height*im_width]) {
    copy(rhs);
    rhs.image_data.reset(nullptr);
}

/**
 * Move assignment
 * @param rhs the rvalue reference that is to be assigned to this object
 * @return this object
 */
Image& Image::operator=(Image&& rhs) {
    im_width = move(rhs.im_width);
    im_height = move(rhs.im_height);
    image_data.reset(new unsigned char[im_height * im_width]);
    copy(rhs);
    rhs.image_data.reset(nullptr);
    return *this;
}

/**
 * Destructor of the Image class
 */
Image::~Image() {
    if (image_data.get()) {
        image_data.reset(nullptr);
    }
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
    return im_height*im_width;
}

int Image::getIndex(int col, int row) const {
    /*if col is less than 0 and row is greater or equal to zero*/
    if (col < 0 && row >= 0) {
        col = -(col) - 1;
    }
    /*If both are less than zero*/
    if (col < 0 && row < 0) {
        row = -(row) - 1;
        col = -(col) - 1;
    }
    /*col is now greater or equal to zero and row is less than zero*/
    if (col >= 0 && row < 0) {
        row = -(row) - 1;
    }
    /*If col is greater than the index and row is fine*/
    if (col >= im_width && row < im_height) {
        col = (2 * im_width) - col - 1;
    }
    /*If row is now greater than height*/
    if (col < im_width && row >= im_height) {
        /*2*width-col-1*/
        row = (2 * im_height) - row - 1;
    }
    /*if they are both out of bounds*/
    if (col >= im_width && row >= im_height) {
        row = (2 * im_height) - row - 1;
        col = (2 * im_width) - col - 1;
    }
    return ((row * im_width) + col);
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

Image Image::operator%(filter& temp) {
    Image result(im_width, im_height);
    int median = (temp.n - 1) / 2;
    int k = 0, m = 0;
    for (int y = 0; y < im_height; ++y) {
        for (int x = 0; x < im_width; ++x) {
            float res = 0;
            for (int i = 0; i < temp.n; ++i) {
                for (int j = 0; j < temp.n; ++j) {
                    k = x - median, m = y - median;
                    res += image_data.get()[getIndex(k++, m)] * temp.filt[i][j];
                }
                k = x;
                ++m;
            }
            int index = result.getIndex(x, y);
            iterator resit = result.begin() + index;
            *resit = (unsigned char) res;
        }
    }
    return result;
}

ostream& DBXMEL004::operator<<(ostream& out, const Image& rhs) {
    out << rhs.header;
    Image::iterator beg = rhs.begin();
    Image::iterator en = rhs.end();
    while (beg != en) {
        //        unsigned char c;
        out << *(beg++);
    }
    return out;
}

istream& DBXMEL004::operator>>(istream& in, Image& rhs) {
    string temp_string;
    bool comments_done = false;
    std::getline(in, temp_string);
    string comments = "";
    stringstream ss;
    while (!comments_done) {
        getline(in, temp_string);
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
    rhs = Image(stoi(temps1), stoi(temps2));
    getline(in, temp_string);
    rhs.image_data.reset(new unsigned char[rhs.get_image_size()]);
    Image::iterator beg = rhs.begin();
    Image::iterator en = rhs.end();
    while (beg != en) {
        //        unsigned char c;
        *(beg++) = in.get();
    }
    rhs.computer_header();
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
    if (input_file.is_open())
        input_file >> (*this);
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
    out_file << (*this);
    out_file.close();
}