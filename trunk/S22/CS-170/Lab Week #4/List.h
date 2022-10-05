////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

struct Node {
    int number; // data portion
    Node *next; // pointer portion

    // Non-default constructor
    Node(int value) {
        number = value;
        next = NULL;
    }
};

class List {
    public:
        // Default constructor
        List();

        // Destructor
        ~List();

        // Adds a node to the end of the list
        void AddToEnd( int value );

        // Adds a node to the front of the list
        void AddToFront( int value );

        // Returns the number of nodes in the list
        int Count();

        // Finds an item and returns the node that contains it
        // Only finds the first occurrence of value
        Node *FindItem( int value );

        // Inserts a new node at the specified position
        void Insert( int value, int position );

        // Deletes a node with the specified value (first occurrence)
        void Delete( int value );

        // Concatenates two lists
        void Concat( List const& Source );

        // Deletes all of the values in the list that are it Items
        void Delete( List const& Items );

        // Inserts a new node in the correct position (sorted small to large)
        void Insert( int value );

        // Displays the list
        void Display();

    private:
        Node *head_;
        Node* MakeNode(int value);
        Node* find(int value, Node** prev);
 
        // Any other private methods you need...
        void free_list();
};

#endif // LIST_H
