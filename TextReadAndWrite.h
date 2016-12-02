/*
 * TextReadAndWrite.h
 *
 *  Created on: Nov 29, 2016
 *      Author: Daniel Ziv
 */

#ifndef TEXTREADANDWRITE_H_
#define TEXTREADANDWRITE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 9
#define LINE_LENGTH 25


void readFileNames(int argc, char *argv[]);
char *get_out_file_name(int argc, char *argv[]);
// void matrix_to_data_struct

#endif /* TEXTREADANDWRITE_H_ */
