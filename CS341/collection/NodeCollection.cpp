
#include <iostream>
#include "NodeCollection.h"
using namespace std;

int nodes[100];
int sum = 0;
int smallest = 2000000000;
int largest = -2000000000;
int medianIndex = -1;


NodeCollection::NodeCollection()
      
   // Destructor
NodeCollection::~NodeCollection();
      
   // Linked list operations
void NodeCollection::insertNode(int value) {
    int a = 0;
    int b = n;
    int middleIndex = 0;
    /*while(a < b && !((nodes[middleIndex] > value) && (nodes[middleIndex - 1] < value))) {
        middleIndex = static_cast<int>(((a-b)/2.0));
        if(value > nodes[middleIndex]) {
            a = middleIndex;
        } else {
            b = middleIndex;
        }
    }
    */
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
};
void NodeCollection::deleteNode(int) {

};
void nodeCollection::fillArray(int *arr) {
    for(int i = 0; i < n; i++) {
        arr[i] = nodes[i];
    }
}
void NodeCollection::findNode(int *, int) {

};