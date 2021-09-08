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
        tree[node] = tree[left]+ tree[right];
    }
    void update(int node, int begin, int end, int index, int newValue)
    {
        if (index > end || index < begin) //out of bounds or no overlap
            return;
        if (begin == index && end == index) //total overlap
        {
            tree[node] = newValue;
            return;
        }
        int left = node * 2;
        int right = left + 1;
        int mid = (begin + end) / 2;
        update(left, begin, mid, index, newValue);
        update(right, mid + 1, end, index, newValue);
        tree[node] = tree[left]+ tree[right];;
    }
    void add(int node, int begin, int end, int index, int newValue)
    {
        if (index > end || index < begin) //out of bounds or no overlap
            return;
        if (begin == index && end == index) //total overlap
        {
            tree[node] += newValue;
            return;
        }
        int left = node * 2;
        int right = left + 1;
        int mid = (begin + end) / 2;
        add(left, begin, mid, index, newValue);
        add(right, mid + 1, end, index, newValue);
        tree[node] = tree[left]+ tree[right];
    }
    int query(int node, int begin, int end, int i, int j)
    {                             
        if (i > end || j < begin) //out of bounds or no overlap
        {
            return 0; 
        }
        if (begin >= i && end <= j) //total overlap
            return tree[node];
        int left = node*2;
        int right = node*2 + 1;
        int mid = (begin + end) / 2;
        int q1 = query(left, begin, mid, i, j);
        int q2 = query(right, mid + 1, end, i, j);
        return q1+q2;
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
    void update(int index, int newValue = 0)
    {
        update(1, 1, arrSize, index, newValue);
    }
    void add(int index, int newValue)
    {
        add(1, 1, arrSize, index, newValue);
    }
};


int main()
{
    int n, q, i, j, val;
    cin >> n >> q;
    vector<int> vec;
    vec.push_back(0);
    for (int k = 0; k < n; k++)
    {
        cin >> val;
        vec.push_back(val);
    }
    SegmentTree Tree(vec);
    for (int m = 0; m < q; m++)
    {
        cin >> val;
        switch (val)
        {
        case 1:
            cin >> i;
            cout<<Tree.query(i,i);
            Tree.update(i,0);
            cout<<" ( ";
             for(int k=1; k<=n; k++) cout << Tree.query(k, k) << ' ';
            cout << ")\n";
            break;
        case 2:
            cin >> i >> j;
            Tree.add(i, j);
            
             for(int k=1; k<=n; k++) cout << Tree.query(k, k) << ' ';
            cout << endl;
            break;
        case 3:
            cin >> i >> j;
            cout << Tree.query(i, j) << endl;
            break;
        default:
            break;
        }
    }
}