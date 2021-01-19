// Ina Patrice Gonzales
// Theory of Computation
// December 12, 2020 

// Description: Program reads in a string from a user, decides if it fits the language of L(G) = {a^nb^n | N >= 0}. 
// If the string is accepted, it is then entered into the DPDA() function to analyze it. 
// A table with the steps, states, unread input, stack, and transition rules are then outputted. 

// Data structures used: <char> stacks, functions, and strings 
// Header files used: iostream, stack, string, and iomanip

// headers 
#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

using namespace std; 

// initialize variables for program
// stacks used for DPDA 
stack <char> inputStack;
stack <char> checkStack; 

// function declaration

// returns true if string is valid
bool validString (string str);

// prints a stack
void printStack (stack <char> anyStack);

// pushes a string into a stack
void pushToStack (string str, stack <char> &anyStack);

// transition rules
void rule1 (string &state, string &rule, string &rUsed);
void rule2 (string &state, string &rule, string &rUsed);
void rule3 (string &state, string &rule, string &rUsed);
void rule4 (string &state, string &rule, string &rUsed);
void rule5 (string &state, string &rule, string &rUsed);
void rule6 (string &state, string &rule, string &rUsed);
void rule7 (string &state, string &rule, string &rUsed);
void rule8 (string &state, string &rule, string &rUsed); 

// uses the given rules to analyze the given input
void DPDA (stack <char> &inputStack, stack <char> &checkStack, string &state, int &step, string &rule, string &rUsed);

// formats the information from the DPDA() into a table
void formatTable (int step, string state,stack <char> inputStack, stack <char> checkStack, string rule, string rUsed);

// main function of program
int main(){
    string dashes = "========================================================================================================";
    // user inputs a string to be checked by the DPDA program
    string inputString;
    cout << dashes << endl << "Hello! Welcome to Ina's Theory of Computation Final Project!" << endl << dashes << endl;
    cout << "To begin, please enter a string like this one --> (ex: aabb$) below!" << endl;
    cout << "Note: This string should fit the language of L(G) = {a^nb^n | N >= 0}." << endl << dashes << endl;;
    cout << "Your Input: ";
    cin >> inputString;

    cout << dashes << endl;

    // if the input is not valid (ex: "absdf$" or "aab$"), it will print an error message and program will quit
    if (validString(inputString) == false) {
        cout << "Input Status: INVALID" << endl << dashes << endl;
        cout << "DPDA Status: REJECTED" << endl;
        cout << "** DPDA does not recognize that string. **" << endl << dashes << endl;
    }
    // if the input is valid (ex: "aabb$" or "aaabbb$"), the program will continue running
    else{
        cout << "Input Status: VALID" << endl;
        cout << dashes << endl << "DPDA Status: ACCEPTED!" << endl;
        cout << "** DPDA recognizes that string. **" << endl << dashes << endl;
        // pushes the valid input into a stack to be used by the DPDA function
        pushToStack(inputString,inputStack);

        // step 0 of the DPDA
        string state = "p";
        string rule = "-";
        string rUsed = " ";
        int step = 0;

        // calling the rest of the program to execute the DPDA 
        DPDA(inputStack,checkStack,state,step,rule,rUsed);
    }

    cout << dashes << endl << "I hope you enjoyed my program! Goodbye!" << endl << dashes << endl;
    return 0;
}

// function definitions

// function that validates if the input string is valid or not (if it fits into the language)
bool validString (string str) {
    // bools are used to keep track of various cases 
    bool aFirst, dollarLast, abEqual;
    // length of the string
    int length = str.length();
    // numA and numB are used for occurrences of 'a' and 'b' respectively
    int numA = count(str.begin(), str.end(),'a');
    int numB = count (str.begin(), str.end(),'b');

    // if the string starts with a, it's valid 
    if (str.at(0) == 'a') {
        aFirst = true;
    }
    else {
        aFirst = false;
    }
    // if the string ends with a $, it's valid 
    if (str.at(length-1) == '$') {
        dollarLast = true;
    }
    else {
        dollarLast = false;
    }
    // if the string has equal numbers of a's b's, it's valid
    if (numA == numB){
        abEqual = true;
    }
    else {
        abEqual = false;
    }

    // if all conditions are met, function returns true 
    if (aFirst == true && dollarLast == true && abEqual == true) {
        return true;
    }
    else {
        return false;
    }
}

// prints stack from top to bottom
void printStack (stack <char> anyStack) {
    // if stack is empty, return
    if (anyStack.empty()){
        return;
    }
    // if stack is not empty, print the stack
    else {
        // top of the stack
        char top = anyStack.top();
        // pop the top element
        anyStack.pop();
        // prints the top of the stack
        cout << top; 
        // recursively calls to print the rest of the stack
        printStack(anyStack);
        // push the element back
        anyStack.push(top);
    }

}

