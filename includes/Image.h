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
    class Image;
    std::ostream& operator<<(std::ostream& out, const DBXMEL004::Image& rhs);
    std::istream& operator>>(std::istream& in, DBXMEL004::Image& rhs);

    typedef struct filter{
        int n; // the dimensions of the 2d array with values.
        float **filt;// this is the 2d array with the filter values
        filter();
        filter(const std::string& filename);// constructor to get the file name 
        float to_fraction(std::string arg); // method to convert the each string read into a fracion.
        ~filter();
    }filter;

    class Image {
    public:

        class iterator {
        private:
            unsigned char *ptr;
            // construct only via Image class (begin/end)
            iterator(unsigned char *p);
            friend class Image;
        public:
            unsigned char* getval();
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
        int getIndex(int row, int col)const;

        /**Image operators*/
        Image& operator+=(const Image& rhs);
        Image& operator-=(const Image& rhs);
        Image operator+(const Image& rhs);
        Image operator-(const Image& rhs);
        Image& operator!();
        Image& operator/(Image& rhs);
        Image& operator*(const int& f);
        Image operator%(filter& temp);
        /*Methods for the iterator*/
        iterator begin() const;
        iterator end() const;
        //        friend std::ostream& DBXMEL004::operator<<(std::ostream& out, const DBXMEL004::Image& rhs);
        //        friend std::istream& DBXMEL004::operator>>(std::istream& in, DBXMEL004::Image& rhs);

        void computer_header() {
            header = "P5\n" + comments + std::to_string(im_height) + " "
                    + std::to_string(im_width) + "\n" + "255\n";
        }

    private:
        int im_width, im_height;
        std::unique_ptr<unsigned char [] > image_data; //pointer holding the data for the image
        std::string comments = "# CREATOR: GIMP PNM Filter Version 1.1\n";
        std::string header = "P5\n" + comments + std::to_string(im_height) + " "
        + std::to_string(im_width) + "\n" + "255\n";
        friend std::ostream& DBXMEL004::operator<<(std::ostream& out, const DBXMEL004::Image& rhs);
        friend std::istream& DBXMEL004::operator>>(std::istream& in, DBXMEL004::Image& rhs);

    };
};
#endif /* IMAGE_H */

