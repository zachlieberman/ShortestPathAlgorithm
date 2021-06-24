#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#include "middleearth.h"

float computeDistance(MiddleEarth me, const string& start, vector<string> dests);
void printRoute(const string& start, const vector<string>& dests);

int main(int argc, char** argv) {
    // check the number of parameters
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }

    // we'll assume the parameters are all well-formed
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    int num_cities = stoi(argv[3]);
    int rand_seed = stoi(argv[4]);
    int cities_to_visit = stoi(argv[5]);

    // create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);
	//cout << "Dests length: " << dests.size() << "/actual: " << cities_to_visit << endl;
	//compute shortest cost path
	vector<string> list;
	list.push_back(dests[0]);
	for(int i=1;i<cities_to_visit;i++){
		list.push_back(dests[i]);
		sort(list.begin(), list.end());
		float cost = 1000;
		vector<string> least;
		do{
			if(computeDistance(me, list[0], list)<cost){
				cost = computeDistance(me, list[0], list);
				least = list;
			}
		} while(next_permutation(list.begin()+1, list.end()));
		list = least;
		cout << "Minimum path has distance " << computeDistance(me, list[0], list) << ": ";
		printRoute(list[0], list);
	}





    //print route
    /*printRoute("Barad-Dur", dests);
    cout << "The total distance is "<< computeDistance(me, "Barad-Dur", dests) << endl;
    */
    //output table to file
    fstream file;
    file.open("distances.txt");
    auto cout_buf = cout.rdbuf(file.rdbuf());
    me.printTable();
    file.close();

    return 0;
}

/*! This method will compute the full distance of the cycle that starts
 at the 'start' parameter, goes to each of the cities in the dests
 vector IN ORDER, and ends back at the 'start' parameter.
@return float total distance of path
*/
float computeDistance(MiddleEarth me, const string& start, vector<string> dests) {
	vector<string> path = dests;
	for(int j=0;j<path.size();j++){
		if(path[j]==start){
			path.erase(path.begin()+j);
		}
	}
	path.insert(path.begin(), start);
	path.push_back(start);
	float sum = 0.0;
	for(int i=0;i<path.size()-1;i++){
		//cout << path[i] << " + " << path[i+1] << " = " << me.getDistance(path.at(i),path.at(i+1)) << endl;
		sum+= me.getDistance(path.at(i),path.at(i+1));
	}

	return sum;
}

/*! This method will print the entire route, starting and ending at the
'start' parameter.
The output should be similar to:
Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
*/
void printRoute(const string& start, const vector<string>& dests) {
	vector<string> path = dests;
	for(int j=0;j<path.size();j++){
		if(path[j]==start){
			path.erase(path.begin()+j);
		}
	}
	path.insert(path.begin(), start);
	path.push_back(start);
	for(int i=0;i<path.size()-1;i++){
		cout << path[i] << " -> ";
	}
	cout << path[path.size()-1] << endl;
}
