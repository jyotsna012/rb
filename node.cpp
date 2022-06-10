#include<iostream>
#include "node.h"

using namespace std;

node::node() {
  val = 0;
  color = 1; //red
  left = NULL;
  parent = NULL;
  right = NULL;
}

node::~node() { 
  left = NULL;
  parent = NULL;
  right = NULL;
}
