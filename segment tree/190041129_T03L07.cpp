#include <bits/stdc++.h>
using namespace std;

class Lazytree
{ 
    struct TreeNode
    {
        int prop, data;
    };
    TreeNode *tree;
   
    int arrSize;
    void build(vector<int> &arr, int node, int begin, int end)
    {
        if (begin == end)
        { 
            tree[node].data = arr[begin];
            tree[node].prop = 0;
            return;
        }
        int left = node * 2;
        int right = left + 1;
        int mid = (begin + end) / 2;
        build(arr, left, begin, mid);
        build(arr, right, mid + 1, end);
        tree[node].data = tree[left].data + tree[right].data;
        tree[node].prop = 0;
    }
    
void update(int node, int begin, int end, int i, int j, int newValue)
    { 
        if (i > end || i < begin) 
            return;
        if (begin >= i && end <= j) 
        {
            tree[node].data += newValue * (end - begin + 1); 
            tree[node].prop += newValue;                     
        }
        int left = node * 2;
        int right = left + 1;
        int mid = (begin + end) / 2;
        update(left, begin, mid, i, j, newValue);
        update(right, mid + 1, end, i, j, newValue);
        tree[node].data = tree[left].data + tree[right].data + (end - begin + 1) * tree[node].prop;
    }

    int query(int node, int begin, int end, int i, int j, int carry)
    {                            
        if (i > end || j < begin) 
        {
            return 0; 
        }
        if (begin >= i && end <= j) 
            return tree[node].data + (end - begin + 1) * carry;
        int left = node * 2;
        int right = left + 1;
        int mid = (begin + end) / 2;
        int q1 = query(left, begin, mid, i, j, carry + tree[node].prop);
        int q2 = query(right, mid + 1, end, i, j, carry + tree[node].prop);
      
        return q1 + q2;
    }
    

public:
    Lazytree(vector<int> &arr)
    {
        arrSize = arr.size()-1;
        tree = new TreeNode[4 * arrSize];
        build(arr, 1, 1, arrSize);
    };
    ~Lazytree()
    {
        delete[] tree;
    }
    int query(int lowerBound, int upperBound)
    {
        return query(1, 1, arrSize, lowerBound, upperBound,0);
    }

    void update(int i, int j, int newValue)
    {
        update(1, 1, arrSize, i, j, newValue);
    }
   
};

int main()
{
    int n, q, i, j, val,v;
    cin >> n >> q;
    vector<int> vec;
    vec.push_back(0);
    for (int k = 0; k < n; k++)
    {
        cin >> val;
        vec.push_back(val);
    }
    Lazytree segTree(vec);
    for (int k = 0; k < q; k++)
    {
        cin >> val;
        switch (val)
        { 
        case 1:    //update
            cin >> i >> j >> v;           //lower, upper , value
            segTree.update(i, j, v);
            break;
        case 2:     //query
            cin >> i >> j;
            cout << segTree.query(i, j) << endl;  //lower,upper
            break;
        default:
            break;
        }
    }
}