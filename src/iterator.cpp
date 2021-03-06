/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <cstdlib>
#include "../include/Image.h"

using namespace std;
using namespace DBXMEL004;

/**
 * 
 * @param p
 */
Image::iterator::iterator(unsigned char* p) : ptr(p) {
}

/**
 * 
 * @param rhs
 */
Image::iterator::iterator(const iterator& rhs) : ptr(rhs.ptr) {
}

/**
 * 
 * @param rhs
 * @return 
 */
Image::iterator& Image::iterator::operator=(const iterator& rhs) {
    this->ptr = rhs.ptr;
    return *this;
}

/**
 * 
 * @return 
 */
unsigned char& Image::iterator::operator*() const {
    return *(this->ptr); //dereference what the pointer is pointing to
}

Image::iterator& Image::iterator::operator++() {
    this->ptr += 1; //increment current item
    return *this; // return the new value
}

Image::iterator Image::iterator::operator++(int) {
    iterator temp(*this); // save the value that will be returning
    operator++(); //post increment
    return temp; // return value before iteration
}

Image::iterator Image::iterator::operator+(const int& rhs) {
    iterator temp(*this); // create a temporary iterator object using this iterator object
    temp.ptr += rhs; // add to it
    return temp; // return the temp object by value to avoid hanging references.
}

Image::iterator Image::iterator::operator-(const int& rhs) {
    iterator temp(*this); // create a temporary iterator object using this iterator object
    temp.ptr -= rhs; // subtract from it
    return temp; // return the temp object by value to avoid hanging references.
}

Image::iterator& Image::iterator::operator--() {
    this->ptr -= 1;
    return *this;
}

Image::iterator Image::iterator::operator--(int) {
    iterator temp(*this);
    operator--();
    return temp;
}

bool Image::iterator::operator!=(const iterator& rhs) const {
    return this->ptr != rhs.ptr;
}

bool Image::iterator::operator==(const iterator& rhs) const {
    return this->ptr == rhs.ptr;
}

unsigned char* Image::iterator::getval() {
    return this->ptr;
}


