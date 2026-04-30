/**
 * @file assn2.cpp
 * @author Patrick McGrath, VIU
 * @version 1.0
 * @date September, 2023
 * 
 *  Assignment #2 - C++ AVL Binary Search Tree implementation
 *  Copyright (C) 2023  Patrick McGrath
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>


// struct for each node in list
// data set to 0
// prev and next set to null
struct Node{
    int data = 0;
    int height = 0;
    Node* left = NULL;
	Node* right = NULL;
};

// declarations
int height(Node *N);
int max(int a, int b);
Node *llrotation(Node *y);
Node *rrrotation(Node *x);
int getBalance(Node *N);
Node *insert(Node* node, int data);
Node *newnode(int data);
int searchfor(Node* root, int tint);
Node* delnod(Node* root, int data);
Node* findmax(Node* root);
Node* findmin(Node* root);
Node* inordsuc(Node* root, Node* tnode);
Node* searchfornode(Node* root, int tint);
Node* parentof(Node* root, Node* tnode);
Node* commanc(Node* root, Node* tnode, Node* tnode1);
int nodedist(Node* start, Node* end);
void printall(Node* root);
void postord(Node* root);
void preord(Node* root);
void freemem(Node* root);


// The first functions are the ones I wrote. Afterwards are a few provided to the class to use in the assignment.


// A function to get a new node with the passed data value
Node *newnode(int data){
    Node *temp = new Node;
    if (temp != NULL){
        temp->data = data;
    }
    return temp;
}

// A funtion for searching for an element
int searchfor(Node* root, int tint){

    // check if root is null
    if (root != NULL){
        // if tree isnt null, check if it is the value
        if (root->data == tint){
            std::cout << "Element " << tint << " is in the tree" << std::endl;
            return 1;
        } else {
            // tree is not empty, check other nodes for data
            Node* temp = root;
            // while loop for moving temp through tree
            while (temp->data != tint){
                // check if tint is less than temp's data
                if (tint < temp->data){
                    // move temp left
                    temp = temp->left;
                    // check if temp is now null,
                    // if so, tint is not there
                    if (temp == NULL){
                        std::cout << "Element " << tint << " is not in the tree" << std::endl;
                        return 0;
                    } else if (temp->data == tint) {
                        // check if tint has been found
                        std::cout << "Element " << tint << " is in the tree" << std::endl;
                        return 1;
                    }
                } else {
                    // tint is not less than temp's data
                    // similar to above but in opposite side
                    temp = temp->right;
                    if (temp == NULL){
                        std::cout << "Element " << tint << " is not in the tree" << std::endl;
                        return 0;
                    } else if (temp->data == tint){
                        std::cout << "Element " << tint << " is in the tree" << std::endl;
                        return 1;
                    }
                }
                // at this point if tint was found or temp went to null, return will be made
                // if not, temp is at one of its children. while loop repeats on this child
            }
        }
    }
    std::cout << "BST is empty. Element not found" << std::endl;
    return 0;
}

// similar function to above searchfor, but returns pointer instead
Node* searchfornode(Node* root, int tint){

    // check if root is null
    if (root != NULL){
        // if it isnt null, check if it is the value
        if (root->data == tint){
            return root;
        } else {
            // tree is not empty, check other nodes for data
            Node* temp = root;
            // while loop for moving temp through tree
            while (temp->data != tint){
                // check if tint is less than temp's data
                if (tint < temp->data){
                    // move temp left
                    temp = temp->left;
                    // check if temp is now null,
                    // if so, tint is not there
                    if (temp == NULL){
                        return NULL;
                    } else if (temp->data == tint) {
                        // check if tint has been found
                        return temp;
                    }
                } else {
                    // tint is not less than temp's data
                    // similar to above but in opposite side
                    temp = temp->right;
                    if (temp == NULL){
                        return NULL;
                    } else if (temp->data == tint){
                        return temp;
                    }
                }
                // at this point if tint was found or temp went to null, return will be made
                // if not, temp is at one of its children. while loop repeats on this child
            }
        }
    }
    return NULL;
}







// A function for deleting a node
// only call if data is known to be in tree
Node* delnod(Node* root, int data){ 
     
    // check if root is null
    if (root == NULL) 
        return NULL; 
 
    // check if data is smaller than root,
    // recursively call delnod on left child, passing left child as "root"
    if (data < root->data){
        root->left = delnod(root->left, data); 
    } else if(data > root->data){
    // otherwise the data either larger than root or is root
    // first check larger, and thus right child
    // again call recursively
        root->right = delnod(root->right, data); 
    } else {



    // if here, then the data is same as roots, perform deletion on that one
    // (base case)

        // first, check if node has less than 2 children
        if((root->left == NULL) || (root->right == NULL)) { 
        
            // if left child not null, point temp there, otherwise, point it to right child
            Node* temp = NULL;
            if (root->left != NULL){
                temp = root->left;
            } else {
                temp = root->right;
            }

            // check if childless
            // temp will point to null
            if (temp == NULL){ 
                // then point temp to "root", the one being deleted
                // and clear current pointer to root to say it was childless later
                temp = root; 
                root = NULL; 

                // if temp is not null, then root has 1 child and temp is it
            } else {
                // root is the node being deleted, 
                // copy info from temp to root
                // then actually delete temp
                root->data = temp->data;
                root->left = temp->left;
                root->right = temp->right;

            }
            // delete the temp node that was either the leaf node being deleted
            // or the former single child, whose contents were moved to the passed node
            delete temp;



        } else { 
            // the node being deleted, root, has 2 children
            // temp will point to the smallest node in the right child tree
            Node* temp = findmin(root->right); 
 
            // Copy that node's data into root, replacing whats being deleted
            // but retaining the child linking
            root->data = temp->data;
 
            // recursively recall this function on the right sub tree to then remove
            // the smallest node the right child tree,
            // since that node is moved to where root was.
            root->right = delnod(root->right, temp->data); 
        } 
    } 
 
    // If the tree had only one node
    // then return  null, this is from the if statement checking for childless
    if (root == NULL){
        return NULL; 
    }
 
    // update current node height
    root->height = max(height(root->left), height(root->right)) + 1;

 
    // check whether this node is unbalanced
    int bal = getBalance(root); 

    // if bal is -1, 0, or 1 then root is balanced
    // otherwise bal will be bal>1 or bal<-1
    // A    bal>1 means left side is taller
    // B    bal<-1 means right side is taller
    // for each there are 2 cases
    // A) since bal>1 is left child larger, you check the balance of roots left child
    // A1) if it is greater than or equal to 0, you do a LL rotation on root, return it
    // A2) if it is smaller than 0, you do an RR rotation on that left child,
    // then you do a LL rotation on the root, return it
    // B) since bal<-1 is right child larger, you check thebalance of the right child
    // B1) if it is less than or equal to 0, you do an RR rotation on root, return it
    // B2) if it is greater than 0, you do an LL rotation on the right child
    // then an RR rotation on the root, return it

 
 
    // A1
    if (bal > 1 && getBalance(root->left) >= 0){
        return llrotation(root); 
    }
 
    // A2
    if (bal > 1 && getBalance(root->left) < 0){ 
        root->left = rrrotation(root->left); 
        return llrotation(root); 
    } 
 
    // B1 
    if (bal < -1 && getBalance(root->right) <= 0){
        return rrrotation(root); 
    }
 
    // B2 
    if (bal < -1 && getBalance(root->right) > 0){ 
        root->right = llrotation(root->right); 
        return rrrotation(root); 
    } 
 
    // return new root
    return root; 
}






// A function for finding the maximum element
Node* findmax(Node* root){

    // check if root is null, return null to indicate that
    if (root == NULL){
        return NULL;
    } else {

        // else, bst is not empty
        // make temp node to go down right hand side
        // until temp's right is null
        // return temp
        Node* temp = root;
        while (temp->right != NULL){
            temp = temp->right;
        }
        return temp;
    }
    return NULL;
}


// A function for finding the minimum element
// same as findmax, just left hand side
Node* findmin(Node* root){
    if (root == NULL){
        return NULL;
    } else {
        Node* temp = root;
        while (temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }
    return NULL;
}



// A function for finding a node's parent
// should already determine if tnode is in tree
// returns null if root is null
// returns null if tnode is root
Node* parentof(Node* root, Node* tnode){

    // check if root is null
    if (root == NULL){
        return NULL;
    } else if (tnode == root){
        return NULL;
    } else {
        Node* parent = root;
        while (parent->left != tnode && parent->right != tnode){
            if (tnode->data < parent->data){
                parent = parent->left;
            } else {
                parent = parent->right;
            }
        }
        return parent;
    }
    return NULL;
}




// A function for find the next in order successor of a value in tree
// returns node of successor, or NULL if tree is empty, or tnode if tnode is max
// should only call if tint has been determined to exist in tree
Node* inordsuc(Node* root, Node* tnode){

    // check if root is NULL
    if (root == NULL){
        return NULL;
    // check if tnode is max node
    } else if (tnode == findmax(root)){
        return tnode;
    } else {
        // tnode exists, is not max
        // check if tnode is root, and it is not max, it will have right child
        // return its right child's tree's min value
        if (tnode == root){
            return findmin(tnode->right);
        } else {
            // if tnode has a right child, return that child's minimum value
            if (tnode->right != NULL){
                return findmin(tnode->right);
            } else {

                // tnode has no right child
                // check if tnode is a left child or right child of its parent
                // if left child, return parent
                // if right child, must go up tree until it gets to an ancestor that is a left child to its parent
                // then return that parent

                // node pointer to find tnode's parent
                Node* temp = parentof(root, tnode);
                // check if tnode is left child of parent
                if (tnode == temp->left){
                    return temp;
                }
                // else, need 2nd pointer to move up.
                // temppar is parent of temp
                // while loop moving up until temp is a left child of temppar
                // then return temppar
                Node* temppar = parentof(root, temp);
                while (temp != temppar->left){
                    temp = temppar;
                    temppar = parentof(root, temp);
                }
                return temppar;
            }
        }
    }
    return NULL;
}


// A function for finding the common ancestor of two nodes
Node* commanc(Node* root, Node* tnode1, Node* tnode2){
    // check if any parameters are null
    if (root == NULL || tnode2 == NULL || tnode2 == NULL){
        return NULL;
    }

    // check if either tnode1 or tnode2 is root, it is common ancestor
    if (tnode1 == root){
        return tnode1;
    }
    if (tnode2 == root){
        return tnode2;
    }

    // if tnode1 and tnode2 are both left of root
    if (tnode1->data < root->data && tnode2->data < root->data){
        // call recursively on left child
        return commanc(root->left, tnode1, tnode2);

        // else if only tnode1 is less than
    } else if (tnode1->data < root->data){
        // tnode1 will be left of root, and tnode2 will be right of it, tnode2 being less than or equal to root has already been checked
        return root;
    } else if (tnode2->data < root->data){
        // same thing, but for the other node
        return root;
    } else {
        // both tnode1 and tnode2 are not less than root
        // call recursively on right child
        return commanc(root->right, tnode1, tnode2);
    }
    return NULL;
}


// A function for finding the vertical distance between 2 nodes
int nodedist(Node* start, Node* end){
    int i = 0;
    // check if eithers null
    if (start == NULL || end == NULL){
        return 0;
    } else {
        // temp node pointer to go from start to end counting how many steps
        // while loop will check if they are the same to start and i will equal 0
        Node* temp = start;
        while (temp != end){
            if (end->data < temp->data){
                temp = temp->left;
            } else {
                temp = temp->right;
            }
            i++;
        }
    }
    return i;
}


// A function for printing tree in order
void printall(Node* root){
    if (root == NULL){
        std::cout << "Tree is empty" << std::endl;
    } else {

        // if root is not null
        // first recursively calls it on non-null left child
        // then prints root value
        // then recursively calls on non-null right child
        if (root->left != NULL){
            printall(root->left);
        }
        std::cout << root->data << "     ";
        if (root->right != NULL){
            printall(root->right);
        }
    }
    return;
}


// A function for postorder traversal of BST
void postord(Node* root){
    if (root == NULL){
    std::cout << "Tree is empty" << std::endl;
    return;
    }

    if (root->left !=NULL){
        postord(root->left);
    }
    if (root->right != NULL){
        postord(root->right);
    }
    std::cout << root->data << "    ";
    return;
}
// A function for preorder traversal of BST
void preord(Node* root){
    if (root == NULL){
        std::cout << "Tree is empty" << std::endl;
        return;
    }

    // print current node;
    std::cout << root->data << "    ";

    // if left child is not null, recursively call on it
    if (root->left != NULL){
        preord(root->left);
    }
    // then if right child is not null, recursively call on that
    if (root->right != NULL){
        preord(root->right);
    }
    return;
}


// A function for freeing memory from tree at end of program
void freemem(Node* root){
    if (root == NULL){
        return;
    }

    // recursively call on both sides of passed node
    if (root->left != NULL){
        freemem(root->left);
    }
    if (root->right != NULL){
        freemem(root->right);
    }

    // here both children will be empty
    // delete and return
    delete root;
    return;
}





// The following functions were provided to the class


// A function to get the height of the tree
int height(struct Node *N){
    if (N == NULL){
        return -1;
    }
    return N->height;
}


// A function to get maximum of two integers
int max(int a, int b){
    return (a > b)? a : b;
}


// A function to do an LL rotation
Node *llrotation(Node *y){
    Node *x = y->left;
    Node *T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    // Return new root
    return x;
}


// A function to do an RR rotation
Node *rrrotation(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    // Return new root
    return y;
}


// Get Balance factor of node N
int getBalance(Node *N){
    if (N == NULL)
    return 0;
    return height(N->left) - height(N->right);
}


// Recursive function to insert a data in the subtree rooted with 
// node and returns the new root of the subtree.
Node *insert(Node* node, int data){
    /* 1. Perform the normal BST insertion */
    if (node == NULL){
        return(newnode(data));
    }
    if (data < node->data){
        node->left = insert(node->left, data);
    } else if (data > node->data){
        node->right = insert(node->right, data);
    }
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),height(node->right));
    /* 3. Get the balance factor of this ancestor node to check
    whether this node became unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && data < node->left->data){
        return llrotation(node);
    }
    // Right Right Case
    if (balance < -1 && data > node->right->data){
        return rrrotation(node);
    }
    // Left Right Case
    if (balance > 1 && data > node->left->data){
        node->left = rrrotation(node->left);
        return llrotation(node);
    }
    // Right Left Case
    if (balance < -1 && data < node->right->data){
        node->right = llrotation(node->right);
        return rrrotation(node);
    }
    /* return the root node pointer */
    return node;
}




