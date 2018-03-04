/*** Melanie Abercrombie ***
 *** COEN 12L T2:15 2/27 ***
 **LAB 5: Queue & Huffman **
 **Part 1: Priority Queue **/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)();
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

/* Function:    createQueue
 * Description: return a pointer to a new priority queue using compare as its comparison function
 * Runtime:     O( )
 */
PQ *createQueue(int (*compare)()){
    //Check that parameters are not null
    assert(compare != NULL);
    
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    
    pq->data = malloc(sizeof(void *) * pq->length);
    
    return pq;
}

/* Function:    destroyQueue
 * Description:
 *
 */
void destroyQueue(PQ *pq){
    //Check that parameters are not null
    assert(pq != NULL);

    /*  Error: pointer being freed was not allocated
        for(int i = 0; i < pq->length; i++)
            free(pq->data[i]);
    */
    
    /*  free(pq->data);
        free(pq);       
     */
}

/* Function:    numEntries
 * Description: return the number of entries in the priority queue pointed to by pq
 * Runtime:     O(1)
 */
int numEntries(PQ *pq){
    //Check that parameters are not null
    assert(pq != NULL);
    
    return pq->count;
}

/* Function:    addEntry
 * Description: add entry to the priority queue pointed to by pq
 * Runtime:     
 */
void addEntry(PQ *pq, void *entry){
    //Check that parameters are not null
    assert(pq != NULL);
    assert(entry != NULL);
    
    //Reallocate if priority queue is full
    if(pq->count == pq->length){
        pq->length *= 2;
        pq = realloc(pq, (sizeof(void *) * pq->length));
    }
    
    //Place new element at end of binary heap
    pq->data[pq->count] = entry;
    
    
    //Reheap up
    int index = pq->count;                          //Starts at last index

    while((*pq->compare)(pq->data[index], pq->data[parent(index)]) == -1){
        //Swippity swapity
        void *swap = pq->data[index];
        pq->data[index] = pq->data[parent(index)];  //Child gets parent data
        pq->data[parent(index)] = swap;             //Parent gets entry data
        //Change index
        index = parent(index);
    }
    //If entry data is greater than parent data, no swapping needed
    pq->count++;
    
}

/* Function:    removeEntry
 * Description: remove and return the smallest entry from the priority queue pointed to by pq
 * Runtime:     O(log(n))
 */
void *removeEntry(PQ *pq){
    //Check that parameters are not null
    assert(pq != NULL);
    
    //Store smallest entry in temporary variable in order to return
    void *temp = &(pq->data[0]);
    
    //Replace root with last element
    pq->data[0] = pq->data[pq->count];
    
    //Reheap down
    int index = 0;
    while( ((rightCh(index) < pq->count) || (leftCh(index)) < pq->count) ){  //Check that the child to be swapped is in bounds
        //If right child exists, determine which child to swap with
        if(rightCh(index) < pq->count){
            //If left child is smaller, swap (skipped if left child is greater)
            if(((*pq).compare)(pq->data[leftCh(index)], pq->data[index]) == -1){
                //Swapity swoopity
                void *swap = pq->data[index];               //Assign root data to temporary pointer
                pq->data[index] = pq->data[leftCh(index)];  //Replace root with left child's smaller data
                pq->data[leftCh(index)] = swap;             //Replace left child's data with temporary (root's) data
                //Change index
                index = leftCh(index);
            }
            //If left child is greater... If right child is smaller, swap
            else if((*pq->compare)(pq->data[rightCh(index)], pq->data[index]) == -1){
                //Swapity swoopity
                void *swap = pq->data[index];               //Assign root data to temporary pointer
                pq->data[index] = pq->data[rightCh(index)]; //Replace root with right child's smaller data
                pq->data[rightCh(index)] = swap;            //Replace right child's data with temporary (root's) data
                //Change index
                index = rightCh(index);
            }
        }
        //If left child exists, swap
        else if(leftCh(index) < pq->count){
            //Swapity swoopity
            void *swap = pq->data[index];                 //Assign root data to temporary pointer
            pq->data[index] = pq->data[leftCh(index)];  //Replace root with left child's smaller data
            pq->data[leftCh(index)] = swap;       //Replace left child's data with temporary (root's) data
            //Change index
            index = leftCh(index);
        }
        //If there are no children, break
        else{
            pq->count--;
            return temp;
        }
    }
    //Error; because while loop should resolve
    return NULL;
}
