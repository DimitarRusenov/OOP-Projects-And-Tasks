#ifndef _HELPER_H_
#define _HELPER_H_

/*
* Max line of .md file is 1024 + memory for the commands. 
*/
static const unsigned int MAX_COMMAND_LINE = 1048;

//Commands:
static const char * makeHeading = "makeHeading";
static const char * makeItalic = "makeItalic";
static const char * makeBold = "makeBold";
static const char * makeCombine = "makeCombine";
static const char * addLine = "addLine";
static const char * removeLine = "remove";
static const char * exitProgram = "exit";	


//Checks if the file exists.
bool ExistingFile(const char * fileName);

//Reads the command
const char * getCommandInput(char *& command);

/*
* Reads the first agrument after getting the command.
* Used in all commands except 'exitProgram' and 'addLine'.
* It also moves the pointer to the second argument if there is one.
*/
int getFirstArgument(char *& command);

/* 
* Reads the second argument after getting the first one.
* Used in all commands except 'exitProgram' , 'addLine' and 'makeHeading'.
* It also moves the pointer to the third argument if there is one.
*/
int getSecondArgument(char *& command);

/*
* Reads the third agument after getting the second one.
* Used in all commands except 'exitProgram' , 'addLine' and 'makeHeading'. 
*/
int getThirdArgument(char *& command);

#endif // _HELPER_H_