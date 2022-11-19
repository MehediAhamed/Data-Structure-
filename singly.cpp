#include <iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

void InsertHead(struct Node **head_ref, int value)
{
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;

    newNode->next = *head_ref;
    *head_ref = newNode;
    //cout << "P" << endl;
}

void InsertEnd(struct Node **head_ref, int value)
{
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->next = NULL;
    newNode->data = value;

    /*If the Linked List is empty,
    then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
    }
    else
    {
        struct Node *temp = *head_ref;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void InsertPosition(struct Node **head_ref, int value, int pos)
{
     struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    
    // head insert
    if (pos == 0)
    {
        InsertHead(head_ref, value);
    }

   

    else if (head_ref == NULL)
    {
        newNode->next = NULL;
        *head_ref = newNode;
    }

    else
    {
        struct Node *temp = *head_ref;
        for (int i = 1; i < pos ; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }


    
}

void display(struct Node *head_ref)
{
    while (head_ref != NULL)
    {

        cout << head_ref->data << endl;
        head_ref = head_ref->next;
    }
}

void DeleteHead(struct Node **head_ref)
{
    if (*head_ref == NULL)
    {
        cout << "List is Empty" << endl;
    }

    else
    {
        struct Node *temp = *head_ref;
        if (temp->next == NULL)
        {
            head_ref = NULL;
            free(temp);
        }

        else
        {
            *head_ref = temp->next;
            free(temp);
            cout << "Node deleted" << endl;
        }
    }
}

void DeleteEnd(struct Node **head_ref)
{
    if (*head_ref == NULL)
    {
        cout << "List is Empty" << endl;
    }

    else
    {
        struct Node *temp1 = *head_ref, *temp2;
        if (temp1->next == NULL)
        {
            *head_ref = NULL;
        }

        else
        {
            while (temp1->next != NULL)
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }

            temp2->next = NULL;
        }
        free(temp1);
        cout << "Node deleted at the end" << endl;
    }
}

void DeletePosition(struct Node **head_ref, int pos)
{
    int flag = 0;
    struct Node *temp1 = *head_ref, *temp2;
    if (pos == 0)
    {
        *head_ref = temp1->next;
        free(temp1);
        cout << "Node Deleted at given position" << endl;
    }
    else
    {
        for (int i = 0; i < pos; i++)
        {
            if (temp1->next != NULL)
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            temp2->next = temp1->next;
            free(temp1);
            cout << "Node Deleted at given position" << endl;
        }

        else
        {
            cout << "Invalid postion. postion exceeds size" << endl;
        }
    }
}
int main()
{
    struct Node *head = NULL;
    InsertHead(&head, 6);
    InsertEnd(&head, 5);
    InsertPosition(&head, 43, 1);
    display(head);

    // DeleteHead(&head);
    // display(head);
    // DeleteEnd(&head);
    // display(head);
     DeletePosition(&head,2);
     display(head);
}