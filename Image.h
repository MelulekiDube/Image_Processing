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


namespace DBXMEL004 {

    class Image {
    public:

        class iterator {
        private:
            unsigned char *ptr;
            // construct only via Image class (begin/end)
        public:
            iterator(unsigned char *p);
            iterator(const iterator & rhs);
            // define overloaded ops: *, ++, --, =
            iterator& operator=(const iterator & rhs);
            // other methods for iterator
            iterator& operator*(void) const;
            iterator& operator++();
            iterator& operator++(int);
            iterator& operator+(const int &rhs);
            iterator& operator--();
            iterator& operator--(int);
            iterator& operator-(const int &rhs);
        };
        Image(); // Default constructor
        Image(const Image& orig); //Copy constructor
        Image(Image&& rhs); //Move constructor
        Image& operator=(const Image& rhs); // Copy assignment
        Image& operator=(Image&& rhs); //Move assignment
        void saveImage(void); // saving image
        void loadImage(std::string imageName); //loading the image
        virtual ~Image(); // Destructor

        // public member declaration
        // define begin()/end() to get iterator to start and
        // "one-past" end.  

        iterator begin(void) {
            //define iterator;
            iterator t(image_data.get());
            //assign it to unique_ptr<char[]>0
            return t;
        } // etc

        iterator end(void) {
            iterator t(begin() +(im_witdh * im_height));
            return t;
        }
    private:
        int im_witdh, im_height;
        std::unique_ptr<unsigned char [] > image_data; //pointer holding the data for the image
    };
};
#endif /* IMAGE_H */

