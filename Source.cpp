#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include "LinkedQueue.h"
#include "Stack.h"
using namespace std;

enum MenuOptions { PROCESS_EXPRESSIONS = 1, EXIT };

const int INPUT_WIDTH = 40;
const int REVERSED_WIDTH = 30;
const int PALINDROME_WIDTH = 10;

void displayMenu();
void loadListFromFile();
void populateQueueAndStack(LinkedQueue& list, Stack& stack, string line);
bool isPalindrome(LinkedQueue list, Stack stack, string& reversedString);
void purgeInputErrors(string errMess);


int main() {
	cout << "Welcome User\n\n";

	int option;

	do {
		option = 0;

		displayMenu();
		cin >> option;
		cout << '\n';

		switch (option) {
		case PROCESS_EXPRESSIONS:
			loadListFromFile();
			break;
		case EXIT:
			cout << "\nExiting Program\n\n";
			break;
		default:
			purgeInputErrors("Invalid selection");
		}
	} while (option != EXIT);

	return 0;
}

void displayMenu() {
	cout << "Main Menu\n"
		"Please select an option:\n"
		"1. Process all expressions\n"
		"2. Exit\n"
		"Selection: ";
}

void loadListFromFile() {
	string inputFileName = "Input.txt";
	string outputFileName = "Output.txt";
	ifstream infile(inputFileName);

	if (!infile.is_open()) {
		cout << "Error: Unable to open '" << inputFileName << "'. Terminating Program\n";
		exit(EXIT_FAILURE);
	}
	else if (infile.peek() == EOF) {
		cout << "Error: '" << inputFileName << "' is empty. No data to process. Terminating Program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	ofstream outfile(outputFileName);
	if (!outfile) {
		cout << "Error: Unable to create file '" << outputFileName << "'. Terminating Program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	stringstream header;
	header << left << setw(INPUT_WIDTH) << "Input" << setw(REVERSED_WIDTH) << "Reverse" << setw(PALINDROME_WIDTH) << "Palindrome\n" << endl;
	cout << header.str();
	outfile << header.str();

	int numExpressions = 0;
	string line;
	stringstream formattedLine;
	while (getline(infile, line) && line.length() <= MAX_CHARS) {
		LinkedQueue list;
		Stack stack;
		string originalLine = line;

		populateQueueAndStack(list, stack, line);

		// Store the original expression
		stringstream formattedLine;
		formattedLine << left << setw(INPUT_WIDTH) << originalLine;

		// Check for palindrome and print the reversed expression
		string reversedString = "";
		bool palindromeFound = isPalindrome(list, stack, reversedString);
		formattedLine << left << setw(REVERSED_WIDTH) << reversedString;

		if (palindromeFound) {
			formattedLine << setw(PALINDROME_WIDTH) << "Yes";
		}
		else {
			formattedLine << setw(PALINDROME_WIDTH) << "No";
		}

		string completeLine = formattedLine.str();
		cout << completeLine << '\n';
		outfile << completeLine << '\n';

		numExpressions++;
	}
	cout << "\nTotal Expressions Processed: " << numExpressions << "\n\n";
	outfile << "\nTotal Expressions Processed: " << numExpressions << "\n\n";

	if (numExpressions == 0) {
		cout << "Error: The data file contains only expressions exceeding " << MAX_CHARS << " characters\n\n";
		outfile << "Error: The data file contains only expressions exceeding " << MAX_CHARS << " characters\n\n";
	}

	infile.close();
	outfile.close();
}

void populateQueueAndStack(LinkedQueue& list, Stack& stack, string line) {
	bool apostrophe_encountered = false;
	for (int i = 0; i < line.length(); i++) {
		char ch = tolower(line[i]);

		if (ch == '\'') {
			apostrophe_encountered = true;
		}
		if (apostrophe_encountered == true && ch == ' ') {
			apostrophe_encountered = false;
		}
		if (apostrophe_encountered == false && isalpha(ch)) {
			list.addNode(ch);
			stack.push(ch);
		}
	}
}

bool isPalindrome(LinkedQueue list, Stack stack, string& reversedString) {
	stringstream palindromeSS;
	bool isPalindrome = true;

	if (stack.isEmpty() && list.isEmpty()) {
		isPalindrome = false;
	}

	while (!stack.isEmpty() && !list.isEmpty()) {
		if (list.front() != stack.peek()) {
			isPalindrome = false;
		}

		palindromeSS << stack.peek();
		list.removeNode();
		stack.pop();
	}
	reversedString = palindromeSS.str();
	return isPalindrome;
}

void purgeInputErrors(string errMess) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Error: " << errMess << "\n\n";
}

/*
---------------RUN PROGRAM THEN COPY PASTE OUTPUT HERE---------------

Test Data:

YES!!! you can dance!
Taco cat
Never odd or even
Madam, I'm Adam
Mr. Owl ate my metal worm.
Was it a car or a cat I saw?
Murder for a jar of red rum.
Do geese see God?
Evil olive
Amore, Roma
A man, a plan, a canal: Panama
My gym
No lemon, no melon
Top spot
Sit on a potato pan, Otis!
Did Hannah See bees? Hanna did.
You, banana boy!
Borrow, or rob?
Eva, can I see bees in a cave?
Poor Dan is in a droop.
Oozy rat in a sanitary zoo.
Step on no pets.
Able was I ere I saw Elba
We panic in a pew.
Won't lovers revolt now?
Don't nod
Ma has a ham.
Was it Eliot's toilet I saw?
Egad! No bondage?
Drab as a fool, aloof as a bard.
Won't lovers revolt now?


*****Test Case #1: Special Characters************************

Input                                   Reverse                       Palindrome

YES!!! you can dance!                   ecnadnacuoysey                No
Taco cat                                tacocat                       Yes
Never odd or even                       neveroddoreven                Yes

Total Expressions Processed: 3


*****Test Case #2: String Length Exceeds MAX_SIZE************

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: 1

Error: The data file contains only invalid expressions.
Lines exceeding 65 characters will not be processed.
Lines containing only non-alphabetical characters will not be displayed.
Please check the 'Input.txt' file before running the program again.


*****Test Case #3: String Length Equals MAX_SIZE*************

Input                                   Reverse                       Palindrome

aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjjjjjiiiihhhhggggffffeeeeddddccccbbbbaaaa No
Taco cat                                tacocat                       Yes
Never odd or even                       neveroddoreven                Yes

Total Expressions Processed: 3


*****Test Case #4: Empty Input File**************************

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: 1

Error: 'Input.txt' file is empty. No data to process. Terminating Program


*****Test Case #5: Strings With Empty Spaces*****************

Input                                   Reverse                       Palindrome

YES!!! you can dance!                   ecnadnacuoysey                No
Taco cat                                tacocat                       Yes
Never odd or even                       neveroddoreven                Yes

Total Expressions Processed: 3


*****Test Case #6: Strings With Leading and Trailing Spaces**

Input                                   Reverse                       Palindrome

   abc                                  cba                           No

Total Expressions Processed: 1


*****Test Case #7: Single Valid Character********************

Input                                   Reverse                       Palindrome

x										x					          Yes

Total Expressions Processed: 1


*****Test Case #8: Single Invalid Character******************

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: 1

Error: The data file contains only invalid expressions.
Lines exceeding 65 characters will not be processed.
Lines containing only non-alphabetical characters will not be displayed.
Please check the 'Input.txt' file before running the program again.


*****Test Case #9: Invalid Menu Selection********************

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: asdf

Error: Invalid Selection Option

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: -1-1

Error: Invalid Selection Option




***** Test Case #10: Strings With Apostrophes****************

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection: asdf

Error: Invalid Selection Option

Main Menu
Please select an option:
1. Process all expressions
2. Exit
Selection:1 

Input                                   Reverse                       Palindrome

Don't nod                               donnod                        Yes

Total Expressions Processed: 1

*/






















































/*


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include "LinkedQueue.h"
#include "Stack.h"
using namespace std;

enum MenuOptions { PROCESS_EXPRESSIONS = 1, EXIT };

const int INPUT_WIDTH = 40;
const int REVERSED_WIDTH = 30;
const int PALINDROME_WIDTH = 10;

void displayMenu();
void loadListFromFile();
void purgeInputErrors(string errMess);


int main() {
	cout << "Welcome\n\n";
	int option;

	do {
		option = 0;

		displayMenu();
		cin >> option;

		switch (option) {
			case PROCESS_EXPRESSIONS:
				loadListFromFile();
				break;
			case EXIT:
				cout << "\nExiting Program\n\n";
				break;
			default:
				purgeInputErrors("Invalid selection");
		}
	} while (option != EXIT);

	return 0;
}

void displayMenu() {
	cout << "Main Menu\n"
		"Please select an option:\n"
		"1. Process all expressions\n"
		"2. Exit\n"
		"Selection: ";
}

void loadListFromFile() {
	string inputFileName = "Input.txt";
	string outputFileName = "Output.txt";
	ifstream infile(inputFileName);

	if(!infile.is_open()) {
		cout << "Error: Unable to open '" << inputFileName << "'. Terminating Program\n";
		exit(EXIT_FAILURE);
	}
	else if (infile.peek() == EOF) {
		cout << "Error: '" << inputFileName << "' is empty. No data to process. Terminating Program\n";
		exit(EXIT_FAILURE);
	}

	ofstream outfile(outputFileName);
	if (!outfile) {
		cout << "Error: Unable to create file '" << outputFileName << "'. Terminating Program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	// Print Header
	stringstream header;
	header << left << setw(INPUT_WIDTH) << "Input" << setw(REVERSED_WIDTH) << "Reverse" << setw(PALINDROME_WIDTH) << "Palindrome\n" << endl;
	cout << header.str();
	outfile << header.str();

	// Process Data
	int numExpressions = 0;
	string line;
	while (getline(infile, line)) {
		LinkedQueue list;
		Stack stack;
		string originalLine = line;

		// Push only valid characters onto stack/list
		for (int i = 0; i < line.length(); i++) {
			char ch = tolower(line[i]);

			if (ch >= 'a' && ch <= 'z') {
				list.addNode(ch);
				stack.push(ch);
			}
		}

		// Print the original
		stringstream ss;
		ss << left << setw(INPUT_WIDTH) << originalLine;

		// Check for Palindrome
		char listChar;
		char stackChar;
		stringstream palindromeSS;
		bool isPalindrome = true;

		while (!stack.isEmpty() && !list.isEmpty()) {
			listChar = list.front();
			stackChar = stack.peek();

			if (listChar != stackChar) {
				isPalindrome = false;
			}

			palindromeSS << stackChar;
			list.removeNode();
			stack.pop();
		}

		ss << left << setw(REVERSED_WIDTH) << palindromeSS.str();

		// Determine if the expression is a palindrome
		if (isPalindrome) {
			ss << setw(PALINDROME_WIDTH) << "Yes" << endl;
		}
		else {
			ss << setw(PALINDROME_WIDTH) << "No" << endl;
		}

		// Output the entire line
		string completeLine = ss.str();
		cout << completeLine;
		outfile << completeLine;

		numExpressions++;
	}
	cout << "\nTotal expressions processed: " << numExpressions << "\n\n";

	infile.close();
	outfile.close();
}

void purgeInputErrors(string errMess) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Error: " << errMess << "\n\n";
}


*/