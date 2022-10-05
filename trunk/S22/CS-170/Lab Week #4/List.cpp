/*!*****************************************************************************
\file    List.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Lab #4
\date    01-30-2022

\brief
This uses a struct and performs various tasks on robot via several
separate functions to create, append and destroy a list.

*******************************************************************************/

#include <iostream> // ostream
#include "List.h"

/*******************************************************************/
/*******************************************************************/

void List::free_list()
{
    while (head_)
    {
        struct Node* temp = head_->next;
        delete head_;
        head_ = temp;
    }
}


List::List(void)
{
    head_ = 0;
}

List::~List(void)
{
    free_list();
}

Node* List::MakeNode(int value)
{
    // The Node constructor sets the value, 
    // and sets next to 0.
    return new Node(value);
}

void List::Display() 
{
    Node *list = head_;

    while (list) {
        std::cout << list->number << "   ";
        list = list->next;
    }
}

int List::Count(void)
{
    int count = 0;
    Node *list = head_;

    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

 // Adds a node to the end of the list
 void List::AddToEnd( int value )
 {

    Node* new_list = List::MakeNode(value);
    new_list->number = value;
    

    if (head_ == 0)
    {
        head_ = new_list;
    }
    else
    {
        Node *temp = head_;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_list;
    }
 }

// Adds a node to the front of t
 void List::AddToFront( int value )
 {
    Node *new_list = List::MakeNode(value);
    new_list->number = value;
    new_list->next = head_;

    head_ = new_list;
 }


// Finds an item and returns the node that contains it
// Only finds the first occurrence of value
Node *List::FindItem( int value )
{
    Node *temp = head_;
    while (temp && temp != 0)
    {
        if (temp->number == value)
        {
            return temp;
        }

        temp = temp->next;
    }

    return 0;
}

// Inserts a new node at the specified position
void List::Insert( int value, int position )
{    
    if (position >= 0 && position <= Count())
    {
        if(position == 0)
        {
            List::AddToFront(value);
        }
        else
        {
             Node *new_list = List::MakeNode(value);
             Node *temp_list = head_;
            int i = 1;
            while (i < position)
            {

                temp_list = temp_list->next;
                i++;
            }

            new_list->next = temp_list->next;
            temp_list->next = new_list;
        }
    }     
}

// Deletes a node with the specified value (first occurrence)
void List::Delete( int value )
{
    struct Node* current_list;
    struct Node* next_list;
    if (head_ == NULL)
    {
        return;
    }
    current_list = head_;
    next_list = current_list->next;

    if (current_list->number == value)
    {
        head_ = next_list;
        delete current_list;
    }
    else
    {
        while (next_list != NULL)
        {
            if (next_list->number == value)
            {
                if (current_list->next->next != NULL)
                {
                    current_list->next = (current_list->next->next);
                    delete next_list;
                    next_list = current_list->next;
                    return;
                }
                else
                {
                    current_list->next = NULL;
                    delete next_list;
                    return;
                }
            }
            current_list = next_list;
            next_list = current_list->next;
        }
    }
}

// Concatenates two lists
void List::Concat( List const& Source )
{
    Node* temp = Source.head_;
    while (temp)
    {
        List::AddToEnd(temp->number);

        temp = temp->next;
    }
}

// Deletes all of the values in the list that are it Items
void List::Delete( List const& Items )
{
    Node* temp = Items.head_;
    while (temp)
    {
       List::Delete(temp->number);
        temp = temp->next;
    }
}

// Inserts a new node in the correct position (sorted small to large)
void List::Insert( int value )
{
        Node* next_list;
        Node* new_list = MakeNode(value);
          
        Node* curr_list = head_;


        if (curr_list == NULL)
        {
            head_ = new_list;

        }

        else if (curr_list->number > new_list->number)
        {
            new_list->next = curr_list;
            head_ = new_list;
        }

        else
        {
            next_list = curr_list->next;
            while (next_list != NULL)
            {

                if (new_list->number < next_list->number)
                {
                    new_list->next = next_list;
                    curr_list->next = new_list;
                    return;
                }

                curr_list = curr_list->next;
                next_list = next_list->next;
            }

            if (next_list == NULL)
            {
                new_list->next = next_list;
                curr_list->next = new_list;
            }
        }
}


