/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Meluleki
 *
 * Created on April 18, 2018, 2:52 PM
 */

#include <cstdlib>
#include <map>
#include "../include/Image.h"

//Definition for the different operations.
#define add "-a"
#define sub "-s"
#define invert "-i"
#define mask "-l"
#define thresh "-t"
#define filt "-f"

//End of definitions.

using namespace std;
using namespace DBXMEL004;

map<string, int> options; //map to hold the different options and represent them as ints to allow to use switch cases

/**
 * method to populate the menu
 */
void populate_options() {
    options.insert(make_pair(add, 0));
    options.insert(make_pair(sub, 1));
    options.insert(make_pair(invert, 2));
    options.insert(make_pair(mask, 3));
    options.insert(make_pair(thresh, 4));
    options.insert(make_pair(filt, 5));
}

/*
 * main method
 */
int main(int argc, char*const argv[]) {
    populate_options();
    cout << "Welcome the parameters are being processed" << endl;
    Image i1, i2, result; // these are variable that will be reused
    switch (options[argv[1]]) {
        case (0): // this means if we are to add to images, i.e. the option selected is -a
        {
            cout << "Selected option is add. Loading the images now" << endl;
            i1.load_image(argv[2]);
            i2.load_image(argv[3]);
            cout << "Adding the two images together" << endl;
            result = i1 + i2;
            break;
        }
        case (1):
        {
            cout << "Selected option is subtract. Loading the images now" << endl;
            i1.load_image(argv[2]);
            i2.load_image(argv[3]);
            cout << "Subtracting the two images from each other" << endl;
            result = i1 - i2;
            break;
        }
        case (2):
        {
            cout << "Selected option is inver. Now loading the image" << endl;
            i1.load_image(argv[2]);
            cout << "Now inverting the image" << endl;
            result = !i1;
            break;
        }
        case (3):
        {
            cout << "Selected option is mask. Loading the images now" << endl;
            i1.load_image(argv[2]);
            i2.load_image(argv[3]);
            cout << "Now masking the image1 with image2" << endl;
            result = i1 / i2;
            break;
        }
        case (4):
        {
            cout << "Selected option is thresh. Loading the image now" << endl;
            i1.load_image(argv[2]);
            int th = stoi(argv[3]);
            cout << "Now applying the threshold to image" << endl;
            result = i1*th;
            break;
        }
        case (5):
        {
            cout << "Selected option is filter. Loading the image now" << endl;
            i1.load_image(argv[2]);
            filter g(argv[3]);
            result = i1 % g;
            break;
        }
    }
    cout << "Saving the result to the out file" << endl;
    result.save_image(argv[argc - 1]);
    cout << "Operation done! Check the result in the output file\nGoodbye!!!!!" << endl;
    return 0;
}

