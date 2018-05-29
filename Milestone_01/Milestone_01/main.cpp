#include <iostream>
#include <vector>
#include <string>

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

//Global variables
const int MEMORY_SIZE = 100;
string memory[MEMORY_SIZE];
int accumulator = 0;

//Function prototypes
void Calculate_Operations(string memory[]);
int Calculate_Operations(int command, int location);
string fixMyString(string rawValue);
string fixMyString(int rawValue);


//Alan & Tyler
void Parse_Input_From_File() {

}


//Initial loop thru our memory array.
//Calls overloaded method to determine and execute the instructions.
void Calculate_Operations(string memory[]) {

	//Branching: Used to hold the location of where we're branching
	int branchValue = 0;

	//Initial loop through memory array.
	for (int index = 0; index < MEMORY_SIZE; index++) {

		//To convert and split up the command and location portions of the string.
		string command = memory[index].substr(0, 2);
		string location = memory[index].substr(2, 2);

		//Throwaway output -- To see non-zero memory indexes.
		if (memory[index].compare("0000") != 0)
		{
			cout << "Initial memory value: " << memory[index] << endl;
		}

		int commandInt = stoi(command);
		int locationInt = stoi(location);

		//branchValue = Calculate_Operations(commandInt, locationInt);
		branchValue = Calculate_Operations(stoi(command), stoi(location));

		//If overloaded method brings back a value, that's our new index location (simulates branching)
		if (branchValue != 0)
		{
			cout << "Branch value from return: " << branchValue << endl;
			int* indexPtr = &index;
			*indexPtr = branchValue;
			cout << "Updated Index: " << index << endl;
		}
	}
}

/*
This method will take in a Vector of Objects from Parse.
From the Object, it will use command & location variables.
Based on the command value, the switch statement will handle distributing
the task to the corresponding command. Location variable will be available for
use when needed. -Scott
*/
int Calculate_Operations(int command, int location) {
	string input;
	string convertedAccumulator;
	int branchValue = 0;
	int memoryInt = 0;
	int value = 0;

	//To determine which Command has been sent, and execute calculations. -Scott
	switch (command) {

		//Read a word from the keyboard into a specific location in memory. 
	case 10:
		//Input loop, if they give a value bigger than 4 digits or leave it blank
		do {
			cout << "Please enter a number between 1 and 9999: ";
			getline(cin, input);

		} while (input.length() > 4 || input.length() == 0);

		//Sends to helper method to convert to string and conform to pattern.
		input = fixMyString(input);
		cout << "Input entered: " << input << endl;
		memory[location] = input;
		break;

		//Write output to screen.
	case 11:
		cout << memory[location] << endl;
		break;

		//Load a word from a specific location in memory into the accumulator.
	case 20:
		//Convert from string to int.
		value = stoi(memory[location]);
		accumulator = value;
		cout << "Loaded " << value << " into the Accumulator." << endl;
		break;

		//Store from accumulator to main memory
	case 21:
		//Converted Accumulator value to string and stored in memory.
		convertedAccumulator = fixMyString(accumulator);
		memory[location] = convertedAccumulator;
		cout << convertedAccumulator << " loaded from Accumulator to Memory." << endl;
		break;

		//Addition: Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator). 
	case 30:
		//Converted string to int for math use.
		memoryInt = stoi(memory[location]);
		cout << accumulator << " + " << memoryInt << " result stored in Accumulator." << endl;
		accumulator += memoryInt;
		break;

		//Subtraction: Subtract a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator).
	case 31:
		//Converted string to int for math use.
		memoryInt = stoi(memory[location]);
		cout << accumulator << " - " << memoryInt << " result stored in Accumulator." << endl;

		//QUESTION: Do we want to catch negative values?
		accumulator = accumulator - memoryInt;
		break;

		//Division: Divide the word in the accumulator by the word from a specific location in memory (leave the result in the accumulator).
	case 32:
		//Converted string to int for math use.
		memoryInt = stoi(memory[location]);

		//Divisor can't be 0
		if (memoryInt != 0) {
			accumulator = accumulator / memoryInt;
		}
		else {
			cout << "CRITICAL ERROR: Cannot Divide by 0." << endl;
			cout << "Exiting..." << endl;
			exit(0);
		}
		break;

		//Multiplication: Multiply a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator). 
	case 33:
		//Converted string to int for math use.
		memoryInt = stoi(memory[location]);
		cout << accumulator << " * " << memoryInt << " result stored in Accumulator." << endl;
		accumulator *= memoryInt;
		break;

		//Branch to a specific location in memory.
	case 40:
		cout << "BRANCHING TO LOCATION: " << location << endl;
		branchValue = location - 1;
		break;

		//BranchNeg: Branch to a specific location in memory if result from input(s) is Negative.
	case 41:
		if (accumulator < 0)
		{
			cout << "BranchNeg: BRANCHING TO LOCATION: " << location << endl;
			branchValue = location - 1;
		}
		break;

		//BranchZero: Branch to a specific location in memory if result from input(s) is 0.
	case 42:
		if (accumulator == 0)
		{
			cout << "BranchZero: BRANCHING TO LOCATION: " << location << endl;
			branchValue = location - 1;
		}
		break;

		//Halt: Stop program completely and exit.
	case 43:

		//Call MEMDUMP method
		cout << "Program Complete -- Exiting..." << endl;
		//exit(0);
		break;

		/* -Scott
		Cases for:
		Memdump--Kevin working on this?

		Break(to make it skip over 1 instruction?)
		Continue(?)
		*/
	}
	return branchValue;
}
/*
Takes in a string and checks the length of the string.
If it's length 1, then it'll add 3 zeros to the front.
2 zeros for length 2, etc.

Parameters: string
Returns: string
*/
string fixMyString(string rawValue) {

	string value = rawValue;
	if (rawValue.length() < 4) {
		if (value.length() == 1) {
			value.insert(0, "000");
		}
		else if (rawValue.length() == 2) {
			value.insert(0, "00");
		}
		else if (rawValue.length() == 3) {
			value.insert(0, "0");
		}
	}
	return value;
}

