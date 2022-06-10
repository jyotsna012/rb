#include <iostream>
#include "node.h"
#include <fstream>

using namespace std;

node* insert(node* head, int data, node* newRoot, node* prev){
 if(head == NULL){
  head = new node();
  head -> val = data;
  head -> color = 0;
  newRoot = head;
  cout << "I am a head node" << endl;	 
 }
 else{
  if(newRoot == NULL){
     newRoot = new node();
     newRoot -> val = data;
     newRoot -> parent = prev;
     cout << "added" << endl;	  
     return newRoot;
  }
  else if(data <= newRoot->val){
    prev = newRoot;
    newRoot -> left = insert(head, data, newRoot->left, prev);
  }
  else{
    prev = newRoot;
    newRoot -> right = insert(head, data, newRoot->right, prev);
  }
  return newRoot;
 
 }
}

//used the same algorithim from Geeks for Geeks https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print(node *root, int space)
{
    if (root == NULL){
        return;
    }else{
    space += 5;
    print(root->right, space);
    cout<<endl;
    for (int i = 0; i < space; i++)
        cout<<" ";
    cout<< "( " << root->val<< ", " << root -> color << ", " << root -> parent << " )"<< "\n";
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
	
    node* head = NULL;
    for(int a = 0; a < numelements; a++){
        node* rootNew = head;
        node* prev = NULL;
        insert(head, arr[a], head, prev);
	cout << head -> val << endl;
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
          insert(root, toAdd, root, prev);          
      }
   
  }  

}
