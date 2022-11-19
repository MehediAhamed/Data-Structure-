#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct node
{
    int data;
    int height;
    node *left;
    node *right;
    node *parent;
};

node *create_node(int data)
{
    node *temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->height = 0;
    return temp;
}
node *root = NULL;

int height(node *x)
{
    if (x == NULL)
    {
        return -1;
    }
    else
        return x->height;
}
void update_height(node *x)
{
    x->height = 1 + max(height(x->left), height(x->right));
}

int balance_factor(node *x)
{
    return height(x->left) - height(x->right);
}

void left_rotate(node *y)
{
    node *x = y->right;
    node *xL = x->left;

    x->parent = y->parent;

    if (y == root)
    {
        root = x;
    }
    else
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    x->left = y;
    y->parent = x;
    y->right = xL;
    if (xL != NULL)
        xL->parent = y;

    node *temp = y;
    while (temp != NULL)
    {
        update_height(temp);
        temp = temp->parent;
    }
}

void right_rotate(node *y)
{
    node *x = y->left;
    node *xR = x->right;
    x->parent = y->parent;
    if (y == root)
        root = x;
    else
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
            y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
    y->left = xR;

    if (xR != NULL)
    {
        xR->parent = y;
    }

    node *temp = y;
    while (temp)
    {
        update_height(temp);
        temp = temp->parent;
    }
}

node *insert_node(int data)
{
    node *new_node = create_node(data);
    if (root == NULL)
        root = new_node;
    else
    {
        node *temp = root;
        node *pos;
        while (temp != NULL)
        {
            pos = temp;
            if (data < temp->data)
                temp = temp->left;
            else if (data > temp->data)
                temp = temp->right;
            else
            {
                delete new_node;
                return NULL;
            }
        }
        new_node->parent = pos;
        if (data < pos->data)
            pos->left = new_node;
        else
            pos->right = new_node;
        temp = new_node;
        while (temp != NULL)
        {
            update_height(temp);
            temp = temp->parent;
        }
    }
    return new_node;
}

node *max_tree(node *x)
{
    while (x->right != NULL)
        x = x->right;
    return x;
}

node *min_tree(node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

node *successor(node *x)
{
    if (x == max_tree(root))
        return NULL;
    else if (x->right != NULL)
        return min_tree(x->right);
    node *y = x->parent;
    while (y->data < x->data)
        y = y->parent;
    return y;
}
void inorder()
{
    node *temp;
    temp = min_tree(root);
    while (temp != NULL)
    {
        cout << temp->data << "(" << balance_factor(temp) << ")"
             << " ";
        temp = successor(temp);
    }
}


void balance_node(node *temp, int b_factor, node *newnode)
{
    // case LL
    cout << "\nImbalance at node: " << temp->data << endl;

    if (b_factor > 1 && newnode->data < temp->left->data)
    {
        cout << "LL case\nright_rotate(" << temp->data << ")" << endl;
        right_rotate(temp);

        cout << "Status:";
        inorder();
        cout << endl;
        cout << "Root:" << root->data << endl;
    }

    // case LR
    else if (b_factor > 1 && newnode->data > temp->left->data)
    {
        cout << "LR case\nleft_rotate(" << temp->left->data << ")\nright_rotate(" << temp->data << ")" << endl;
        left_rotate(temp->left);
        right_rotate(temp);
        cout << "Status:";
        inorder();
        cout << endl;
        cout << "Root:" << root->data << endl;
    }

    // case RR
    else if (b_factor < -1 && newnode->data > temp->right->data)
    {
        cout << "RR case\nleft_rotate(" << temp->data << ")" << endl;
        left_rotate(temp);
        cout << "Status:";
        inorder();
        cout << endl;
        cout << "Root:" << root->data << endl;
    }

    // case RL
    else if (b_factor < 1 && newnode->data > temp->right->data)
    {
        cout << "RL case\nright_rotate(" << temp->right->data << ")\nleft_rotate(" << temp->data << ")" << endl;

        right_rotate(temp->right);
        left_rotate(temp);
        cout << "Status:";
        inorder();
        cout << endl;
        cout << "Root:" << root->data << endl;
    }
}

void AVL_insert(int data)
{
    node *newnode = insert_node(data);
    node *temp = newnode;
    while (temp != NULL)
    {
        update_height(temp);
        temp = temp->parent;
    }
    temp = newnode;
    inorder();
    int flag = 0;
    while (temp != NULL)
    {
        int bfactor = balance_factor(temp);
        if (bfactor < -1 || bfactor > 1)
        {
            flag = 1;
            balance_node(temp, bfactor, newnode);
            break;
        }
        else
            temp = temp->parent;
    }

    if (flag == 0)
    {
        cout << "\nBalanced" << endl;
        cout << "Root:" << root->data << endl;
    }
}



node *commonnode(int x, int y)
{
    node *temp = root;
    while (1)
    {
        if (x < temp->data && y < temp->data)
            temp = temp->left;
        else if (x > temp->data && y > temp->data)
            temp = temp->right;
        else
            return temp;
    }
}

node *search(int key)
{
    node *x = root;
    while (x != NULL && x->data != key)
    {
        if (x->data > key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}



node *every_node_between(int l, int h)
{
    node *temp;
    temp = search(l);

    while (temp->data != h)
    {
        cout << temp->data << " ";
        temp = successor(temp);
    }
    cout << temp->data << " ";
}

void every_node_between2(node *temp, int l, int h)
{

    if (temp == NULL)
        return;

    if (l < temp->data)
    {
        every_node_between2(temp->left, l, h);
    }
    if (l <= temp->data && h >= temp->data)
        cout << temp->data << " ";

    every_node_between2(temp->right, l, h);
}
int cnt = 0;
node *look_common_high(node *common, int high)
{
    node *x = common;
    while (x != NULL && x->data != high)
    {
        if (x->data > high)
        {
            cnt++;
            x = x->left;
            cout << x->data << " ";
        }

        else
        {
            cnt++;
            x = x->right;
            cout << x->data << " ";
        }
    }
    return x;
}
void print_path_between_nodes(int l, int h)
{
    node *low = search(l);
    node *common = commonnode(l, h);

    if (common->data > l)
    {
        while (low->parent->data != common->data)
        {
            cnt++;
            cout << low->data << " ";
            low = low->parent;
        }
        cout << low->data << " ";
        cnt++;
    }

    cnt++;
    cout << common->data << " ";
    look_common_high(common, h);

    cout << endl;
    cout << cnt << endl;
}
int main()
{
    int n;
    while (1)
    {
        cin >> n;
        if (n == -1)
        {
            break;
        }
        AVL_insert(n);

        cout << endl;
    }
    cout<<"Status:";
       inorder();
    return 0;
}