/*
Takes in an int, converts it to a string, and checks
the length of the string. If it's length 1, then
it'll add 3 zeros to the front. 2 zeros for length 2, etc.

Parameters: int
Returns: string
*/
string fixMyString(int rawValue) {

	string value = to_string(rawValue);
	if (value.length() < 4) {
		if (value.length() == 1) {
			value.insert(0, "000");
		}
		else if (value.length() == 2) {
			value.insert(0, "00");
		}
		else if (value.length() == 3) {
			value.insert(0, "0");
		}
	}
	return value;
}

// Output_Data()

int main() {

	//Throwaway, to initialize the array.
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = "0000";

	}


	//Test case #1
	memory[0] = "1007";
	memory[1] = "1008";
	memory[2] = "2007";
	memory[3] = "3008";
	memory[4] = "2109";
	memory[5] = "1109";
	memory[6] = "4300";
	memory[7] = "0000";
	memory[8] = "0000";
	memory[9] = "0000";


	////Test case #2
	//memory[0] = "1009";
	//memory[1] = "1010";
	//memory[2] = "2009";
	//memory[3] = "3110";
	//memory[4] = "4107";
	//memory[5] = "1109";
	//memory[6] = "4300";
	//memory[7] = "1110";
	//memory[8] = "4300";
	//memory[9] = "0000";
	//memory[10] = "0000";


	//Test case #3 (ours)
	/*
	Use a for loop to
	find the smallest of
	10 numbers.
	*/

	////Custom Addition
	//memory[0] = "1007";
	//memory[1] = "1008";
	//memory[2] = "2007";
	//memory[3] = "3008";
	//memory[4] = "2109";
	//memory[5] = "1109";
	//memory[6] = "4300";
	//memory[7] = "0000";
	//memory[8] = "0000";
	//memory[9] = "0000";

	////Custom Division
	//memory[0] = "1007";
	//memory[1] = "1008";
	//memory[2] = "2007";
	//memory[3] = "3208";
	//memory[4] = "2109";
	//memory[5] = "1109";
	//memory[6] = "4300";
	//memory[7] = "0000";
	//memory[8] = "0000";
	//memory[9] = "0000";

	////Custom Multiplication
	//memory[0] = "1007";
	//memory[1] = "1008";
	//memory[2] = "2007";
	//memory[3] = "3308";

	//memory[4] = "2109";
	//memory[5] = "1109";
	//memory[6] = "4300";
	//memory[7] = "0000";
	//memory[8] = "0000";
	//memory[9] = "0000";

	////Custom Subtraction / Branch / Addition  1-1 = 0, branch, 0+1 = 1
	//memory[0] = "1008"; //Read value from keyboard
	//memory[1] = "1009"; //Read value from keyboard
	//memory[2] = "2008"; //Load Memory 07 into Accumulator
	//memory[3] = "3109"; //Subtract Accum - Memory 08 (value stored in Accum)
	//memory[4] = "4020"; //Branch to Memory 20
	//memory[5] = "2110"; //Store Accum value into Memory 09
	//memory[6] = "1110"; //Output Memory 09 to screen.
	//memory[7] = "4300"; //Halt
	//memory[20] = "3009"; //Add Accum + Memory 08 into Accum
	//memory[21] = "2115"; //Store accum into Mem 15
	//memory[22] = "1115"; //Output Mem 15
	//memory[23] = "4300"; //Halt

	////Custom Subtraction / BranchNEG / Addition 1-2 = -1, branchneg, -1+2 = 1
	//memory[0] = "1008"; //Read value from keyboard
	//memory[1] = "1009"; //Read value from keyboard
	//memory[2] = "2008"; //Load Memory 07 into Accumulator
	//memory[3] = "3109"; //Subtract Accum - Memory 08 (value stored in Accum)
	//memory[4] = "4120"; // If Accum value is negative, Branch to Mem 20
	//memory[5] = "2110"; //Store Accum value into Memory 09
	//memory[6] = "1110"; //Output Memory 09 to screen.
	//memory[7] = "4300"; //Halt
	//memory[20] = "3009"; //Add Accum + Memory 08 into Accum
	//memory[21] = "2115"; //Store accum into Mem 15
	//memory[22] = "1115"; //Output Mem 15
	//memory[23] = "4300"; //Halt

	Calculate_Operations(memory);

	return 0;
}