# Deadlock Handler

This program outputs the order in which processes have their requests for resources met. The program is also capable of detecting potential deadlocks between processes and will output the order the processes will run after recovering from a deadlock.

---
# Building

Compile `main.cpp` from the command line using:
```
g++ main.cpp -o main
```

Some devices may require you to compile using a different C++ version. You can specify which version to use using the `std` flag. For example, to compile `main.cpp` using C++11, you would use the command below:
```
g++ -std=c++11 main.cpp -o main
```

---
# Running the Program
To run the program, type the name of the program using the command:
```
main
```

## Using Input/Output Files
If you want to use an input file to run the program, follow the command template below:
```
main < input_file
```

If you would like to use an input and output file to run the program, use the command template below:
```
main < input_file > output_file
```

# Input
The program first takes an `int` value representing the number of cases to test.

Each test case begins with two inputs:
1. An `int` value `P` representing the number of processes to test
2. An `int` value `R` representing the number of resource types

The program will then request for multiple lines of input, which are explained below:
1. The first line shall contain `R` numbers, which represent how many of each resource is still available
2. The next `P` lines shall contain `R` numbers, which represent how many of each resource is currently held by each process
3. The next `P` lines shall contain `R` numbers, which represent how many of each resource is still needed by each process

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