// pushes a string into a stack
void pushToStack (string str, stack <char> &anyStack) {
    // putting the input string into inputStack
    for(int i = 0; i < str.length(); i++){
        anyStack.push(str.at(i));
    }
    // since the input is in the correct order, it will be pushed in backwards 
    string reverse;
    // pushes the reverse string into the stack
    while (!anyStack.empty()){
        reverse.push_back(anyStack.top());
        anyStack.pop();
    }
    // this puts the stack in the correct order to use in the program
    for (int i = 0; i < reverse.length();i++){
        anyStack.push(reverse.at(i));
    }
}

// transition rules 

void rule1(string &state, string &rule, string &rUsed){
    rule = "1";
    state = "q";
    rUsed = "";
    checkStack.push('S');
}

void rule2(string &state, string&rule, string &rUsed){
    rule = "2";
    state = "qa";
    rUsed = "";
    inputStack.pop();
}

void rule3(string &state, string&rule, string&rUsed){
    rule = "3";
    state = "q";
    rUsed = "";
    checkStack.pop();
}

void rule4(string &state, string &rule, string &rUsed){
    rule = "4";
    state = "qb";
    rUsed = "";
    inputStack.pop();
}

void rule5(string &state, string &rule, string &rUsed){
    rule = "5";
    state = "q";
    rUsed = "";
    checkStack.pop();
}

void rule6(string &state, string &rule, string &rUsed){
    rule = "6";
    state = "q$";
    rUsed = "";
    inputStack.pop();
}

void rule7(string &state, string &rule, string &rUsed){
    rule = "7";
    state = "qa";
    rUsed = "S -> aSb";
    checkStack.pop();
    checkStack.push('b');
    checkStack.push('S');
    checkStack.push('a');
}

void rule8(string &state, string &rule, string &rUsed){
    rule = "8";
    state = "qb";
    rUsed = "S -> e";
    checkStack.pop();
}

// uses the transition rules to analyze the given input
void DPDA (stack <char> &inputStack, stack <char> &checkStack, string &state, int &step, string &rule, string &rUsed){
    do {
        if (step == 0){
            rule = "-";
            formatTable(step, state,inputStack,checkStack,rule, rUsed);
            step++;
        }
        else {
            if (state == "p"){
                rule1(state, rule, rUsed);
                formatTable(step, state,inputStack,checkStack,rule, rUsed);
                step++;
            }

            if (state == "q"){
                if (inputStack.top() == '$'){
                    rule6(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
                else if (inputStack.top() == 'b'){          
                    rule4(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
                else {
                    rule2(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
            }

            if (state == "qa"){
                if (checkStack.top() == 'S'){
                    rule7(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
                else{
                    rule3(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
            }

            if (state == "qb"){
                if (checkStack.top() == 'S'){
                    rule8(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;           
                }
                else{
                    rule5(state, rule, rUsed);
                    formatTable(step, state,inputStack,checkStack,rule, rUsed);
                    step++;
                }
            }
        }
    } while (!(inputStack.empty()));

}

// formats the information from the DPDA() into a table
void formatTable (int step, string state,stack <char> inputStack, stack <char> checkStack, string rule, string rUsed){
    string separator = " "; 
    if (step == 0){

        // printing out the header for each row
        // / printing out STEP
        cout << left << setw(10);
        cout << "STEP" << ' ';

        // printing out STATE
        cout << left << setw(10);
        cout << "STATE"; 

        // printing out UNREAD INPUT 
        cout << left << setw(15);
        cout << ' ';
        cout << "UNREAD INPUT";

        // printing out STACK
        cout << left << setw(16);
        cout << ' ';
        cout << "STACK";

        // printing out RULE 
        cout << left << setfill(' ') << setw(10);
        cout << ' ';
        cout << "RULE";

        cout << left << setw(5);
        cout << '\t';
        cout << "R USED";

        cout << endl;

        // printing out Step 0's values 
        // printing out STEP
        cout << left << setw(10);
        cout << step << ' ';

        // printing out STATE
        cout << left << setw(10);
        cout << state; 

        // printing out UNREAD INPUT 
        cout << left << setw(15);
        cout << ' ';
        printStack(inputStack);

        // printing out a separator between the columns
        cout << left << setw(20);
        cout << separator;
        cout << '\t';

        // printing out STACK
        cout << left;
        printStack(checkStack);

        // printing out RULE 
        cout << left << setfill(' ') << setw(10);
        cout << '\t';
        cout << rule;

        cout << left << setw(5);
        cout << '\t';
        cout << rUsed;

        cout << endl;


    }
    else {
        // printing out STEP
        cout << left << setw(10);
        cout << step << ' ';

        // printing out STATE
        cout << left << setw(10);
        cout << state; 

        // printing out UNREAD INPUT 
        cout << left << setw(15);
        cout << ' ';
        printStack(inputStack);

        // printing out a separator between the columns
        cout << left << setw(20);
        cout << separator;
        cout << '\t';

        // printing out STACK
        cout << left;
        printStack(checkStack);

        // printing out RULE 
        cout << left << setfill(' ') << setw(10);
        cout << '\t';
        cout << rule;

        cout << left << setw(5);
        cout << '\t';
        cout << rUsed;

        cout << endl;

    }
}
