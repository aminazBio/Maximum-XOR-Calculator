#include <iostream>
using namespace std;

struct Node
{
   Node *left, *right;
   Node():left(NULL),right(NULL){}
};

void Insert(Node* r, int x)
{
   int b = sizeof(int) * 8;
   for(int i = b-1; i >= 0; i--)
   {
        int BitVal = (x & (1 << i)); 
        if(BitVal != 0)
        {
            if(r -> right == NULL)
                r -> right = new Node();
            r = r -> right;
        }
        else
        {
            if(r -> left == NULL)
                r -> left = new Node();
            r = r -> left;
        }
   }
}

int Find(Node* r, int x, int BitPos)
{
    if(r == NULL || BitPos < 0)
        return 0;
    if(BitPos == 0)
    {
        if( (x & (1 << BitPos)) == 1)
            return (r -> left == NULL) ? 0 : 1;
        else
            return (r -> right == NULL) ? 0 : 1;
    }

    int bitVal = 0;
    int number = 0;

    if((x & (1 << BitPos)) != 0)
    {
        if(r -> left == NULL)
        {
            number = Find(r -> right, x, BitPos-1);
            bitVal = 0;
        }
        else
        {
            number = Find(r -> left, x, BitPos-1);
            bitVal = 1;
        }
    }
    else
    {
        if(r -> right == NULL)
        {
            number = Find(r -> left, x, BitPos-1);
            bitVal = 0;
        }
        else
        {
            number = Find(r -> right, x, BitPos-1);
            bitVal = 1;
        }
    }
    if(bitVal == 0)
        number = number & ~(1 << BitPos); 
    else
        number = number | (1 << BitPos); 
    return number;
}

void Max(int * arr, int n)
{
    Node* r = new Node();
    int max = 0;
    for(int i = 0; i < n; i++)
    {
        int m = Find(r, arr[i], (sizeof(int)*8)-1 );
        if(m > max)
            max = m;
        Insert(r, arr[i]);
    }
    cout << max;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    int arr[n];

    for(int i = 0; i < n; i++)
    {	
		cin >> arr[i];
        cin.ignore();
    }
   
    Max(arr, n);
}