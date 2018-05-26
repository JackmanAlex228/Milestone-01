#include <iostream>
#include <vector>
using namespace std;


/*	I/O
		READ			10	read into memory
		Write			11
	Load/store operations
		LOAD			20	load from memory location into accumulator
		STORE			21
	Arithmetic operation
		ADD				30	number in memory location + number in accumulator (keep result in accumulator)
		SUB				31
		DIV				32
		MULT			33
	Control operations
		BRANCH			40	branch into specific location in memory
		BRANCHNEG		41
		BRANCHZERO		42
		HALT			43
	Debugging opreations
		MEMDUMP			print the memory image on the screen
		BREAK
		CONTINUE
	Terminate program	-99999
*/

void Parse_Input_From_File() {

}

//Taking in a Vector of Objects from Parse_Input? -Scott


/*
	This method will take in a Vector of Objects from Parse. 
	From the Object, it will use command & location variables.
	Based on the command value, the switch statement will handle distributing
	the task to the corresponding command. Location variable will be available for
	use when needed. -Scott
*/
void Calculate_Operations() {
	
	const int MEMORY_SIZE = 99; 
	int memory[MEMORY_SIZE];
	int accumulator;
	int result;
	int inputToMemory, outputFromMemory;

	int command, location, branchLocation;

	// Parse_Input_From_File(command, location)

	//Calculations

	/*
	5/25/2018 Thinking of throwing the switch statement in a for-loop so that for each object
	in the vector we get from Parse, we can loop thru and send out the corresponding command.
	
	What do you think Alex?
	
	-Scott	
	*/

	//To determine which Command has been sent, and execute calculations. -Scott
	switch (command) {
	
	//Read a word from the keyboard into a specific location in memory. 
	case 10:
		memory[location] = inputToMemory;
		break;
	
	//Write output to screen.
	case 11:
		cout << memory[location] << endl;
		break;
	
	//Load a word from a specific location in memory into the accumulator.
	case 20:
		accumulator = memory[location];
		break;
	
	//Store from accumulator to main memory
	case 21:
		memory[location] = accumulator;
		break;

	//Addition: Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator). 
	case 30:
		result = accumulator + memory[location];
		accumulator = result;
		break;

	//Subtraction: Subtract a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator).
	case 31:
		result = accumulator - memory[location];
		accumulator = result;
		break;

	//Division: Divide the word in the accumulator by the word from a specific location in memory (leave the result in the accumulator).
	case 32:
		//Divisor can't be 0
		if (memory[location] != 0) {
			result = accumulator / memory[location];
		}
		else {
			result = 99999;
		}
		accumulator = result;
		break;

	//Multiplication: Multiply a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator). 
	case 33:
		result = accumulator * memory[location];
		accumulator = result;
		break;
	
	//Branch to a specific location in memory.
	case 40:
		break;
	
	//BranchNeg: Branch to a specific location in memory if result from input(s) is Negative.
	case 41:
		break;
	
	//BranchZero: Branch to a specific location in memory if result from input(s) is 0.
	case 42:
		break;
	
	//Halt: Stop program completely and exit.
	case 43:
		//System.exit() cpp related command.
		break;

	//Execute instructions.
	case -99999:
		//Run the instructions
		break;

	//Bad Divisor, exit program: Can't divide by 0.
	case 99999:
		//Exit Program as an error for Divisor being 0.
		break;
	}

	/*
	Cases for:
	Memdump
	Break(to make it skip an instruction or instructions?)
	Continue(Not sure how this fits?) -Scott
	*/				



	// Output_Data()
	
}



// Output_Data()

int main() {
	Calculate_Operations();
	return 0;
}