/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Header oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 *Author – Daniel ziv 205614308 and Redael Mdinaradze 319331823
2. Project – Exercise 2
3. Using – TestFile
4. Description – This Module is responsible for managing the different threads for each check of a file
 */

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO Library Includes oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <sys/stat.h>
#include <string.h>

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOo Defines oOoOoOoOoOoOoOoOoOoOoOoO*/
#define NUM_OF_TESTS 4

void FindFileExtension(char* file_name,char *file_extension,int length_of_extension)
{
	strncpy(file_extension,file_name+(FindLocationOfExtension(file_name)*sizeof(char)),(length_of_extension));
	file_extension[strlen(file_name)-FindLocationOfExtension(file_name)]=0;
}

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

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
	char ch=getc(files_to_test);
	while(ch!=EOF && i<5)
	{
		five_bytes_arr[i]=ch;
		i++;		
		 ch=getc(files_to_test);
	}
	five_bytes_arr[i]=0;
}
/**
*
* Accepts:
* --------
* str_to_test-a char array (string)
*
* Returns:
* --------
* location of file extension
*
*Description:
*------------
* FindLocationOfExtension finds the location of file extension
*
*/
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
* All inputs are accepted through the argv[] array
* File_path is a string representing the full path of the file we wish to check (technicly because of our assumptions its just the file name)
*
* Output logfile - string that represents the location of the log file we wish to create
*
* Returns:
* --------
* output logfile
*
* Description:
*------------
* TestFile uses the win32 API to create threads that runs checks for the file in file_path
*/
int main (int argc,char* argv[])
{
	char five_bytes[6];
	int length_of_file_extension=strlen(argv[1])-FindLocationOfExtension(argv[1])+1;
	char *file_extension=(char*)malloc(sizeof(char)*length_of_file_extension);
	FILE *file_to_check=NULL;
	FILE *log_file=NULL;
	//LPTHREAD_START_ROUTINE FindLocationOfExtension(char* str);
	//LPTHREAD_START_ROUTINE ReturnFiveBytes(FILE* files_to_test,char *five_bytes_arr);
	//LPTHREAD_START_ROUTINE ReturnFileSize(FILE* files_to_test);
	//LPTHREAD_START_ROUTINE FindLocationOfExtension;
	int i;
	HANDLE ThreadHandles[NUM_OF_TESTS];   /* An array of thread handles */
	LPDWORD ThreadIDs[NUM_OF_TESTS];        /* An array of threadIDs */
	DWORD exitcode;
	if (argc<3)
		exit(1);
	file_to_check=fopen(argv[1],"r");
	if(file_to_check==NULL)
	{
		printf("error openning file\n");
		exit(2);
	}
	log_file=fopen(argv[2],"w");
	if(log_file==NULL)
	{
		printf("error openning file\n");
		exit(2);
	}
	/* CreateThread(
		NULL,            
		0,               
		(LPTHREAD_START_ROUTINE)FindFileExtension,    
		argv[1],   
		0,                
		ThreadIDs[0]);*/
	FindFileExtension(argv[1],file_extension,strlen(argv[1])-FindLocationOfExtension(argv[1]));
	fprintf(log_file,"the file extension of the tested file is: %s\n",file_extension);
	rewind(file_to_check);
	fprintf(log_file,"the test file size is: %d\n",ReturnFileSize(file_to_check));
	rewind(file_to_check);
	fprintf(log_file,"the file was created on\n");
	rewind(file_to_check);
	fprintf(log_file,"the file was last modified on\n");
	rewind(file_to_check);
	ReturnFiveBytes(file_to_check,five_bytes);
	fprintf(log_file,"The file’s first 5 bytes are: %s\n",five_bytes);
	fclose(file_to_check);
	fclose(log_file);
	exit(0);
}