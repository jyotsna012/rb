#include <iostream>
#include "node.h"
#include <fstream>

using namespace std;

void setProperties(node* &head, node* &newNode);

void right(node* &root){
	cout << root -> val << endl;
	//node* currentLeft = current -> left;
	//current -> left = currentLeft -> right;
	
}

void left(){

}

void reColor(node* &head, node* &parent, node* &grandParent, node* &uncle){
	parent -> color = 0;
	uncle -> color = 0;
	if(grandParent -> parent != NULL){
		grandParent -> color = 1;
		setProperties(head, grandParent);
	}
}

void setProperties(node* &head, node* &newNode){
	cout << "in set properties" << endl;
	cout << "test 1" << endl;
	if(newNode -> parent == NULL){
		cout << "node is root" << endl;
	}
	else if(newNode -> parent -> color != 0){
		node* grandParent = newNode -> parent-> parent;
		cout << "the parent is red" << endl;
		if(newNode -> parent == grandParent->left){
			cout << "test 2" << endl;
			node* uncle = grandParent->right;
			cout << "text 3" << endl;
			if(uncle != NULL){
				cout << "test 4" << endl;
				if(uncle -> color == 1){
					reColor(newNode, newNode -> parent, grandParent, uncle);
				}
			}else if(uncle == NULL|| uncle -> color == 0){
				//
				cout << "uncle black or null" << endl;
			  	//left left case
			  	if(newNode == newNode -> parent -> left){
				  //rotate right
				  //recolor
				  cout << "ll" << endl;
				  right(newNode -> grandParent);
			  	}
				//left right case
				else if(newNode == newNode -> parent -> right){
				   //rotate right, rotate right, recolor
				   cout << "lr" << endl;
				
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
				   //rotate left
				   //recolor
				   cout << "rr" << endl;	
				//right left case
				}else if(newNode == newNode -> parent -> left){
				   //rotate left, rotate left, recolor
				   cout << "rl" << endl;
				}
			}		
		
		}
	}
}

node* insert(node* &head, int data, node* &newRoot, node* &prev, node* &current){
 if(head == NULL){
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
	  cout << "new root real: " << newRoot -> val << endl;
     return newRoot;
  }
  else if(data <= newRoot->val){
    prev = newRoot;
    newRoot -> left = insert(head, data, newRoot->left, prev, current);
  }
  else{
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
	
    node* root = NULL;
    for(int a = 0; a < numelements; a++){
        node* rootNew = root;
        node* prev = NULL;
	node* current = new node();
        root = insert(root, arr[a], rootNew, prev, current);
	setProperties(root, current);
    }	
     
    int choice = 0;
    bool tf = true;
    while(tf == true){
      cout << "What would you like to do? Type 1 to add, Type 4 to print, Type 5 to quit" << endl;
      cin >> choice;
      cin.get();
      if(choice == 5){
          tf =false;
      }else if(choice == 4){
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
	  cout << "call set properties for trial" << endl;
          setProperties(root, current);    
      }
   
  }  

}
