//jyotsna tera
//june 10th 2022
//red balck tree - insert
// creates a red black tree which can take in new number and make sure that the tree is still balanced accoring to properties

//sources used: 
//https://www.youtube.com/watch?v=UaLIHuR1t8Q&t=616s - Reb Black Tree Insertion
//https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/ 

#include <iostream>
#include "node.h"
#include <fstream>

using namespace std;

//function prototype
void setProperties(node* &head, node* &newNode);
void left(node* &root, node* &realRoot);
void right(node* &root, node* &realRoot);

node* FindMin(node* root)
{
 while(root->left != NULL) root = root->left;
 return root;
}

node* Delete(node* root, node* current){
	if(current -> color == 1){
		cout << "in here" << endl;
		if(root == NULL){
		return root;
		}else if(current -> val < root -> val){
			cout << "in 1" << endl;
		root -> left = Delete(root->left, current);
		}else if(current -> val > root -> val){
			cout << "in 2" << endl;
		root -> right = Delete(root->right, current);
		}else{
			cout << "in 3" << endl;
			if(root -> left == NULL && root -> right == NULL){
			delete root;
			root = NULL;
			}else if(root -> left == NULL){
			node* temp = root;
			root = root -> right;
			delete temp;
			}else if(root -> right == NULL){
			node* temp = root;
			root = root -> left;
			delete temp;
			}else{
			node* temp = FindMin(root->right);
			root->val = temp ->val;
			root -> right = Delete(root -> right, temp);
		}
		
	}
	return root;
	}
}


node* Search(node* root, int data){
  if(root == NULL){
     cout << "not found" << endl;
    return NULL;
  }
  else if(root->val == data){
	  cout << "found" << endl;
    return root;
  }
  else if(data <= root->val){
    return Search(root->left, data);
  } 
  else{
    return Search(root->right, data);
  }
}

//function to recolor.
void reColor(node* &head, node* &parent, node* &grandParent, node* &uncle){
	//sets the parents and uncle to black
	parent -> color = 0;
	uncle -> color = 0;
	//sets gp tp red if its not root
	if(grandParent -> parent != NULL){
		grandParent -> color = 1;
		//runs set properties to balnce the new tree
		setProperties(head, grandParent);
	}
}

//function that makes sure all the prpperties of rbtree is met
void setProperties(node* &head, node* &newNode){
	//if the new node is head then nothing need to change
	if(newNode -> parent == NULL){
	}
	//if the parents of the new node is red the red red conflict happens
	else if(newNode -> parent -> color != 0){
		//creats grandparent node
		node* grandParent = newNode -> parent-> parent;
		//new node is left of grandpatent
		if(newNode -> parent == grandParent->left){
			node* uncle = grandParent->right;
			//if uncle of new node is red the recoloring occurs
			if(uncle != NULL){
				if(uncle -> color == 1){
					reColor(newNode, newNode -> parent, grandParent, uncle);
				}
			//if uncle is black or null then rotations occus	
			}else if(uncle == NULL|| uncle -> color == 0){
			  	//left left case
			  	if(newNode == newNode -> parent -> left){
				  //rotate right
				  //recolor
				  right(grandParent, head);
				  //color of parent and grand parent is swapped
				  int tempColor = newNode -> parent -> color;
				  newNode -> parent -> color = grandParent -> color;
				  grandParent -> color = tempColor;
			  	}
				//left right case
				else if(newNode == newNode -> parent -> right){
				   //rotate left, rotate right, swap
				   cout << "in the left right" << endl;
				   left(newNode -> parent, head);
				   cout << "out of left" << endl;
			           right(grandParent, head);
				   cout << "out of right" << endl;
				  int tempColor = newNode -> parent -> color;
				  newNode -> parent -> color = grandParent -> color;
				  grandParent -> color = tempColor;
				}
			}
		}else if(newNode -> parent == grandParent->right){
			node* uncle = grandParent->left;
			if(uncle != NULL){
				cout << "test 4" << endl;
				if(uncle -> color == 1){
					reColor(newNode, newNode -> parent, grandParent, uncle);
				}
			}else if(uncle == NULL || uncle -> color == 0){
				//rotations
				//right right case
				if(newNode == newNode -> parent -> right){
				   left(grandParent, head);
				  int tempColor = newNode -> parent -> color;
				  newNode -> parent -> color = grandParent -> color;
				  grandParent -> color = tempColor;
				   //recolor
				//right left case
				}else if(newNode == newNode -> parent -> left){
					//right rotation, left rotation, swap
				   right(newNode -> parent, head);
				   left(grandParent, head);
				  int tempColor = newNode -> parent -> color;
				  newNode -> parent -> color = grandParent -> color;
				  grandParent -> color = tempColor;
				}
			}		
		
		}
	}
}

