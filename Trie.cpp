#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
typedef struct node
{
    int word_count;
    bool endmark;
    node *next[26];
    node()
    {
        word_count = 0;
        endmark = false;
        for (int i = 0; i < 26; i++)
        {
            next[i] = NULL;
        }
    }
} node;

node *root = new node();

void wordSeperator(string str, vector<string> &s)
{
    stringstream ss(str);
    string word;
    while (ss >> word)
    {
        s.push_back(word);
    }
}

void insert(string str, int len)
{
    node *temp = root;
    for (int i = 0; i < len; i++)
    {
        int idx = str[i] - 'a';
        if (temp->next[idx] == NULL)
        {
            temp->next[idx] = new node();
        }
        temp = temp->next[idx];
    }

    temp->endmark = true;
}

void search(string str)
{
    int len = str.size();
    node *temp = root;
    for (int i = 0; i < len; i++)
    {
        int idx = str[i] - 'a';
        if (temp->next[idx] == NULL)
        {
            cout << "F ";
            return;
        }
        else
            temp = temp->next[idx];
    }

    if (temp->endmark)
    {
        cout << "T ";
    }
    else
        cout << "F ";
}

void display(node *temp, char *str, int level)
{
    if (temp->endmark == true)
    {
        str[level] = '\0';
        cout << str << " ";
    }
    for (int i = 0; i < 26; i++)
    {
        if (temp->next[i] != NULL)
        {
            str[level] = 'a' + i;
            display(temp->next[i], str, ++level);
            level--;
        }
    }
}

node *get_node(node *root, string word)
{
    node *temp = root;

    for (int i = 0; i < word.length(); i++)
    {

        char ch = word[i];
        if (temp->next[ch - 'a'] == NULL)
        {
            return NULL;
        }
        temp = temp->next[ch - 'a'];
    }

    return temp;
}

bool search_trie(node *root, string str)
{
    node *temp = get_node(root, str);
    return temp != NULL; // both will return true if is a word
}
int prefix_count(node *root, string prefix)
{
    node *curr = root;
    int cnt = 0, len = prefix.length();
    for (int i = 0; i < len; i++)
    {
        int id = prefix[i] - 'a';
        if (curr->next[id] == NULL || curr->next[id]->word_count == 0)
            return 0;
        curr = curr->next[id];
    }
    return curr->word_count;
}
int main()
{
    char str2[20];
    string str;

    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    vector<string> s;
    wordSeperator(str, s);

    for (int i = 0; i < s.size(); i++)
    {
        insert(s[i], s[i].size());
    }

    display(root, str2, 0);
    cout << endl;

    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    s.clear();
    wordSeperator(str, s);

    for (int i = 0; i < s.size(); i++)
    {
        search(s[i]);
    }
    return 0;
}