#include <iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *create_node(int x)
{
    struct Node *temp = new Node;
    temp->data = x;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void insert_front(int x)
{
    struct Node *newnode = create_node(x);
    if (head == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    return;
}

void insert_back(int x)
{
    struct Node *newnode = create_node(x);
    newnode->prev = tail;
    tail->next = newnode;
    tail = newnode;
    return;
}

void insert_after_node(int key, int x)
{
    struct Node *newnode = create_node(key);
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == x)
        {
            if (temp == tail)
            {
                newnode -> prev = temp;
                temp -> next = newnode;
                tail = newnode;
                return;
            }
            newnode->next = temp->next;
            temp->next->prev = newnode;
            temp->next = newnode;
            newnode->prev = temp;
            return;
        }
        temp = temp->next;
    }
    cout << "\nERROR ! Node doesn't exist\n";
    return;
}

void update_node(int key, int x)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == x)
        {
            temp->data = key;
            return;
        }
        temp = temp->next;
    }
    cout << "\nERROR ! Node doesn't exist\n";
    return;
}

void remove_head()
{
    if (head == NULL)
    {
        cout << "ERROR! empty!" << endl;
        return;
    }
    if (head == tail)
    {
        head = NULL;
        tail = NULL;
        return;
    }
    struct Node *temp = head;
    temp->next->prev = NULL;
    head = temp->next;
    free(temp);
    return;
}

void remove_element(int key)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            if (temp == tail)
            {
                tail = temp->prev;
                temp->prev->next = NULL;
                free(temp);
                return;
            }
            else if (temp == head)
            {
                temp -> next -> prev = NULL;
                head = temp -> next;
                free(temp);
                return;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(temp);
                return;
            }
        }
        temp = temp->next;
    }
    cout << "\nERROR ! Node doesn't exist\n";
    return;
}

void remove_end()
{
    struct Node *temp = tail;
    if (temp == NULL)
    {
        cout << "NO ELEMENTS TO REMOVE" <<endl;
        return;
    }
    tail = temp->prev;
    temp->prev->next = NULL;
    free(temp);
    return;
}

void display()
{
    struct Node *temp = head;
    cout << "\n\nList in Forward : ";
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    return;
}
void display_rev()
{
    struct Node *temp = tail;
    cout << "\n\nList in Reverse : ";
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
    return;
}

int main()
{
    int n, x, key;
    while (1)
    {
        system("cls");
        cout << "PRESS 1 to insert at front" << endl;
        cout << "PRESS 2 to insert at back" << endl;
        cout << "PRESS 3 to insert after a node" << endl;
        cout << "PRESS 4 to update a node" << endl;
        cout << "PRESS 5 to remove head" << endl;
        cout << "PRESS 6 to remove a node" << endl;
        cout << "PRESS 7 to remove the last node." << endl;
        cout << "PRESS 8 to exit.\n\n\n" << endl;
        cout << "Enter number : ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "\nEnter key : ";
            cin >> key;
            insert_front(key);
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 2:
            cout << "\nEnter key : ";
            cin >> key;
            insert_back(key);
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 3:
            cout << "\nEnter target : ";
            cin >> x;
            cout << "\nEnter key : ";
            cin >> key;
            insert_after_node(key, x);
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 4:
            cout << "\nEnter target : ";
            cin >> x;
            cout << "\nEnter key : ";
            cin >> key;
            update_node(key, x);
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 5:
            remove_head();
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 6:
            cout << "\nEnter key : ";
            cin >> key;
            remove_element(key);
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 7:
            remove_end();
            display();
            display_rev();
            fflush(stdin);
            getchar();
            break;
        case 8:
            system("cls");
            return 0;
        default:
            break;
        }
    }
    system("cls");
    return 0;
}