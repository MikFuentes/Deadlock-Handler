TO BE EDITED

What is the program? 

This program outputs the order in which processes have their requests for the resources they still need fulfilled. It contains the algorithms to show whether a dedalock will occur and the order in which the processes will run after recovering from the deadlock.

How do you run and use the program? 

Some devices may require you to compile the cpp file with c++11 (g++ -std=c++11 CS162A_Project2_Fuentes_Robles_code.cpp -o CS162A_Project2_Fuentes_Robles_code)
After compiling and running the exe, it takes in an int input which will be the number of cases to be inputted. 
Each case will require you to first input 2 ints, which will be the number of processes (P) follow by the number of resource types (R).
The next line contains R numbers which represent how many of each resource is still available.
The next P lines contain the resources currently held by each process.
The next P lines contain the number of resources that each process still needs.
It will continue to take inputs until enough test cases are provided.

After receving all the inputs, program will output the order in which the processes will have their requests fulfilled.
If there is a deadlock, it will output that a deadlock has occured and which processes are in deadlock.
Finally, it will print the process request order and the method used to handle the deadlock.


What are its functions and operations?

int main:
We initialize an int for the number of test cases and get the input for this, and we also initialize a string answer which will be used to output the request order of each test case.
For each test case, we set the deadlockCount to 0 and get the inputs for the number of processes and number of resource types then for each resource type, we get the number available.
We get the input  for the number of resources each process is holding and the number of each reource that each process still needs to run and store these in their own matrices.
We create a matrix for the total number of resources each process needs in order to run 
For each process, we add how much resources the process is currently holding to the number of resources and compare it with the resource goal of the process
If the total is equal to or more than the goal, then the process can run and its currently held resources are added to the resources available.
If the total is less than the goal it will check for the next process.
If no process can run or a deadlock has occured, it will loop through the processes in the deadlock and return all their held resources to the available resources and then run each process.
In the end, the run order for each test case is printed.
