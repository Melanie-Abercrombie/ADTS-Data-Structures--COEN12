/*** Melanie Abercrombie ***
 *** COEN 12L T2:15 3/13 ***
 **LAB 5: Queue & Huffman **
 *Part 2: Huffman Encoding */

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pack.h"
#include "pqueue.h"

struct tree
{
	
};

///////Functions to find node index
/* parent:  return an integer representing the index of the parent of a node wtih index i
 * Runtime: O(1) */
int parent(int i){
    int index = (i - 1)/2;
    return index;
}
/* leftCh:  return an integer representing the index of the left child of a node wtih index i
 * Runtime: O(1) */
int leftCh(int i){
    int index = (2 * i) + 1;
    return index;
}
/* rightCh: return an integer representing the index of the right child of a node wtih index i
 * Runtime: O(1) */
int rightCh(int i){
    int index = (2 * i) + 2;
    return index;
}
///////

int main (int argc, char *argv[]){
	FILE *fp;
	int charcount[256 + 1];


}