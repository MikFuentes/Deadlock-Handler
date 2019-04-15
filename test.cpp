#include <cstdio>
#include <iostream>
#include <array>
using namespace std;



int main(){
	int numCases, num;
	cin >> numCases;
	
	//For each test case
	for(int i=0; i<numCases; i++){
		
		//*GET INPUT*//
		//Get inputs for the number of processes and number of resources types
		int numProcesses, numResourceTypes;
		cin >> numProcesses >> numResourceTypes;
		
		//Make new array for the resources available
		int availableResources [numResourceTypes]; //instantiate an empty array matching size of numResourceTypes
		//array<int, numResourceTypes> availableResources;
		
		//Make new array for the current processes
		int currentProcesses [numResourceTypes][numProcesses]; //instantiate an empty 2d array matching the size of numResourceTypes and numProcesses
		//array<int, numResourceTypes, numProcesses> currentProcesses;
		
		//Make new array to compare
		int finalProcesses [numResourceTypes][numProcesses]; //instantiate an empty 2d array matching the size of numResourceTypes and numProcesses
		//array<int, numResourceTypes, numProcesses> finalProcesses;
		
		//Input initial number of each available resource
		for(int j=0; j<numResourceTypes;j++){
			cin >> num;
			availableResources[j] = num;  
		}
		
		//Input initial number of each resource that each process is holding
		for(int j=0;j<numProcesses; j++){
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				currentProcesses[k][j] = num;  
			}
		}
		
		//Input initial number of each resource that each process is supposed to hold to run
		for(int j=0;j<numProcesses; j++){
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				finalProcesses[k][j] = num;  
			}
		}
		
		//*CHECK PROCESSES*//
		cout << endl;
		for(int j=0;j<numProcesses; j++){
			for (int k=0; k<numResourceTypes; k++) {
				cout << currentProcesses[k][j] << " "; 
			}cout << endl;
		}
		
		cout << endl;
		for(int j=0;j<numProcesses; j++){
			for (int k=0; k<numResourceTypes; k++) {
				cout << finalProcesses[k][j] << " "; 
			}cout << endl;
		}cout << endl;
		
	}
	return 0;
}
