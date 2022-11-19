#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct node
{
    int data;
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
    return temp;
}

node *root = NULL;

bool insert_node(int data)
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
                return false;
            }
        }
        new_node->parent = pos;
        if (data < pos->data)
            pos->left = new_node;
        else
            pos->right = new_node;
    }
    return true;
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

node *predecessor(node *x)
{
    if (x == min_tree(root))
        return NULL;
    else if (x->left != NULL)
        return max_tree(x->left);
    node *y = x->parent;
    while (y->data > x->data)
        y = y->parent;
    return y;
}

void BST_delete(int x)
{
    node *temp = search(x);

    if (temp == NULL)
        cout << "The node to be deleted is not found" << endl;
    else
    {
        node *p = temp->parent;
        // delete head

        if (p == NULL)
        {
            if (temp->right != NULL)
            {
                root = temp->right;
                root->parent = NULL;
                node *y = successor(temp);
                y->left = temp->left;

                if (temp->left != NULL)
                    temp->left->parent = y;
            }
            else if (temp->left != NULL && temp->right == NULL)
            {
                root = temp->left;
                root->parent = NULL;
            }
            else
                root = NULL;
            return;
        }

        // if node has no child--leaf node
        if (temp->left == NULL && temp->right == NULL)
        {
            if (temp == p->left)
                p->left = NULL;
            else
                p->right = NULL;
        }

        // if node has both child
        else if (temp->left != NULL && temp->right != NULL)
        {
            node *y = successor(temp);

            if (temp == p->right)
                p->right = temp->right;
            else
                p->left = temp->right;

            temp->right->parent = p;
            y->left = temp->left;
            temp->left->parent = y;
        }
        // if node has 1  right child
        else
        {
            if (temp == p->right)
            {
                if (temp->left == NULL)
                {

                    p->right = temp->right;
                    temp->right->parent = p;
                }
                else
                {
                    p->right = temp->left;
                    temp->left->parent = p;
                }
            }
            else
            {
                if (temp->left == NULL)
                {

                    p->left = temp->right;
                    temp->right->parent = p;
                }
                else
                {
                    p->left = temp->left;
                    temp->left->parent = p;
                }
            }
        }
    }
}

void level_order(struct node *root)
{
    queue<struct node *> qq;
    struct node *curr;
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
    cout << endl;
}

void inorder()
{
    node *temp;
    temp = min_tree(root);
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = successor(temp);
    }
}






node* commonnode(int x, int y)
{
    node* temp=root;
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

int max_in_way(node * x,int low,int high)
{
     if (commonnode(low,high)->data == high)
    {
        return high;
    }
    while (x->right != NULL && x->data <= high)
        x = x->right;
    return x->data;

}
int main()
{
    int n, rem;
    while (1)
    {
        cin >> n;
        if (n == -1)
        {
            break;
        }
        insert_node(n);
    }

    inorder();
}