// main function (my work again)	
int main(){

    // string for user input
    std::string input = "";
    std::string input1 = "";

    // prompt and input
    std::cout << "How many nodes are in the BST?" << std::endl;
    std::cin >> input;

    // convert input to int
    int BST = std::stoi(input);

    // temp ints for further user input, function results
    int tint = 0;
    int tint1 = 0;
    int tint2 = 0;
    int tint3 = 0;
    int result = 0;

    // root node and temp nodes
    Node *root = NULL;
    Node *tnode = NULL;
    Node *tnode1 = NULL;
    Node* tnode2 = NULL;

    // while loop for adding new nodes until the desired size
    while (BST != 0){

        // prompt and input
        std::cout << "Enter the data for next node in BST" << std::endl;
        std::cin >> input;
        tint = stoi(input);

        // check if its the first insert, and thus is also the root
        if (BST == 1){
            root = insert(root, tint);
        } else {
            // else insert
            root = insert(root, tint);
           // Node *nnode = insert(root, tint);
        }

        // reduce BST size still needed
        BST--;
    }

    // prompt
    std::cout << "What operations do you want to perform on the BST" << std::endl;
    std::cout << "Enter 1 to search for the data in BST" << std::endl;
    std::cout << "Enter 2 to insert new node in the BST" << std::endl;
    std::cout << "Enter 3 to delete a node from the BST" << std::endl;
    std::cout << "Enter 4 to find height of the BST" << std::endl;
    std::cout << "Enter 5 to find maximum node from BST" << std::endl;
    std::cout << "Enter 6 to find minimum node from the BST" << std::endl;
    std::cout << "Enter 7 to find inorder succesor of a node" << std::endl;
    std::cout << "Enter 8 to find distance between two nodes" << std::endl;
    std::cout << "Enter 9 to find inorder traversal of nodes" << std::endl;
    std::cout << "Enter 10 to find preorder traversal of nodes" << std::endl;
    std::cout << "Enter 11 to find postorder traversal of node" << std::endl;
    std::cout << "Enter Q to quit" << std::endl;
    std::cin >> input;

    // while loop for continuous entry
    while (input != "q" && input != "Q"){
        tint = std::stoi(input);
        if (tint < 1 || tint > 11){
            tint = 0;
        }

        // switch case for input
        switch (tint){
            case 0:
                std::cout << "Please enter a number from 1-11 or Q" << std::endl;
                break;
            case 1:
                std::cout << "Enter the element to be searched" << std::endl;
                std::cin >> input;
                tint = std::stoi(input);
                result = searchfor(root, tint);
                break;
            case 2:
                std::cout << "Enter the data for the element to be inserted" << std::endl;
                std::cin >> input;
                tint = std::stoi(input);
                root = insert(root, tint);
                break;
            case 3:
                std::cout << "Enter the data for the element to be deleted" << std::endl;
                std::cin >> input;
                tint = std::stoi(input);
                tnode = searchfornode(root, tint);
                if (tnode != NULL){
                    root = delnod(root, tint);
                } else {
                    std::cout << "Could not delete element " << tint << ". It is not in the tree" << std::endl;
                }
                break;
            case 4:
                if (root != NULL){
                    std::cout << "The height of the BST is " << root->height << std::endl; 
                } else {
                    std::cout << "BST is empty. Height is 0" << std:: endl;
                }
                break;
            case 5:
                tnode = findmax(root);
                if (tnode == NULL){
                    std::cout << "BST is empty, there is no max" << std::endl;
                } else {
                    std::cout << "The maximum element in BST is " << tnode->data << std::endl;
                }
                break;
            case 6:
                tnode = findmin(root);
                if (tnode == NULL){
                    std::cout << "BST is empty, there is no min" << std::endl;
                } else {
                    std::cout << "The minimum element in BST is " << tnode->data << std::endl;
                }
                break;
            case 7:
                std::cout << "Enter the element who's in-order successor is to be found" << std::endl;
                std::cin >> input;
                tint = std::stoi(input);
                tnode = searchfornode(root, tint);
                // if tint is found, tnode points to it
                if (tnode != NULL){
                    // check if tnode is max node
                    tnode1 = inordsuc(root, tnode);
                    if (tnode == tnode1){
                        std::cout << "There is no successor to " << tint << ". It is the max node" << std::endl;
                    } else {
                        std::cout << "The successor to " << tint << " is " << tnode1->data << std::endl;
                    }
                } else {
                    std::cout << "Element " << tint << "is not in tree" << std::endl;
                }
                break;
            case 8:
                std::cout << "Enter the first element whose distance is to be found" << std::endl;
                std::cin >> input;
                tint = std::stoi(input);
                tnode = searchfornode(root, tint);
                if (tnode == NULL){
                    std::cout << "Element " << tint << " is not in the tree" << std::endl;
                    break;
                } else {
                    std::cout << "Enter the second element whose distance is to be found" << std::endl;
                    std::cin >> input;
                    tint1 = std::stoi(input);
                    tnode1 = searchfornode(root, tint1);
                    if (tnode1 == NULL){
                        std::cout << "Element " << tint1 << " is not in the tree" << std::endl;
                        break;
                    } else {
                        // tnode and tnode1 are in tree, find their common ancestor
                        tnode2 = commanc(root, tnode, tnode1);
                        //find distance between tnode/tnode2 and tnode1/tnode2
                        tint2 = nodedist(tnode2, tnode) + nodedist(tnode2, tnode1);
                        std::cout << "Distance between nodes " << tint << " and " << tint1 << " is " << tint2 << std::endl;
                        break;
                    }
                }
                break;
            case 9:
                printall(root);
                std::cout << "" << std::endl;
                break;
            case 10:
                preord(root);
                std::cout << "" << std::endl;           
                break;
            case 11:
                postord(root);
                std::cout << "" << std::endl;    
                break;
            default:
                break;
        }

        input = "";
        input1 = "";
        tint = -1;
        tint1 = -1;
        tint2 = -1;
        tint3 = -1;
        result = -1;
        tnode = NULL;
        tnode1 = NULL;
        tnode2 = NULL;
        // prompt for next input
        std::cout << "Enter your next choice between 1 to 11 or Q" << std::endl;
        std::cin >> input;
    }

    //memory deletion
    freemem(root);

    // goodbye
    std::cout << "Goodbye" << std::endl;
	return 0;
}