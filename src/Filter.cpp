/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../includes/Image.h"
#include <sstream>
#include <fstream>
using namespace DBXMEL004;
using namespace std;

/**
 * Constructor to create a filter from a given file.
 * @param fileName
 */
filter::filter(const string& fileName) {
    ifstream in;
    in.open(fileName);
    if(!in.is_open()){
        cout<<"The file either does nor exist or has permission problems"<<endl;
        return;
    }
    in>>n;
    filt = new float*[n];
    for (int i = 0; i < n; ++i) {
        float *row = new float[n];// create a new array that float[i] will be pointing to.
        filt[i] = row;
        for (int j = 0; j < n; ++j) {
            string temp;
            in>>temp;
            row[j] = to_fraction(temp);// first convert the string to a float and then place it in the filt array
        }
    }
    in.close();
}
filter::filter() : filt(nullptr) {
}
filter::~filter(){
    for (int i = 0; i < n; ++i) {
        delete [] filt[i];
    }
    delete []filt;
}

/**
 * The method to convert an string representation of a fraction into an actual fraction
 * @param arg this is the string in for of "1/4" that needs to be converted to a float
 * @return the float representation of that string.
 */
float filter::to_fraction(std::string arg) {
    istringstream ss(arg);
    string num_temp, dem_temp;// temporary string to hold the numerator and denominator
    char temp = ss.get();
    bool past_sign = false;
    while (!ss.eof()) { // while there is still something in the string stream
        if (!past_sign) {
            if (temp == '/') past_sign = true; //so after we get the character '/' we discard it and start filling in the denominator string
            else num_temp += temp;
        } else {
            dem_temp += temp;
        }
        temp = ss.get();
    }
    float num = stof(num_temp);// convert the numerator string to a float
    float den = stof(dem_temp); // convert the denominator string to a float
    return num / den;
}
