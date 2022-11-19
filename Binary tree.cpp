#include <iostream>
#include <queue>
using namespace std;
typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;
node *root = NULL;
node *ans = NULL;
char value;
node *createNode(char val)
{
    node *temp = new node();
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
}

void preorderTraversalSearch(node *temp)
{
    if (temp == NULL)
        return;
    else
    {
        if (temp->data == value)
        {
            ans = temp;
            return;
        }
        preorderTraversalSearch(temp->left);
        preorderTraversalSearch(temp->right);
    }
}

void level_order(node*temp)
    {
        queue<node *> qq;
        node *curr;
        if (root != NULL)
            qq.push(root);
        while (!qq.empty())
        {
            curr = qq.front();
            qq.pop();
            cout << curr->data << " ";
            if (curr->left != NULL)
                qq.push(curr->left);
            if (curr->right != NULL)
                qq.push(curr->right);
        }
    }



void preorderTraversal(node *temp)
{
    if (temp == NULL)
        return;
    else
    {
        cout << temp->data << "(";
        if (temp->parent != NULL)
            cout << temp->parent->data << ") ";
        else
            cout << "N) ";
        preorderTraversal(temp->left);
        preorderTraversal(temp->right);
    }
}

void inorderTraversal(node* temp){
    if(temp != NULL){
        inorderTraversal(temp->left);
        cout<<temp->data<<" ";
        inorderTraversal(temp->right);
    }
}
void postorderTraversal(node* temp){
    if(temp != NULL){
        postorderTraversal(temp->left);
        postorderTraversal(temp->right);
        cout<<temp->data<<" ";
    }
}

void removeelement(node *temp, int key)
{
    // removes subtree
    ans = NULL;
    value = key;
    preorderTraversalSearch(root);
    if (ans->parent->left == ans)
        ans->parent->left = NULL;
    else
        ans->parent->right = NULL;
}
int height(node *root)
{
    if (root == NULL)
        return -1;
    int lst = height(root->left);
    int rst = height(root->right);
    return max(lst, rst) + 1;
}
int level(node *root, int val)
{
    node *temp;
    // Base Case
    if (root == NULL)
        return 0;
    // Create an empty queue for level order traversal
    queue<node *> q;
    // Create a var represent current level of tree
    int currLevel = 0;
    // Enqueue Root
    q.push(root);
    while (q.empty() == false)
    {
        int size = q.size();
        while (size--)
        {
            temp = q.front();
            if (temp->data == val)
                return currLevel;
            q.pop();
            /* Enqueue left child */
            if (temp->left != NULL)
                q.push(temp->left);
            /*Enqueue right child */
            if (temp->right != NULL)
                q.push(temp->right);
        }
        currLevel++;
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        char a, b, c;
        cin >> a >> b >> c;
        if (b == '0' && c == '0')
            root = createNode(a);
        else
        {
            ans = NULL;
            value = b;
            node *newnode = createNode(a);
            preorderTraversalSearch(root);
            if (c == '1')
                ans->left = newnode;
            else
                ans->right = newnode;
            newnode->parent = ans;
        }
    }
    preorderTraversal(root);
    cout << endl;
    while (1)
    {
        int c;
        cin >> c;
        switch (c)
        {
        case 2:
        {
            char n;
            cout << "Enter Value : ";
            cin >> n;
            removeelement(root, n);
            preorderTraversal(root);
            cout << endl;
            break;
        }
        case 3:
        {
            char n;
            cout << "Enter Value : ";
            cin >> n;
            ans = NULL;
            value = n;
            preorderTraversalSearch(root);
            if (ans == NULL)
            {
                cout << "NOT PRESENT\n";
                break;
            }

            else
                cout << "Present, left(";
            if (ans->left != NULL)
                cout << ans->left->data;
            else
                cout << "null";
            cout << ") right(";
            if (ans->right != NULL)
                cout << ans->right->data;
            else
                cout << "null";
            cout << ")\n";

            break;
        }

        case 4:
        {
            cout << height(root) << endl;
        }
        }
    }
}