//function to insert - same as bst excpet keeps track fo current and previous to assign parent to each node
node* insert(node* &head, int data, node* &newRoot, node* &prev, node* &current){
 if(head == NULL){
  //if the node is the first node then color is set to black
  head = new node();
  head -> val = data;
  head -> color = 0;
  newRoot = head;
  return newRoot;	 
 }
 else{
  if(newRoot == NULL){
     newRoot = new node();
     newRoot -> val = data;
     newRoot -> parent = prev;
     current = newRoot;
     return newRoot;
  }
	 //if new node value is less than root
  else if(data <= newRoot->val){
    prev = newRoot;
	  //turn left
    newRoot -> left = insert(head, data, newRoot->left, prev, current);
  }
  else{//else turn right
    prev = newRoot;
    newRoot -> right = insert(head, data, newRoot->right, prev, current);
  }
  return newRoot;
 
 }
}

//used the same algorithim from Geeks for Geeks https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print(node* &root, int space)
{
    if (root == NULL){
        return;
    }else{
    space += 5;
    print(root->right, space);
    cout<<endl;
    for (int i = 0; i < space; i++)
        cout<<" ";
    if(root -> parent == NULL){	    
    	cout<< "( " << root->val<< ", " << root -> color << ", NULL" << " )"<< "\n";
    }else{
    cout<< "( " << root->val<< ", " << root -> color << ", " << root -> parent -> val << " )"<< "\n";
    }
    print(root->left, space);
    }
}

int main(){
  int* arr = new int[101];
  int numelements = 0;
  int option = 0;
  cout << "enter the number of elements you are inputting" << endl;
  cin >> numelements;
  cin.get();
  cout << "Type 1 below to enter elements maually and type 2 below to upload from a file" << endl;
  cin >> option;
  cin.get();
	
     if(option == 1){
	  //text input: reads numbers from user and adds to array   
          cout << "please enter your elements below. press enter between each one" << endl;       
          for(int i = 0; i < numelements; i++){
               int input;
               cin >> input;
               cin.get();
               arr[i] = input;
          }  
       } else if(option == 2){
	  //file input: reads numbers from file and add   
		  ifstream myFile;
		  char filename[20];
    		cout << "enter file name" << endl;
    		cin >> filename;
    		cin.get();
    		myFile.open(filename);
		for(int a = 0; a < numelements; a++){
	     int in;
      myFile >> in;
      cout << in << endl;
      arr[a] = in;
	     }
    }
	
    //takes all entered values, creates nodes for them, runs insert function	
    node* root = NULL;
    for(int a = 0; a < numelements; a++){
        node* rootNew = root;
        node* prev = NULL;
	node* current = new node();
        root = insert(root, arr[a], rootNew, prev, current);
	setProperties(root, current);
    }	
     
    //gives users choices for next move	
    int choice = 0;
    bool tf = true;
    while(tf == true){
      cout << "What would you like to do? Type 1 to add, Type 2 to Delete, Type 3 to Search, Type 4 to print, Type 5 to quit" << endl;
      cin >> choice;
      cin.get();
      if(choice == 5){
          tf =false;
      }else if(choice == 4){
	 cout << "the first number is the value, the second number is color (1 = red, 0 = black), thirs number is value of parent" << endl;
        print(root, -5);
      }else if(choice == 1){
          numelements++;
          int toAdd;
          cout << "what number do you want to add" << endl;
          cin >> toAdd;
          cin.get();
          node* rootNew = root;
          node* prev = NULL;
          node * current = new node();
	  insert(root, toAdd, rootNew, prev, current);   
	  //set properties called after  each insert to make sure no rbtree rules are violated.
          setProperties(root, current);    
      }else if(choice == 3){
          int number;
          cout << "enter number to search?" <<endl;
          cin>>number;
          if(Search(root,number) != NULL){
            cout << "found" << endl;
          }else{
            cout << "not found" << endl;
          }
      }else if(choice == 2){
           int number;
          cout << "enter number to delete?" <<endl;
          cin>>number;
          if(Search(root,number) != NULL){
            delete(root, Search(root,number));
          }
      }
   
  }  

}

//right rotation
void right(node* &root, node* &realRoot){
	node *temp = root->left;
    	root->left = temp->right;
    	if (root->left != NULL){
        	root->left->parent = root;
	}
    	temp->parent = root->parent;
   	if (root->parent == NULL){
        	realRoot = temp;
	}
    	else if (root == root->parent->right){
        	root->parent->right = temp;
	}else{
        	root->parent->left = temp;
	}
    	temp->right = root;
    	root->parent = temp;	
}
 
//left roation
void left(node* &root, node* &realRoot){
    node *temp = root->right;
    root->right = temp->left;
    if (root->right != NULL){
        root->right->parent = root;
    }
    temp->parent = root->parent;
    if (root->parent == NULL){
        realRoot = temp;
    }else if (root == root->parent->left){
        root->parent->left = temp;
    }else{
        root->parent->right = temp;
    }
    temp->left = root;
    root->parent = temp;
}

