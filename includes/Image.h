/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.h
 * Author: Meluleki
 *
 * Created on April 18, 2018, 2:53 PM
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <iostream>
#include <string>

namespace DBXMEL004 {

    class Image {
    public:

        class iterator {
        private:
            unsigned char *ptr;
            // construct only via Image class (begin/end)
        public:
            unsigned char* getval();
            iterator(unsigned char *p);
            iterator(const iterator & rhs);
            // define overloaded ops: *, ++, --, =
            iterator& operator=(const iterator & rhs);
            // other methods for iterator
            unsigned char& operator*(void) const;
            iterator& operator++();
            iterator operator++(int);
            iterator& operator+(const int &rhs);
            iterator& operator--();
            iterator operator--(int);
            iterator& operator-(const int &rhs);
            bool operator!=(const iterator& rhs) const;
        };
        Image(); // Default constructor
        Image(const int w, const int h);
        Image(const int a, const int b, unsigned char arr[]);
        Image(const Image& orig); //Copy constructor
        Image(Image&& rhs); //Move constructor
        Image& operator=(const Image& rhs); // Copy assignment
        Image& operator=(Image&& rhs); //Move assignment
        void copy(const Image& rhs);
        void save_image(std::string imageName); // saving image
        void load_image(std::string imageName); //loading the image
        virtual ~Image(); // Destructor
        int get_image_size() const;

        /**Image operators*/
        Image& operator+=(const Image& rhs);
        Image& operator-=(const Image& rhs);
        Image operator+(const Image& rhs);
        Image operator-(const Image& rhs);
        Image& operator!();
        Image& operator/(Image& rhs);
        Image& operator*(const int& f);

        /*Methods for the iterator*/
        iterator begin() const;
        iterator end() const;

    private:
        int im_witdh, im_height;
        std::unique_ptr<unsigned char [] > image_data; //pointer holding the data for the image
        std::string comments = "# CREATOR: GIMP PNM Filter Version 1.1\n";
        std::string header = "P5\n" + comments + std::to_string(im_height) + " "
        + std::to_string(im_witdh) + "\n" + "255\n";

        void computer_header() {
            header = "P5\n" + comments + std::to_string(im_height) + " "
                    + std::to_string(im_witdh) + "\n" + "255\n";
        }
        friend std::ostream& operator<<(std::ostream& out, const Image& rhs);
        friend std::istream& operator>>(std::istream& in, Image& rhs);

    };
};
#endif /* IMAGE_H */

