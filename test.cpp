#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <functional>
using namespace std;

void printEverything(vector<int> availableResources, deque<vector<int>> currentProcesses, deque<vector<int>> goalProcesses){
	string output = "\n-----------------\n";
	
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
	
	cout << output << "-----------------\n" << endl;
}

int main(){
	int numCases, num;
	cin >> numCases;
	
	//For each test case
	for(int i=0; i<numCases; i++){
		string answer = "";
		
		//*INPUT*//
		//Get inputs for the number of processes and number of resources types
		int numProcesses, numResourceTypes;
		cin >> numProcesses >> numResourceTypes;
		
		//Make new vector for the resources available
		vector<int> availableResources(numResourceTypes); //instantiate an empty vector matching size of numResourceTypes
		
		//Make a "matrix" for the current processes
		deque<vector<int>> currentProcesses;
		
		//Make "matrix" to compare
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
			inter_mat.push_back(j+1); //index number
			currentProcesses.push_back(inter_mat);
		}
		
		//Input number of each resource that each process is supposed to hold to run
		for(int j=0;j<numProcesses; j++){
			vector<int> inter_mat;  //Intermediate matrix to help insert(push) contents of whole row at a time
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				inter_mat.push_back(num);
			} 
			inter_mat.push_back(j+1); //index number
			goalProcesses.push_back(inter_mat);
		}
		
		//*CHECK PROCESSES*//
		printEverything(availableResources, currentProcesses, goalProcesses);
		
		//*GENERATE OUTPUT*//
		//While there are still processes to be run
		while (!(currentProcesses.empty())) {
			
			//What's on top?
			for(int elem: currentProcesses.front()){
				cout << elem << " ";
			} cout << "Top" << endl;
			
			//What's available?
			for(int elem: availableResources){
				cout << elem << " ";
			} cout << "  Available" << endl;
			
			//If you add the top with what's available...
			deque<vector<int>> inter_mat = currentProcesses; //Temporary storage
			transform(currentProcesses.front().begin(), currentProcesses.front().end(), availableResources.begin(), inter_mat.front().begin(), plus<int>());
			
			//...what is the result?
			cout << "--------" << endl;
			for(int elem: inter_mat.front()){
				cout << elem << " ";
			} cout << "Result" << endl;
			
			//What's the requirement?
			for(int elem: goalProcesses.front()){
				cout << elem << " ";
			} cout << "Requirement" << " ";
			
			//If that result meet the processes' requirements 
			if(inter_mat.front() >= goalProcesses.front()){
				cout << "(o)\n\n" << endl;
				
				//Get those resources and run
				transform(currentProcesses.front().begin(), currentProcesses.front().end(), availableResources.begin(), currentProcesses.front().begin(), plus<int>()); 
				transform(availableResources.begin(), availableResources.end(), availableResources.begin(), availableResources.begin(), minus<int>()); // = 0 available resources?
				
				//Give the resources back and terminate
				transform(currentProcesses.front().begin(), currentProcesses.front().end()-1, availableResources.begin(), availableResources.begin(), plus<int>()); //more resources than before
				
				//Give the index 
				answer += "#" + to_string(currentProcesses.front().at(numResourceTypes)) + " ";
				
				//Remove it from the top
				currentProcesses.pop_front();
				goalProcesses.pop_front();
			}
			else{
				cout << "(x)\n\n" << endl;
				
				//Check the next process
				currentProcesses.push_back(currentProcesses.front()); //Push to the bottom
				currentProcesses.pop_front(); //Delete the top
				goalProcesses.push_back(goalProcesses.front()); //Push to the bottom
				goalProcesses.pop_front(); //Delete the top
			}
		}
		cout << "---------------\nProcess Request Order:\n" << answer << endl;
	}
	return 0;
}
