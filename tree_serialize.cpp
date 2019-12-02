
// A C++ Program serialize and deserialize an N-ary tree 
#include<stdio.h> 
#include<bits/stdc++.h>
#define MARKER -1.0 //"}"
using namespace std; 
  
// A node of N-ary tree 
struct Node { 
   double lat;
   double lon; 
   int no;
   vector<Node *> child;
}; 
  
// A utility function to create a new N-ary tree node 
Node *newNode(double lat, double lon ) 
{ 
    Node *temp = new Node; 
    temp->lat = lat;
    temp->lon = lon; 
    return temp; 
} 
  
// This function stores the given N-ary tree in a file pointed by fp 
void serialize(Node *root, FILE *fp) 
{ 
    // Base case 
    if (root == NULL) return; 
  
    // Else, store current node and recur for its children 
    fprintf(fp, "%lf ", (double)root->no);
    fprintf(fp, "%lf ", root->lat);
    fprintf(fp, "%lf ", root->lon);  
    int N=root->no;
    for (int i = 0; i < N && root->child[i]; i++) 
         serialize(root->child[i],  fp); 
} 

int deSerialize(Node *&root, FILE *fp) 
{ 
    double no; 
    if ( !fscanf(fp, "%lf ", &no) || no== MARKER ) return 1; 

    double val_lat,val_lon;

    fscanf(fp, "%lf ", &val_lat) ;
    fscanf(fp, "%lf ", &val_lon) ;

    root=newNode(val_lat, val_lon);
    root->lat=val_lat;
    root->lon=val_lon; 

    root->no=no;
    cout << no << "lol" <<endl;

    for (int i = 0; i < no; i++) 
    {  
      Node temp;
      root->child.push_back(&temp);
      deSerialize(root->child[i], fp);
    } 
    return 0; 
} 
  
// A utility function to create a dummy tree shown in above diagram 
Node *createDummyTree() 
{ 
    Node *root = newNode(0,0); 

    root->child.push_back(newNode(1.1,0.0)); 
    root->child.push_back(newNode(1.2,0.0)); 
    root->child.push_back(newNode(1.3,0.0)); 

    root->child[0]->child.push_back( newNode(2.11,0.0)); 
    root->child[0]->child.push_back( newNode(2.12,0.0)); 

    root->child[2]->child.push_back( newNode(2.31,0.0)); 
    root->child[2]->child.push_back( newNode(2.32,0.0)); 
    root->child[2]->child.push_back( newNode(2.33,0.0)); 
    root->child[2]->child.push_back( newNode(2.34,0.0)); 

    root->child[0]->child[1]->child.push_back( newNode(3.111,0.0)); 
    root->no=3;
    
    root->child[0]->no=2;
    root->child[1]->no=0;
    root->child[2]->no=4;

    root->child[0]->child[0]->no=0;
    root->child[0]->child[1]->no=1;
    root->child[2]->child[0]->no=0;
    root->child[2]->child[1]->no=0;
    root->child[2]->child[2]->no=0;
    root->child[2]->child[3]->no=0;

    root->child[0]->child[1]->child[0]->no = 0; 
    return root; 
} 
  
// A utlity function to traverse the constructed N-ary tree 
void traverse(Node *root) 
{ 
    if (root) 
    { 
        printf("(%lf , %lf) ", root->lat, root->lon); 
        cout << endl;
        int N= root->no;
        if(N==0) cout << endl;
        for (int i = 0; i < N; i++) 
            traverse(root->child[i]); 
    } 
} 
  
// Driver program to test above functions 
int main() 
{ 
    Node *root = createDummyTree(); 
    traverse(root); 

    FILE *fp = fopen("/home/vib2810/Algorithms/tree.txt", "w"); 
    if (fp == NULL) 
    { 
        puts("Could not open file"); 
        return 0; 
    } 
    serialize(root, fp); 
    fclose(fp); 
  
    Node *root1 = NULL; 
    fp = fopen("/home/vib2810/Algorithms/tree.txt", "r"); 
    deSerialize(root1, fp); 
  
    printf("Constructed N-Ary Tree from file is \n"); 
    traverse(root1); 
    
  
    return 0; 
}
