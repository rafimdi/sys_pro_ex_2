/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Header oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 *Author – Daniel ziv 205614308 and Redael Mdinaradze 319331823
2. Project – Exercise 2
3. Using – TestManager
4. Description – This Module is responsible for managing the different processes for each checked file
 */
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO Library Includes oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO Project Includes oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#include "TextReadAndWrite.h"

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Defines oOoOoOoOoOoOoOoOoOoOoOoO*/

#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

/**
*
* Accepts:
* --------
* All inputs are accepted through the argv[] array
* files_to_test - string of the name of the file containing names of all the files we wish to test (argv[1])
*
* output_files_directory - string that represents the location of the directory we wish to put our output files into (argv[2])
*
*proccess_status_check_frequency- integer contating the amount of time we wish to let a process run (argv[3])
* Returns:
* --------
* All the output log files required
*
*Description:
*------------
*TestManager uses the win32 API to create a process that runs the
* command in 'CommandLine'. it uses the win32 API function CreateProcess()
* using default values for most parameters.
*/

int main(int argc, char *argv[])
{
	 char *str="tata.txt";
	int i=0;
	if (argc<4)
	{
		exit(1);
	}
    FILE* files_to_test=fopen(str,"w");
    i++;
    i++;
    fclose(files_to_test);
    files_to_test=fopen(argv[1],"r");
    if (files_to_test == NULL )
    {
    	printf ("ERROR! - could not open the txt file \n");
    	exit(2);
    }
    char *file_path=NULL;
    char *output_log_file_path=argv[2];
    int proccess_check_frequency=argv[3];
    ReadFileNameAndProduceLog(files_to_test, argv[2],output_log_file_path,file_path);
    fclose(files_to_test);
    exit(0);
}

/**
*
* Accepts:
* --------
*
* files_to_test -  file pointer of the file which contains names of all the files we wish to test
*
* output_files_directory - string that represents the location of the directory we wish to put our output files into
*
* output_log_file_path -pointer to string of the path of a file we wish to write the log to (not a full file_path)
* will be used for output.
*
* Returns:
* --------
* file_name - string of the name of a file we wish to test (not a full file_path)
* output_log_file_path- string of the path of a file we wish to write the log to (not a full file_path)
*
* Description:
* -----------
* ReadFileNameAndProduceLog reads a line from files_to_test and produces the File name
* and output file path for TestFile.exe
*
*/
void ReadFileNameAndProduceLog(FILE* files_to_test, char* output_files_directory, char* output_log_file_path,char* file_name)
{
	int CUR_MAX = 100;
	char *token;
	char ch=getc(files_to_test);
	int count = 0;
	int length = 0;
	file_name = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.

	while ( (ch != '\n') && (ch != EOF) )
	{
	    if(count ==CUR_MAX-1)
	    { // expand if needed
	      CUR_MAX *= 2; // expand to double the current size of anything similar.
	      count = 0;
	      file_name = realloc(file_name, CUR_MAX); // re allocate memory.
	    }
	    ch = getc(files_to_test); // read from stream.
	    file_name[length] = ch; // stuff in buffer.
	    length++;
	    count++;
	}
	output_log_file_path=(char*) malloc(sizeof(char)*(strlen(file_name) +strlen(output_files_directory)+ 10));
	if (output_log_file_path == NULL){
			printf("ERROR - MEM allocation failed\n");
			exit(1);
		}
		token = strtok(file_name, ".");
		strcpy(output_log_file_path,output_files_directory);
		strcat(output_log_file_path, token);
		strcat(output_log_file_path,"_log.txt");
}
