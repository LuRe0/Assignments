#include <iostream> // cout, endl
#include "List.h"

namespace CS170
{
    namespace ListLab
    {
        namespace 
        {
        /*!******************************************************************
          Construct a node with given integer value

          \param value
          integer

          \return
          pointer to newly constructed node
         ********************************************************************/
            struct Node* MakeNode(int value)
            {
                struct Node *pNode = new Node; // Allocate memory for the node
                pNode->number = value;         // Set data field (number)
                pNode->next = 0;               // Set next (no next yet)

                return pNode;
            }
        }

        /*!******************************************************************
          Print the list.

          \param list
          The list to count.

          \return
          void
         ********************************************************************/
        void PrintList(struct Node *list)
        {
            while (list)
            {
                std::cout << list->number << "   ";
                list = list->next;
            }
            std::cout << std::endl;
        }

        /*!******************************************************************
          Get the number of nodes in the list.

          \param list
          The list to count.

          \return
          The number of nodes in the list.
         ********************************************************************/
        int Count(struct Node *list)
        {
            int count = 0; // Number of nodes in the list

            while (list)
            {
                count++;
                list = list->next;
            }

            return count;
        }

        // ... your code 



        // Adds a node to the front of the list
        void AddToEnd(Node **pList, int value)
        {
            struct Node *new_list = MakeNode(value);
            new_list->number = value;

            if (*pList == 0)
            {
                *pList = new_list;
            }
            else
            {
                struct Node *temp = *pList;
                while (temp->next)
                {
                    temp = temp->next;
                }
                temp->next = new_list;
            }     
        }

        // Adds a node to the end of the list
        void AddToFront(Node **pList, int value)
        {
            struct Node *new_list = MakeNode(value);
            new_list->number = value;
            new_list->next = *(pList);

            *(pList) = new_list;
        }

        // Finds an item and returns the node that contains it
        Node *FindItem(Node *list, int value)
        {
            struct Node *temp = list;
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

        // Frees (deletes) all of the nodes in the list
        void FreeList(Node *pList)
        {
            while (pList)
            {
                struct Node *temp = pList->next;
                delete pList; 
                pList = temp;
            }
        }

        // Inserts a new node at the specified position
        void Insert(Node **pList, int value, int position)
        {
           

            if (position >= 0 && position <= Count(*pList))
            {
                if(position == 0)
                {
                    AddToFront(pList, value);
                }
                else
                {
                    struct Node *new_list = MakeNode(value);
                    struct Node *temp_list = *pList;
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

    } // namespace ListLab
} // namespace CS170
