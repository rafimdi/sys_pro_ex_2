/*
 * TextReadAndWrite.c
 *
 *  Created on: Nov 29, 2016
 *      Author: Daniel Ziv
 */


// #########################################################################################
// Author - Daniel Ziv - 205614308
//          Refael Mdinaradze - 319331823
//
// Project - Ex1
//
// Used files -  "txt_data_conv.h"
//
//
// Description - This file implements a conversion from txt file to data strucy and vise versa:
//							which includes all the needed sub-routiens to solve them
//							1.reads txt file -> matrix
//                          2.matrix -> txt file
//							3.get appropiate out txt file name
//							4.print matrix - self debug purposes
//
// #####################################################################################

#include "TextReadAndWrite.h"

/*
*input: sudokoMatrix, argc, argc
*outputs:None(void)
*This function filles a matrix from the values listed in the text file given in argv[argc = 2]
*/
void readFileNames(int argc, char *argv[])
{
    char line[LINE_LENGTH];

	FILE *file_of_names = NULL ;

	file_of_names = fopen(argv[2], "r");
	if (file_of_names == NULL ){
		printf ("ERROR! - could not open the txt file \n");
		exit(1);
	}


    while(fgets(line,LINE_LENGTH,file_of_names)!=NULL)
    {

    }
	//print_matrix(sudokoMatrix);
	fclose(file_of_names);
}
/*
*input:  argc, argv
*outputs: ouput's file name
**This function determines the output's file name considering the num of the arguments
*if the number of arguments == 3 create new out name from the input text name format
* else(num og args == 4 -> output's file name will be taken from argv[argc]
*/
char *get_out_file_name(int argc, char *argv[])
{
	char *out_file_name;
	int i = 0 ;
	char *token ;
	//char *tmp = NULL ;
	out_file_name = (char*) malloc(sizeof(char)*strlen((argv[2]) + 10)); // to include the "_out" addition
	if (out_file_name == NULL){
		printf("ERROR - MEM allocation failed\n");
		exit(1);
	}
	token = strtok(argv[2], ".");
	out_file_name = strcat(token, "_out.txt");
	return out_file_name;
}

