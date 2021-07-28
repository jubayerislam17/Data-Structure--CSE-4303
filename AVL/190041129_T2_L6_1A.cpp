/*
Task-2

Utilize the functions implemented in Task-1 to provide a complete solution for maintaining a ‘Balanced BST.’ 
The program will continue inserting values until it gets -1. For each insertion, it checks whether the newly inserted node has imbalanced any node or not. If any imbalanced node is found, ‘rotation’ is used to fix the issue.

Your program must include the following functions:
Void insertion (key) 		// iteratively inserts key
Void update_height(node)	// update the height of a node
Int height(node)			// returns the height of a node
Int balance_factor(node)	// returns balance factor
Left_rotate(node)
Right_rotate(node)
check_balance(node):
check if a node is imbalanced and calls relevant rotations.
print_avl(root)			// inorder traversal

Sample Input
Sample Output
12
12(0)
Balanced
Root=12
9
9(0) 12(1)
Balanced
Root=12
5
5(0) 9(1) 12(2)
Imbalance at node: 12
LL case
right_rotate(12)
Status: 5(0) 9(0) 12(0)
Root=8
11
5(0) 9(-1) 11(0) 12(1)
Balanced
Root=9
20
5(0) 9(-1) 11(0) 12(0) 20(0)
Balanced
Root=9
15
5(0) 9(-2) 11(0) 12(-11) 15(0) 20(1)
Imbalance at node: 9
RR case
Left_rotate(9)
Status: 5(0) 9(0) 11(0) 12(0) 15(0) 20(1)
Root=12
7
5(-1) 7(0) 9(1) 11(0) 12(1) 15(0) 20(1)
Balanced
Root=12
3
3(0) 5(0) 7(0) 9(1) 11(0) 12(1) 15(0) 20(1)
Balanced
Root=12
6
3(0) 5(-1) 6(0) 7(1) 9(2) 11(0) 12(1) 15(0) 20(1)
Imbalance at node: 9
LR Case
Left_rotate(5), right_rotate(9)
3(0) 5(0) 6(0) 7(0) 9(-1) 11(0) 12(1) 15(0) 20(1)
Root=12
27
3(0) 5(0) 6(0) 7(0) 9(-1) 11(0) 12(1) 15(0) 277(0) 20(0)
Balanced
Root=12
-1
Status: 3(0) 5(0) 6(0) 7(0) 9(-1) 11(0) 12(1) 15(0) 20(0) 27(0)


Note:
Do not use any recursive implementation
The status of the tree is finally supposed to be like this:
12(1)
				    /       \
				   7(0)       20(0)
				  /  \      /    \
				5(0)	9(0) 15(0)  27(0)
			     /  \	  \
			  3(0)   6(0)  11(0)
-----------------------------------------------------------------------------

12(0)	->	12(1)	->	12(2) -> LL Case				9(0)
/		/	   Right_rotate(12)	   	     /	    \
    9(0)	    9(1)				         5(0)    12(0)
    /
  5(0)
-----------------------------------------------------------------------------
9(-1)			9(-1)				9(-2)
    /	   \		     /    \			     /    \
   5(0)  12(1)  ->    5(0)  12(0)	  ->     5(0)   12(-1)	
        /                  /   \                /   \
      11(0)               11(0) 20(0)        11(0)  20(1)
  							      /
                                                 15(0) 
-----------------------------------------------------------------------------
->imbalance at(9)			12(0)			     12(1)	
  RR Case			    /      \			    /      \
  Left_rotate(8)           9(0)      20(1)  ->	 9(1)      20(1)
				 /  \       /		       /  \       /
			    5(0)  11(0)  15(0)	     5(-1)  11(0)  15(0)
								  \
								  7(0)
-----------------------------------------------------------------------------
12(1)					12(1)
          /      \				    /      \
 9(1)      20(1)			 9(2)      20(1)
      /  \       /				/  \       /
   5(0)  11(0)  15(0)	->	    5(-1)  11(0)  15(0)	
  /    \				   /    \
3(0)    7(0)				 3(0)    7(1)
						   /
                                       6(0)	
-----------------------------------------------------------------------------
Imbalance at node(9), LR Case			12(1)
Left_rotate(5)   			          /       \
	   					 9(2)       20(1)
						/   \      /
					     7(2)  11(0) 15(0)
                                  /
					   5(0)
					  /  \
					3(0)  6(0)
-----------------------------------------------------------------------------
Right_rotate(9)			12(1)
				    /      \
				   7(0)      20(1)
				  /  \      /
				5(0)	9(-1) 15(0)
			     /  \	  \
			  3(0)   6(0)  11(0)
-----------------------------------------------------------------------------

12(1)
				    /       \
				   7(0)       20(0)
				  /  \      /    \
				5(0)	9(-1) 15(0)  27(0)
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
        inorder(root);
        printf("Imbalance at Node: %d\n", x->data);
        if (bf > 1 and val < x->left->data)
            {
                printf("LL case\nRight_rotate(%d)\n", x->data);
                LLrotation(x);
            }
        else if (bf > 1 and val > x->left->data)
            {
                printf("LR case\nLeft_rotate(%d)\nRight rotate(%d)", x->left->data,x->data);
                x->left=RRrotation(x->left);
                 LLrotation(x);
            }
        else if (bf < -1 and val > x->right->data)
              {
                  printf("RR case\nLeft_rotate(%d)\n", x->data);

                 RRrotation(x);
            }
        else if (bf < -1 and val < x->right->data)
        {
            printf("RL case\nRight_rotate(%d)\nLeftt rotate(%d)", x->right->data,x->data);
            x->right=LLrotation(x->right);
            RRrotation(x);
        }

        printf("Status: ");
        inorder(root);
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

         if (!check)
        {
            inorder(root);
            printf("Balanced\n");
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
        int in;
        while(cin>>in && in!=-1)
        {
            tree.insert(in);
            tree.printRoot();
            cout<<endl;
        }
        cout << "Status: ";
        tree.print_avl();
        cout << endl;
    }
