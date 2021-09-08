#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int *tree;
    int arrSize;
    void build(vector<int> &arr, int node, int begin, int end)
    {
        if (begin == end)   // leaf node
        { 
            tree[node] = arr[begin];
            return;
        }
        int left = node*2;
        int right = node*2 + 1;
        int mid = (begin + end) / 2;
        build(arr, left, begin, mid);
        build(arr, right, mid + 1, end);
        tree[node] =  min(tree[left],tree[right]);
    }
    
    int query(int node, int begin, int end, int i, int j)
    {                             
        if (i > end || j < begin) //out of bounds or no overlap
        {
            return INT_MAX; 
        }
        if (begin >= i && end <= j) //total overlap
            return tree[node];

        int left = node*2;
        int right = node*2 + 1;
        int mid = (begin + end) / 2;
        int q1 = query(left, begin, mid, i, j);
        int q2 = query(right, mid + 1, end, i, j);
        return min(q1,q2);
    }
  

public:
    SegmentTree(std::vector<int> &arr)
    {
        arrSize = arr.size()-1;
        tree = new int[4 * arrSize];
        build(arr, 1, 1, arrSize);
    }
    ~SegmentTree()
    {
        delete[] tree;
    }
    int query(int lowerBound, int upperBound)
    {
        return query(1, 1, arrSize, lowerBound, upperBound);
    }
    
    
};



int main()
{
    int n, q, i, j, val;
    cin >> n >> q;
    vector<int> vec;
    vec.push_back(INT_MAX);
    for (int k = 0; k < n; k++)
    {
        cin >> val;
        vec.push_back(val);
    }
    SegmentTree Tree(vec);
    for(int k=0;k<q;k++){
        cin>>i>>j;
        cout<<Tree.query(i,j)<<endl;
    }
}