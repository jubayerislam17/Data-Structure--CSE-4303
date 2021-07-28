/*
Task-3:

Let T be a rooted tree. The Lowest Common Ancestor(LCA) between two nodes n1 and n2 is the lowest node in T with both n1 and n2 as descendants (we allow a node to be its descendant).
The LCA of n1 and n2 in T is the shared ancestor of n1 and n2 located farthest from the root. Computation of lowest common ancestors may be helpful, for instance, as part of a procedure for determining the distance between pairs of nodes in a tree.

Let’s assume two nodes of a BST are n1 and n2. Your task is to find out their LCA. For example, suppose the status of the tree is as follows:
		 20
   	 	/   \
  	    8     22
 	   / \
  4   12
   	     / \
         10  14

LCA of 10 & 14: 12
LCA of 4  & 22: 20
LCA of 4  & 8 : 8
LCA of 4  & 12 :8 (20 is also a common ancestor, but not ‘lowest’)
LCA of 8  & 14: 8
LCA of 8  & 22: 20
LCA of 20 & 8 : 20
LCA of 10 & 12: 12

Steps:
At first, a sequence of N integers will be inserted (until -1)
The numbers are inserted in an AVL Tree. The final status of the tree is shown after all nodes are inserted.
Then there will be a number T, followed by T pairs of n1 & n2
For each pair, your task is to print the LCA. 

(PTO)

Sample Input
Sample Output
Input sequence
12 9 5 11 20 15 7 3 6 27 -1
Status: 3(0) 5(0) 6(0) 7(0) 9(-1) 11(0) 12(1) 15(0) 20(0) 27(0)
11
3 6
6 11
27 9
12 27
27 12
6 7
9 3
7 20
20 15
11 7
11 27
-1

5
7
12
12
12
7
7
12
20 
7
12


Note: 
Use AVL Tree
The solution must be O(logN)

12(1)
				    /       \
				   7(0)       20(0)
				  /  \      /    \
				5(0)	9(0) 15(0)  27(0)
			     /  \	  \
			  3(0)   6(0)  11(0)
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
    void inorder(Node *x)
    {
        stack<Node *> st;
        Node *tmp = root;
        while (tmp or !st.empty())
        {
            if (tmp)
            {
                st.push(tmp);
                tmp = tmp->left;
            }
            else
            {
                tmp = st.top(); // because tmp is now null ; need previous node
                printf("%d(%d) ", st.top()->data, balance_factor(st.top()));
                st.pop();
                tmp = tmp->right;
            }
        }
        cout<<endl;
    }

    void balance_node(Node *x, int bf, int val)
    {

        if (bf > 1 and val < x->left->data)
            {

                LLrotation(x);
            }
        else if (bf > 1 and val > x->left->data)
            {

                x->left=RRrotation(x->left);
                 LLrotation(x);
            }
        else if (bf < -1 and val > x->right->data)
              {


                 RRrotation(x);
            }
        else if (bf < -1 and val < x->right->data)
        {

            x->right=LLrotation(x->right);
            RRrotation(x);
        }


    }

    void check_balance(Node* n,int val)
    {
        bool check = false;
        Node* temp=n;
        while(temp)
        {
            int bf = balance_factor(temp);
            if(bf<-1 || bf>1)  //imbalanced
            {
                balance_node(temp,bf,val);
                break;
            }
            temp=temp->parent;
        }


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
        check_balance(n,val);
    }

    Node* LLrotation(Node* z)
    {
        Node* y = z->left;
        Node* t3= y->right; //right child of y

        if(z==root)
        {
            root=y;
            y->parent=z->parent;
        }
        else
        {
            y->parent=z->parent;
            if(z==z->parent->right)
                z->parent->right=y;
            else
                z->parent->left=y;
        }
        y->right = z;
        z->parent=y;
        z->left = t3;
        if(t3) t3->parent=z;

        update_height(z);
        return y;

    }

    Node* RRrotation(Node* z)
    {
        Node* y=z->right;
        Node* t3=y->left;

        if(z==root)
        {
            root=y;
            y->parent=z->parent;
        }
        else
        {
            y->parent=z->parent;
            if(z==z->parent->right) z->parent->right=y;
            else z->parent->left=y;
        }
            y->left=z;
            z->parent=y;
            z->right=t3;
            if(t3) t3->parent=z;

            update_height(z);

        return y;
    }

     Node *LCA(int p, int q)
     { //iterative implementation
         Node *tmp = root;
         while (tmp)
         {
             if (tmp->data > p && tmp->data > q)
                 tmp = tmp->left;
             else if (tmp->data < p && tmp->data < q)
                 tmp = root->right;
             else
                 break;
         }
         return tmp;
     }

    void print_avl()
    {
        inorder(root);
    }
    void printRoot()
    {
        cout<<"Root="<<root->data<<endl;
    }

};

      main()
    {
        AVLtree tree;
        int in,n1,n2;
        while(cin>>in && in!=-1)
        {
            tree.insert(in);

        }
        cout << "Status: ";
        tree.print_avl();
        cin>>in;
        while(in--)
        {
         cin>>n1>>n2;
        cout<<tree.LCA(n1,n2)->data<<endl;
        }
        cout << endl;
    }
