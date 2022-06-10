using namespace std;

class node {
    //constructor
    node();
    //destructor
    ~node(); 
    node* left;
    node* right;
    node* parent;
    int val;
    int color;
}
