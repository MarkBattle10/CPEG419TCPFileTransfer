/* This is a helper function that can be called if something goes wrong. It 
 * takes in a string to be printed out as an error message and exits the 
 * program.
 */

#include <stdio.h> /*for perror*/
#include <stdlib.h> /*for exit*/

void DieWithError(char *errMsg){
	perror(errMsg);
	exit(1);
}
