// Specification file for the NumberList class
#ifndef NODECOLLECTION_H
#define NODECOLLECTION_H

class NodeCollection
{
private:
    void destroy();

public:
   // Constructor
    NodeCollection()
      
   // Destructor
    ~NodeCollection();
      
   // Linked list operations
    void insertNode(int);
    void deleteNode(int);
    void displayNodes() const;
    int findNode(int *, int);
};
#endif