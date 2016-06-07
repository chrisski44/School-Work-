
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


void run_command(char *command);
void cd(void);
void shell_commands(char *command);
void run_child_process(char *command);
void return_time();
void direct_input_output(char *args, int in, int out);
void check_input(char *command);
void input_file(char* command);
void output_file(char* command);
int input; // variables that allow me to determine input or output based on < or > 
int output;

int main(void) {

	char *command = malloc(sizeof(char) * 100);
	char *command_input = malloc(sizeof(char) * 100);

	printf("My shell: \n");

	while (1) {

		output = 0;
		input = 0;


		printf(">");

		if (fgets(command_input, 100, stdin) != NULL) {

			check_input(command_input);

			command = strtok(command_input, " ()<>|&;\n\t");

			run_command(command);
		}
	}

	return(EXIT_SUCCESS);

}

/*
Run command takes in the command line arguments and checks to see 
what the commands are and goes to methods appropriaretly from there. If 
exit, time, or cd are used, then one of my created methods are used. If 
not, then a method where I use execvp to handle commands is used

*/
void run_command(char *command) {

	if (strcmp(command, "exit") == 0) {
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "cd") == 0) {
		cd();
	}
	else if (strcmp(command, "time") == 0) {
		return_time();
	}
	else {
		shell_commands(command);
	}
}
/*
This cd method functions like a regular cd command and changes the directory
based on what the user enters. If there is not an appropriate directory 
entered, then an error message is returned to the user.

*/
void cd(void) {

	char *directory = malloc(sizeof(char) * 100);

	directory = strtok(NULL, " ()<>|&;\n\t");


	if (chdir(directory) != 0) {
		printf("%s \n", strerror(errno));
	}


}
/*
If time, cd, or exit is not used, then this method is called to use 
various shell commands based on what the user enters. Tries to create a fork
and if it is possible, then it runs a child process and continues on to other method.
Allows the program to wait appropriately.
*/
void shell_commands(char *command) {

	pid_t pid = fork();

	if (pid == -1) {
		printf("Error creating the fork");
	}

	else if (pid > 0) {

		waitpid(pid, NULL, 0);
	}

	else {
		run_child_process(command);
	}
}
/*
Method that allows myshell to run the many 
shell commands based on what is entered 
in the command line
*/
void run_child_process(char *command) {

	char *directory = malloc(sizeof(char) * 100);

	char *arguments = malloc(sizeof(char) * 100);
	int number_of_arguments = 0;
	char *command_line[20];


	command_line[number_of_arguments++] = command;

	directory = strtok(NULL, " ()<>|&;\n\t");

	while (directory != NULL) {

		command_line[number_of_arguments++] = directory;
		directory = strtok(NULL, " ()<>|&;\n\t");
	}

	if (input || output) {
		number_of_arguments--;
		arguments = command_line[number_of_arguments];

		command_line[number_of_arguments] = NULL;

		direct_input_output(arguments, input, output);
	}

	else {
		command_line[number_of_arguments] = NULL;
	}

	if (execvp(command, command_line) == -1) {
		printf("%s \n", strerror(errno));
	}
}
/*
Method that is called if "time" is entered into the command line.
Calls time.h prototype and returns the current time to the user
*/
void return_time() {
	time_t get_time;
	char* format_time;

	get_time = time(NULL);

	/* Convert to local time format. */
	format_time = ctime(&get_time);

	printf("Current time: %s", format_time);


}
/*
Method that utilizes the input and output global variables to determined
if < or > was entered. Able to see if a file needs to be written to or 
needs directed output based on command line arguments.
*/
void direct_input_output(char *args, int in, int out) {
	if (in) {
		input_file(args);
		return;
	}
	if (out) {
		output_file(args);
		return;
	}
}
/*

This method sets the input and output global variables appropriately based on whether
or not the user entered > or < characters. Uses the strstr method to check the entire 
entered command line to look for these specific characters.

*/
void check_input(char *command) {

	char *check_command = malloc(sizeof(char) * 100);

	check_command = strstr(command, ">");
	if (check_command != NULL) {
		output = 1;
		return;
	}

	check_command = strstr(command, "<");

	if (check_command != NULL) {

		input = 1;
		return;
	}
}
/*
This file accepts the name of the file, and allows the input
to be redirected 
*/
void input_file(char* command) {

	FILE *f;

	if (command != NULL) {
		f = freopen(command, "r", stdin);

		if (f == NULL) {

			printf("No such file or directory exists");
		}
	}
}
/*
This method is called when the user enters a > on the command line. Takes in
a filename as an argument to create a file and then create output. Error
is thrown if the file does not exist.
*/
void output_file(char* command) {

	FILE *f;

	if (command != NULL) {
		f = freopen(command, "w", stdout);

		if (f == NULL) {
			printf("No such file or directory exists");
		}
	}
}

