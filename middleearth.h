#ifndef MIDDLEEARTH_H
#define MIDDLEEARTH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

using namespace std;

/*! Lord of the Rings Shortest Path Algorithm

*/
class MiddleEarth {
public:

/*! Iluvatar, the creator of Middle-Earth
@param xsize integer of size of x axis
@param ysize integer of size of y axis
@param num_cities integer of number of cities
@param seed integer for number generator
*/
    MiddleEarth(int xsize, int ysize, int num_cities, int seed);

/*! The Mouth of Sauron!
Prints out info on the created 'world'
*/

    void print();
    void printTable(); /*!< Prints a tab-separated table of the distances, which can be loaded into Excel or similar */

/*! This method returns the distance between the two passed cities.
If we assume the has table is O(1), then this method is also O(1)
@param city1 first parameter
@param city2 second parameter
@return distance between two cities
*/
    float getDistance(const string& city1, const string& city2);

/*! Returns the list of cities traveled to
@param length positive integer of cities traveled to
@return list of cities traveled to
*/
    vector<string> getItinerary(unsigned int length);

private:
    int num_city_names; /*!< Number of different cities */
    int xsize; /*!< integer Size of x parameter */
    int ysize; /*!< integer Size of y parameter */
    unordered_map<string, float> xpos, ypos; /*!< Map of x and y positions */
    vector<string> cities; /*!< Vector of cities */
    unordered_map<string, unordered_map<string, float>> distances; /*!< Map of distances between cities */

    mt19937 gen; /*!< Mersenne-Twister random number engine */
};

#endif
