#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void printEverything(vector<int> availableResources, deque<vector<int>> currentProcesses, deque<vector<int>> goalProcesses){
	string output = "\n";
	
	//Available Resources
	output+= "Available:\n";
	for(int aResourecs : availableResources){
		output += to_string(aResourecs) + " ";
	} output += "\n\n";
	
	//Current Processes
	output+= "Current Processes:\n";
	for(vector<int> v : currentProcesses) {
		for(int elem : v){
			output += to_string(elem) + " ";
		} output += "\n";
	}output += "\n";
	
	//Final Processes
	output+= "Process Goals:\n";
	for(vector<int> v : goalProcesses) {
		for(int elem : v){
			output += to_string(elem) + " ";
		} output += "\n";
	}
	
	cout << output << endl;
}

int main(){
	int numCases, num;
	cin >> numCases;
	
	//For each test case
	for(int i=0; i<numCases; i++){
		
		//*INPUT*//
		//Get inputs for the number of processes and number of resources types
		int numProcesses, numResourceTypes;
		cin >> numProcesses >> numResourceTypes;
		
		//Make new vector for the resources available
		vector<int> availableResources(numResourceTypes); //instantiate an empty vector matching size of numResourceTypes
		
		//Make a matrix for the current processes
		deque<vector<int>> currentProcesses;
		
		//Make matrix to compare
		deque<vector<int>> goalProcesses;
		
		//Input initial number of each available resources
		for(int j=0; j<numResourceTypes;j++) cin >> availableResources[j];  
		
		//Input initial number of each resource that each process is holding
		for(int j=0;j<numProcesses; j++){
			vector<int> inter_mat;  //Intermediate matrix to help insert(push) contents of whole row at a time
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				inter_mat.push_back(num);
			} 
			currentProcesses.push_back(inter_mat);
		}
		
		//Input initial number of each resource that each process is supposed to hold to run
		for(int j=0;j<numProcesses; j++){
			vector<int> inter_mat;  //Intermediate matrix to help insert(push) contents of whole row at a time
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				inter_mat.push_back(num);
			} 
			goalProcesses.push_back(inter_mat);
		}
		
		//*CHECK PROCESSES*//
		printEverything(availableResources, currentProcesses, goalProcesses);
		
		//Go through the current processes in order
		//Check if they can meet the requirements if they use the available resources
			//If yes, hold them, and then terminate the processes by releasing all of its resources
		//Repeat
	
	}
	return 0;
}
