/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Header oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo*/
/*
 *Author � Daniel ziv 205614308 and Redael Mdinaradze 319331823
2. Project � Exercise 2
3. Using � TestManager
4. Description � This Module is responsible for managing the different processes for each checked file
 */

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO Library Includes oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <sys/stat.h>
#include <string.h>
#include <tchar.h>

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO project Includes oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#include "StringConversionTools.h"

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Defines oOoOoOoOoOoOoOoOoOoOoOoO*/

#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
int LinesInFile(FILE *fp)
{
	int lines=1;
	char ch;
	while(!feof(fp))
	{
		ch = fgetc(fp);
		if(ch == '\n')
		{
			lines++;
		}
	}
	rewind(fp);
	return lines;
}
void ReadFileNameAndProduceLog(FILE* files_to_test, char* output_files_directory, char** output_log_file_path,char** file_name);
/**
*
* Accepts:
* --------
* 
* files_to_test - string of the name of the file containing names of all the files we wish to test
*
* Returns:
* --------
* size of the file in bytes
*
*Description:
*------------
* ReturnFileSize returns amount of bytes in file file_to_test
*
*/
int ReturnFileSize(FILE* files_to_test)
{
	int i=0;
	char ch=getc(files_to_test);
	while(ch!=EOF)
	{
		i++;
		ch=getc(files_to_test);
	}
	return i;
}
/**
*
* Accepts:
* --------
* 
* files_to_test - string of the name of the file containing names of all the files we wish to test
*
* five_bytes_arr- a char array (string) size 6 which will be filled with the first 5 bytes (chars) and 0 (string terminator) at the last place
*
* Returns:
* --------
* first 5 bytes output will be delivered using five_bytes_arr and the array will be null terminated
*
*Description:
*------------
* ReturnFiveBytes returns the first 5 bytes (chars) of a file.
*
*/
void ReturnFiveBytes(FILE* files_to_test,char *five_bytes_arr)
{
	int i=0;
	while(five_bytes_arr[i]!=EOF && i<5)
	{
		five_bytes_arr[i]=getc(files_to_test);
		i++;		
	}
	five_bytes_arr[i]=0;
}
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

int main (int argc,char* argv[])
{
	int i=0;
	int time_till_wait=(int)(argv[2]-'0');
	int lines_in_file;
	char *file_path=NULL;
    char *output_log_file_path=NULL;
    char *proccess_check_frequency=NULL;
	char *runtime_log_file_path=(char*)malloc((strlen(argv[2])+20)*sizeof(char));
	char *command_line=(char*)malloc(sizeof(char)*1000);
	LPTSTR command;
	FILE *fp=NULL;
	FILE *runtime_logfile=NULL;
	PROCESS_INFORMATION *procinfo;
	HANDLE* ipHandles;
	DWORD waitcode=(DWORD)malloc(sizeof(DWORD));
	DWORD exitcode;
	BOOL retVal=0;
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 };
	if (argc<4)
		exit(1);
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("error openning file\n");
		exit(2);
	}
	strcpy(runtime_log_file_path,argv[2]);
	strcat(runtime_log_file_path,"\\");
	strcat(runtime_log_file_path,"runtime_logfile.txt");
	runtime_logfile=fopen(runtime_log_file_path,"w");
	if(runtime_logfile==NULL)
	{
		printf("error openning file\n");
		exit(2);
	}
	lines_in_file=LinesInFile(fp);
	procinfo=(PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION)*lines_in_file);
	ipHandles=(HANDLE*)malloc(sizeof(HANDLE)*lines_in_file);
	for(i=0;i<lines_in_file;i++)
	{
		ReadFileNameAndProduceLog(fp, argv[2],&output_log_file_path,&file_path);
		strcpy(command_line,"TestFile.exe");
		strcat(command_line," ");
		strcat(command_line,file_path);
		strcat(command_line," ");
		strcat(command_line,output_log_file_path);
		command=ConvertCharStringToLPTSTR(command_line);
		retVal = CreateProcess(NULL,command,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startinfo,&procinfo[i]);
		if (retVal == 0)
		{
			fprintf(runtime_logfile,"!!! Failed to create new process to run %s. Error code:%d!!!\n", file_path,GetLastError());
			return;
		}
		fprintf(runtime_logfile,"Successfully created a process with ID %d to execute %s\n",i,file_path);
		ipHandles[i]=procinfo[i].hProcess;
	}
		waitcode = WaitForMultipleObjects(lines_in_file,ipHandles,1,time_till_wait); /* Waiting 5 secs for the process to end */
		fprintf(runtime_logfile,"WaitForMultipleObject output: ");
		switch (waitcode)
		{
		case WAIT_TIMEOUT:
			fprintf(runtime_logfile,"WAIT_TIMEOUT\n"); break;
		case WAIT_OBJECT_0:
			fprintf(runtime_logfile,"WAIT_OBJECT_0\n"); break;
		default:
			fprintf(runtime_logfile,"0x%x\n", waitcode);
		}
	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		fprintf(runtime_logfile,"Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		for(i=0;i<lines_in_file;i++)
		TerminateProcess(ipHandles[i],BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate */
	}
	for(i=0;i<lines_in_file;i++)
	{
		GetExitCodeProcess(procinfo[i].hProcess, &exitcode);
		fprintf(runtime_logfile,"The exit code for the process is 0x%x\n", exitcode);
		CloseHandle(procinfo[i].hProcess); /* Closing the handle to the process */
		CloseHandle(procinfo[i].hThread); /* Closing the handle to the main thread of the process */
	}
	exit(0);
}

int FindLocationOfExtension(char* str)
{
	int i=0,location_of_last_point;
	while(str[i]!=0)
	{
		while(str[i]!='.')
		{
			i++;
			break;
		}
		if(str[i]=='.')
		{
			location_of_last_point=i;
			i++;
		}
	}
	return location_of_last_point;
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
void ReadFileNameAndProduceLog(FILE* files_to_test, char* output_files_directory, char** output_log_file_path,char** file_name)
{
	int CUR_MAX = 100;
	char *token;
	char ch=getc(files_to_test);
	int count = 0;
	int length = 0;
	int locat;
	(*file_name) = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
	if((*file_name)==NULL)
	{
		printf("oh no couldnt allocate mem\n");
		exit (3);
	}
	while ( (ch != '\n') && (ch != EOF) )
	{
	    if(count ==CUR_MAX-1)
	    { // expand if needed
	      CUR_MAX *= 2; // expand to double the current size of anything similar.
	      count = 0;
	      (*file_name) = (char*)realloc((*file_name), CUR_MAX); // re allocate memory.
		  if((*file_name)==NULL)
			{
				printf("oh no couldnt allocate mem\n");
				exit (3);
			}
	    }
		(*file_name)[length] = ch; // stuff in buffer.
	    ch = getc(files_to_test); // read from stream.
	    length++;
	    count++;
	}
	(*file_name)[length]=0;
	(*output_log_file_path)=(char*) malloc(sizeof(char)*(strlen((*file_name)) +strlen(output_files_directory)+ 10));
	if ((*output_log_file_path) == NULL){
			printf("ERROR - MEM allocation failed\n");
			exit(1);
		}
		token=(char*) malloc(sizeof(char) * strlen(*file_name)+10);
		strncpy(token,*file_name,FindLocationOfExtension(*file_name));
		token[FindLocationOfExtension(*file_name)]=0;
		strcpy((*output_log_file_path),output_files_directory);
		strcat((*output_log_file_path),"\\");
		strcat((*output_log_file_path), token);
		strcat((*output_log_file_path),"_log.txt");
		printf("%s\n", *output_log_file_path);
}
