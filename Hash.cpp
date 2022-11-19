#include<iostream>

using namespace std;

double load_factor(int n,int table_size)
{
    return n/(1.00*table_size);
}

int linear_count = 0;

void linear_hash(int table[],int tsize,int num)
{
    //computing the hash value
    int index = num % tsize;

    //Inserting in the table if there is no collision
    if(table[index]==-1)
    {
        linear_count++;
        table[index] = num;
        cout << "Inserted : " << "Index: " << index << "(L.F= " << load_factor(linear_count,tsize) << ")" << endl;
    }
    else 
    {
        //if there is a collision
        for (int j = 0; j < 6; j++)
        {
            //computing new hash value
            int t = (index+j) % tsize;
            if(table[t]==-1)
            {
                table[t] = num;
                linear_count++;
                cout << "Inserted : " << "Index: " << t << "(L.F= " << load_factor(linear_count,tsize) << ")" << endl;
                return;
            }
            else 
            {
                cout << "Collision: " << " Index: " << t << endl;
            }
        }
        cout << "Input Abandoned" << endl;
        return;
    }
    return;
}

int q_count = 0;

void quadratic_hash(int table[],int tsize,int num)
{
    //computing the hash value
    int index = num % tsize;

    //Inserting in the table if there is no collision
    if(table[index]==-1)
    {
        q_count++;
        table[index] = num;
        cout << "Inserted : " << "Index: " << index << "(L.F= " << load_factor(q_count,tsize) << ")" << endl;

    }
    else 
    {
        //if there is a collision
        for (int j = 0; j < 6; j++)
        {
            //computing new hash value
            int t = (index+j*j) % tsize;
            if(table[t]==-1)
            {
                table[t] = num;
                q_count++;
                cout << "Inserted : " << "Index: " << t << "(L.F= " << load_factor(q_count,tsize) << ")" << endl;
                return;
            }
            else 
            {
                cout << "Collision: " << " Index: " << t << endl;
            }
        }
        cout << "Input Abandoned" << endl;
        return;
    }
    return;
}

int d_count = 0;

void double_hash(int table[],int tsize,int num)
{
    //computing the hash value
    int index = num % tsize;

    //Inserting in the table if there is no collision
    if(table[index]==-1)
    {
        d_count++;
        table[index] = num;
        cout << "Inserted : " << "Index: " << index << "(L.F= " << load_factor(d_count,tsize) << ")" << endl;

    }
    else 
    {
        int R = 7; // prime number

        //if there is a collision
        for (int j = 0; j < 6; j++)
        {
            //computing new hash value
            int t = (num + j*(R- (num % R))) % tsize;
            if(table[t]==-1)
            {
                table[t] = num;
                d_count++;
                cout << "Inserted : " << "Index: " << t << "(L.F= " << load_factor(d_count,tsize) << ")" << endl;
                return;
            }
            else 
            {
                cout << "Collision: " << " Index: " << t << endl;
            }
        }
        cout << "Input Abandoned" << endl;
        return;
    }
    return;
}




int main(void)
{
    int choice, N,Q;
    cin >> choice >> N >> Q;

    int table_size = N;
    // int hash_table[table_size];

    int hash_table[table_size];

    for (int i = 0; i < table_size; i++)
    {
        hash_table[i] = -1;
    }

    while(Q--)
    {
        int n;
        cin >> n;
        if(choice==1)
        {
            linear_hash(hash_table,table_size,n);
        }
        else if(choice==2)
        {
            quadratic_hash(hash_table,table_size,n);
        }
        else if(choice==3)
        {
            double_hash(hash_table,table_size,n);
        }
    }
    
    return 0;
}
