/*! Zach Lieberman, zl5nrs, topological.cpp, 4/20/20 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
using namespace std;

/*! Main: Uses parameter argv[1] for file input */
int main(int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
	map<string, int> classes; //map of all classes -> index
	map<int, string> order; // map of index -> class
	string s1, s2;
	int count = 0;
	while(s1!="0"){
	file >> s1;
	file >> s2;
	if(s2!="0"&&s2!=" "&&s1!="0"&&s1!=" "){
	    classes.insert(pair<string, int>(s1, 0));
	    classes.insert(pair<string, int>(s2,0));
	    }
	}
	for(auto &x: classes){
		x.second=count++;
		order.insert(pair<int, string>(x.second, x.first));
		//cout << x.first << " " << x.second << endl;
	}
	int numVertices = classes.size();
	int adjMatrix[numVertices][numVertices];
	int i,j;
	//set matrix to zeroes
	for(i=0;i<numVertices;i++){
		for(j=0;j<numVertices;j++){
			adjMatrix[i][j]=0;
		}
	}
	//cout << "[0][0]: " << adjMatrix[0][0] << endl;

	//go through file again
	ifstream file2(argv[1], ifstream::binary);
	string n1, n2;
	map<string, int>::iterator vert;
	map<string, int>::iterator e;

	while(n2!="0"){
	file2 >> n1;
	file2 >> n2;
	//cout << "s1: " << n1 << " s2: " << n2 << endl;
		if(n2!="0"&&n2!=" "&&n1!="0"&&n1!=" "){
		    vert = classes.find(n1);
		    e = classes.find(n2);
		    //cout << "[" << vert->second << "][" << e->second << "]" << endl;
		    adjMatrix[vert->second][e->second]=1;
		}
	}

	//print matrix
	/*for(int i=0;i<numVertices;i++){
		for(int j=0;j<numVertices;j++){
			cout << adjMatrix[i][j] << " ";
		}
	cout << endl;
	}*/

	//create path
	vector<string> path;
	int hasVisited[numVertices];
	int indegree[numVertices];
	//set visited and indegree to zero
	for(i=0;i<numVertices;i++){
		hasVisited[i]=0;
		indegree[i]=0;
	}
	//set indegrees
	for(i=0;i<numVertices;i++){
		for(j=0;j<numVertices;j++){
			indegree[i]+=adjMatrix[j][i];
		}
	}

	count = 0;
	while(count<numVertices){
		for(i=0;i<numVertices;i++){
			if(indegree[i]==0&&hasVisited[i]==0){
				path.push_back(order.at(i));
				hasVisited[i]=1;
			}
			for(j=0;j<numVertices;j++){
				if(adjMatrix[i][j]==1)
					indegree[j]--;
			}
		}
		count++;
	}

	for(i=0;i<numVertices;i++)
		cout << path[i] << " ";
	cout << endl;

    // close the file before exiting
    file.close();
    file2.close();
}
