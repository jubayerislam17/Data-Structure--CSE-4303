/*
Task-1

A series of values are being inserted in a BST. Your task is to show the balance factor of every node after each insertion.
balance_factor= heightofLeftSubtree - heightofRightSubtree

The following requirements have to be addressed:
Continue taking input until -1.
After each insertion, print the nodes of the tree in an inorder fashion. Show the balance_factor beside each node within a bracket.
Each node has the following attributes: data, left pointer, right pointer, parent pointer, and node height. (store balance_factor if needed)
Your code should have the following functions:
Void Insertion (key) 		// iteratively inserts key
Void Update_height(node)	// update the height of a node
Int height(node)			// returns the height of a node
Int balance_factor(node)	// returns balance factor

Sample Input
Sample Output
12
8
5
11
20
4
7
17
18
-1
12(0)
8(0) 12(1)
5(0) 8(1) 12(2)
5(0) 8(0) 11(0) 12(2)
5(0) 8(0) 11(0) 12(1) 20(0)
4(0) 5(1) 8(1) 11(0) 12(2) 20(0)
4(0) 5(0) 7(0) 8(1) 11(0) 12(2) 20(0)
4(0) 5(0) 7(0) 8(1) 11(0) 12(1) 17(0) 20(1)
4(0) 5(0) 7(0) 8(1) 11(0) 12(0) 17(-1) 18(0) 20(2)


Note: 
If the balance_factor isn’t stored, showing it for every node might result in O(n) [it’s allowed in this solution]. However, after insertion, height needs to be updated only for the ancestors O(height).
*/

#include<bits/stdc++.h>
using namespace std;


struct Node
    {
        int data;
        int height;
        Node* left, *right, *parent;
        Node(int data)
            : data(data),height(0),left(NULL),right(NULL),parent(NULL){}
    };

class AVLtree
{
private:
    Node* root  = NULL;

public:

    int height(Node* x)
    {
        if(x == NULL)
            return -1;
        else
            return x->height;
    }

    void update_height(Node* x)
    {
        while(x)
        {
            x->height = 1 + max(height(x->left),height(x->right));
            x = x->parent;
        }
    }

    int balance_factor(Node *x)
    {
        return height(x->left)-height(x->right);
    }

    void insert(int val)
    {
        Node *n= new Node(val);
        if(!root)
        {
            root = n;
            return;
        }

        Node* temp = root, *prev;
        while(temp)
        {
            prev = temp;
            if(val < temp->data)
                temp = temp->left;
            else if(val>temp->data)
                temp= temp->right;
            else return;
        }
        n->parent = prev;
        val<prev->data ? prev->left=n : prev->right=n;

        update_height(n);
    }

    void inorder(Node *x)
    {
        if(!x)
            return;
        inorder(x->left);
        cout<<x->data<<"("<<balance_factor(x)<<") ";
        inorder(x->right);
    }

    void print()
    {
        inorder(root);
    }


};

    main()
    {
        AVLtree tree;
        int in;
        while(cin>>in && in!=-1)
        {
            tree.insert(in);
            tree.print();
            cout<<endl;
        }
    }
