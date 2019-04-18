#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <functional>
using namespace std;

void printEverything(vector<int> availableResources, deque<vector<int>> currentProcesses, deque<vector<int>> resourcesNeeded, deque<vector<int>> goalProcesses){
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
	
	//Resources still needed
	output+= "Resources still needed:\n";
	for(vector<int> v :  resourcesNeeded) {
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
	string answer = "";
	cin >> numCases;
	
	//For each test case
	for(int i=0; i<numCases; i++){
		int deadlockCount = 0;
		bool deadlock = false;
		string deadProcesses = "";
		answer += "Test Case #" + to_string(i+1) + ":\n---------------\nProcess Request Order:\n";
		
		//*INPUT*//
		//Get inputs for the number of processes and number of resources types
		int numProcesses, numResourceTypes;
		cin >> numProcesses >> numResourceTypes;
		
		//Make new vector for the resources available
		vector<int> availableResources(numResourceTypes); //instantiate an empty vector matching size of numResourceTypes
		
		//Make a "matrix" for the current processes
		deque<vector<int>> currentProcesses;
		
		//Make a "matrix" for the resources needed per process
		deque<vector<int>> resourcesNeeded;
		
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
		
		//Input initial number of each resource that each process still needs to run
		for(int j=0;j<numProcesses; j++){
			vector<int> inter_mat;  //Intermediate matrix to help insert(push) contents of whole row at a time
			for (int k=0; k<numResourceTypes; k++) {
				cin >> num;
				inter_mat.push_back(num);
			} 
			inter_mat.push_back(j+1); //index number
			resourcesNeeded.push_back(inter_mat);
		}

		//Make "matrix" to compare
		deque<vector<int>> goalProcesses = currentProcesses;
		
		//Calculate the required resources for each processes
		for(vector<int> v : currentProcesses){
			transform(goalProcesses.front().begin(), goalProcesses.front().end()-1, goalProcesses.front().begin(), goalProcesses.front().begin(), minus<int>()); //clear contents
			transform(currentProcesses.front().begin(), currentProcesses.front().end()-1, resourcesNeeded.front().begin(), goalProcesses.front().begin(), plus<int>());
			
			currentProcesses.push_back(currentProcesses.front()); //Push to the bottom
			currentProcesses.pop_front(); //Delete the top
			resourcesNeeded.push_back(resourcesNeeded.front()); //Push to the bottom
			resourcesNeeded.pop_front(); //Delete the top
			goalProcesses.push_back(goalProcesses.front()); //Push to the bottom
			goalProcesses.pop_front(); //Delete the top
		}
		
		//*CHECK PROCESSES*//
		printEverything(availableResources, currentProcesses, resourcesNeeded, goalProcesses);
		
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
			transform(currentProcesses.front().begin(), currentProcesses.front().end()-1, availableResources.begin(), inter_mat.front().begin(), plus<int>());
			
			//...what is the result?
			cout << "--------" << endl;
			for(int elem: inter_mat.front()){
				cout << elem << " ";
			} cout << "Result" << endl;
			
			//What's the requirement?
			for(int elem: goalProcesses.front()){
				cout << elem << " ";
			} cout << "Requirement" << " ";
			
			//Check if each individual element has the required resources
			int count = 0;
			for(int j=0;j<numResourceTypes;j++){
				if(inter_mat.front().at(j) >= goalProcesses.front().at(j)){
					count++;
				}
			}
			
			//If that result meet the processes' requirements 
			if(count == numResourceTypes){
				cout << "(o)\n\n" << endl;
				deadlockCount = 0; //Reset the count
				deadProcesses = ""; //Reset 
				
				//Get those resources and run
				transform(currentProcesses.front().begin(), currentProcesses.front().end()-1, availableResources.begin(), currentProcesses.front().begin(), plus<int>()); 
				transform(availableResources.begin(), availableResources.end(), availableResources.begin(), availableResources.begin(), minus<int>()); // = 0 available resources?
				
				//Give the resources back and terminate
				transform(currentProcesses.front().begin(), currentProcesses.front().end()-1, availableResources.begin(), availableResources.begin(), plus<int>()); //more resources than before
				
				//Get the index 
				answer += "#" + to_string(currentProcesses.front().at(numResourceTypes)) + " ";
				
				//Remove it from the top
				currentProcesses.pop_front();
				resourcesNeeded.pop_front();
				goalProcesses.pop_front();
			}
			else{
				cout << "(x)\n\n" << endl;
				deadlockCount++; //Increment the count
				deadProcesses += "#" + to_string(currentProcesses.front().at(numResourceTypes)) + " "; //Get the index
				
				//Check the next process
				currentProcesses.push_back(currentProcesses.front()); //Push to the bottom
				currentProcesses.pop_front(); //Delete the top
				resourcesNeeded.push_back(resourcesNeeded.front()); //Push to the bottom
				resourcesNeeded.pop_front(); //Delete the top
				goalProcesses.push_back(goalProcesses.front()); //Push to the bottom
				goalProcesses.pop_front(); //Delete the top
			}
			
			//DEADLOCK - "A set of processes P1, P2, P3, ... , is in a DEADLOCK state if EVERY PROCESS in the set is WAITING for an event E1 that can be caused only by one of them, say P1."
			if(deadlockCount>=currentProcesses.size()){
				cout << "---DEADLOCK HAS OCCURERD---" << endl;
				cout << "The following processes are in deadlock:" << deadProcesses << endl;
				deadlock = true;
				break;
			}
		}
		
		//If a deadlock has occurred...
		if(deadlock == true){
			//Fix it
			cout << "hi" << endl;
		}
		
		answer += "\n\n";
	} 
	cout << answer << endl;
	return 0;
}
