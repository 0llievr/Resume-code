/**
 * @file rbtree.cpp
 *
 * @brief functions for red black tree 
 *
 * @author Oliver Lynch
 * @date 11/22/19
 */

#include <iostream>
#include <iomanip>
#include "rbtree.h"
#include "rbapp.h"


using std::cout;
using std::setw;
using std::endl;
using std::vector;


// Tree Modifiers/////////////////////////////////////////////////////
/*
 * @brief   tree constructor
 *             sets nil pointers to all point at itself
 */
RBTree::RBTree(){
   nil = new Node();
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = nil;
   
}

/*
 * @brief   tree deconstructor
 *             converts tree into a linked list and deletes each node one by one
 */
RBTree::~RBTree(){
 RBTree::Node* ptr;
    for (RBTree::Node* it = root; it != nil; it = ptr) {
        if (it->left == nil) {
            ptr = it->right;
            delete it;
        }
        else {
            // Rotate the left link into a right link
            ptr = it->left;
            it->left = ptr->right;
            ptr->right = it;
        }
    }
    delete nil;
    delete root;
}

/*
 * @brief   creates a node and passes node to RBInsert
 *          
 * @param   key and value of node
 */
void RBTree::rbInsert(const string& key_, const string& value_){
   
   RBTree::Node* node;
   node = new RBTree::Node(key_, value_);
   rbInsert(node);
}

/*
 * @brief   finds the first node with given key, and checks value with found keys value
 *             if value = value call private RBDelete
 *             if vlaue !=  value, check succesors and predesesors untill value is found
 *             if not found do nothing
 *          
 * @param   key and value of node
 */
void RBTree::rbDelete(const string& key, const string& value_){

   bool found = false;

   RBTree::Node* z;

   z = rbTreeSearch(root, key);
   if(z != nil){      
      if(*(z->value) == value_){
         found = true;
      }
      else{
         //if value is not at the first key found check succesoors and predisesors
         RBTree::Node* ptr_p = z;
         RBTree::Node* ptr_s = z;
            while(!found && (rbTreePredecessor(ptr_p) != nil) 
                     && *(rbTreePredecessor(ptr_p)->key) == key){
               ptr_p = rbTreePredecessor(ptr_p);
               if(*(ptr_p->value) == value_){
                  found = true;
                  z = ptr_p;
               }
            }
            while(!found && (rbTreeSuccessor(ptr_s) != nil) 
                     && *(rbTreeSuccessor(ptr_s)->key) == key){
               ptr_s = rbTreeSuccessor(ptr_s);
               if(*(ptr_s->value) == value_){
                  found = true;
                  z = ptr_s;
               }
            }
      }
      if(found){
         rbDelete(z);
      }
   }
}

/*
 * @brief   Finds ALL nodes with given key
 *             finds first node with key and checks that nodes successors 
 *             and predesessors to see if it also has the same key
 *          
 * @param   key
 * 
 * @return  all nodes with key = key
 */
vector<const string*> RBTree::rbFind(const string& key){
   //returns a vector so you can pop it out?
   RBTree::Node* ptr = root;
   vector<const string*> rval;

   ptr = rbTreeSearch(root, key);
   RBTree::Node* ptr_p = ptr;
   RBTree::Node* ptr_s = ptr;

   if(ptr != nil){
         while((rbTreePredecessor(ptr_p) != nil) 
                  && *(rbTreePredecessor(ptr_p)->key) == key){ 
               ptr_p = rbTreePredecessor(ptr_p);
               rval.push_back(ptr_p->value);
         }

      rval.push_back(ptr->value);

         while((rbTreeSuccessor(ptr_s) != nil) && *(rbTreeSuccessor(ptr_s)->key) == key){
            ptr_s = rbTreeSuccessor(ptr_s);
            rval.push_back(ptr_s->value);
      }
   }
   return rval;
}

/*
 * @brief   calls rbPrintTree if root != nil
 *          
 * @param   key and value of node
 */
void RBTree::rbPrintTree(){
   if (root != nil)
      reverseInOrderPrint(root, 0);
}

// Nodes/////////////////////////////////////////////////////
/*
 * @brief   nil node constructor, set all pointers to nul
 *          set color to black
*/
RBTree::Node::Node(){
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = 'B';
   key = nullptr;
   value = nullptr;
}
/*
 * @brief   Node constructor
 *             set all node pointers to nul
 *             set key and value with dynamic mem
 *          
 * @param   key and value of node
 */
RBTree::Node::Node(const string& key_, const string& value_){

   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = 'R';
   key = new string(key_);
   value = new string(value_);

}
/*
 * @brief   node deconstructor
 *             deletes dynamic key and value
 *             set all pointers to null
 */
RBTree::Node::~Node(){
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = '\0';
   delete key;
   delete value;
   key = nullptr;
   value = nullptr;

}

// Private Ansestors/////////////////////////////////////////////////////

/*
 * @brief finds min of tree
 *          go left untill you cant
 *          
 * @param  node to search sub tree
 * 
 * @return  min value of subtree
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* node){
   RBTree::Node* ptr = node;
   while (ptr->left != nil){
      ptr = ptr->left;
   }
   return ptr;
}

/*
 * @brief finds max of tree
 *          go right untill you cant
 *          
 * @param  node to search sub tree
 * 
 * @return  min value of subtree
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* node){
   RBTree::Node* ptr = node;
   while (ptr->right != nil){
      ptr = ptr->right;
   }
   return ptr;
}

/*
 * @brief finds successor of node
 *          if theres a right child find max of that sub tree
 *          else find parent if parent is a right
 *          
 * @param  node to act as subtree start point
 * 
 * @return  Successor of node
 */
RBTree::Node* RBTree::rbTreeSuccessor(Node* node){
   RBTree::Node* x = node;
   if(x->right != nil){
      return rbTreeMinimum(x->right);
   }
   RBTree::Node* y = x->parent;
   while(y != nil && x == y->right){
      x = y;
      y = y->parent;
   }
   return y;

}

/*
 * @brief finds pretessesor of node
 *          if theres a left child find max of that sub tree
 *          else find parent if parent is a left
 *          
 * @param  node to act as subtree start point
 * 
 * @return  Predecessor of node
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* node){
   RBTree::Node* x = node;
   if(x->left != nil){
      return rbTreeMaximum(x->left);
   }
   RBTree::Node* y = x->parent;
   while(y != nil && x == y->left){
      x = y;
      y = y->parent;
   }
   return y;
}

/*
 * @brief search subtree for given key
 *          
 * @param  node to act as subtree start point, key to search for
 * 
 * @return  returns all values with given key 
 */
RBTree::Node* RBTree::rbTreeSearch(Node* node, const string& key ){
   //takes key returns first node with key in tree
   while(node != nil){

      if (key > *(node->key)){
         node = node->right;
      }

      else if(key < *(node->key)){
         node = node->left;
      }

      else{
         return (node);
         }
   }
   return nil;
}

/*
 * @brief finds pretessesor of node
 *          if theres a left child find max of that sub tree
 *          else find parent if parent is a left
 *          
 * @param  node to act as subtree start point
 * 
 * @return  Predecessor of node
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

// Private Mutators/////////////////////////////////////////////////////
/*
 * @brief rotate subtree left
 *          
 * @param  node to act as subtree start point
 */
void RBTree::leftRotate(Node* x){
   RBTree::Node* y = x->right;

   x->right = y->left;

   if(y->left != nil){
      y->left->parent = x;
   }

   y->parent = x->parent;

   if(x->parent == nil){
      root = y;
   }

   else if(x == x->parent->left){
      x->parent->left = y;
   }

   else{
      x->parent->right = y;

   }
   y->left = x;
   x->parent = y;
}

/*
 * @brief rotate subtree right
 *          
 * @param  node to act as subtree start point
 */
void RBTree::rightRotate(Node* x){
   RBTree::Node* y = x->left;

   x->left = y->right;

   if(y->right != nil){
      y->right->parent = x;
   }

   y->parent = x->parent;

   if(x->parent == nil){
      root = y;
   }

   else if(x == x->parent->right){
      x->parent->right = y;
   }

   else{
      x->parent->left = y;
   }
   y->right = x;
   x->parent = y;

}
/*
 * @brief fixup for rbTree insert
 *          pushes down blackness or rotates depending on parent nodes
 *          
 * @param  node to act as subtree start point
 */
void RBTree::rbInsertFixup(Node* z){
   RBTree::Node* y;

   while (z->parent->color == 'R'){
      if(z->parent == z->parent->parent->left){ //if parent is a left child
         y = z->parent->parent->right;

         if(y->color == 'R'){
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         }

         else {
            if (z == z->parent->right){ //if z is a right child
            z = z->parent;
            leftRotate(z);
            }

            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            rightRotate(z->parent->parent);
         }
      }
      else{
         y = z->parent->parent->left;
         if(y->color == 'R'){
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         }
         else{
            if (z == z->parent->left){ //if z is a right child
               z = z->parent;
               rightRotate(z);
            }
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            leftRotate(z->parent->parent);
         }
      }
   }
   root->color = 'B';
}

/*
 * @brief fixup for rbTree delete
 *          pushes down blackness or rotates depending on parent nodes
 *          
 * @param  node to act as subtree start point
 */
void RBTree::rbDeleteFixup(Node* x){
      RBTree::Node* w;

   while(x != root && x->color == 'B'){
      if(x == x->parent->left){
         w = x->parent->right;
         if (w->color == 'R'){
            w->color = 'B';
            x->parent->color = 'R';
            leftRotate(x->parent);
            w = x->parent->right;
         }
         if(w->left->color == 'B' && w->right->color == 'B'){
            w->color = 'R';
            x = x->parent;
         }
         else{ 
            if (w->right->color == 'B'){
               w->left->color = 'B';
               w->color = 'R';
               rightRotate(w);
               w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->right->color = 'B';
            leftRotate(x->parent);
            x = root;
         }
      }
      else{
         if(x == x->parent->right){
            w = x->parent->left;
            if (w->color == 'R'){
               w->color = 'B';
               x->parent->color = 'R';
               rightRotate(x->parent);
               w = x->parent->left;
            }
            if(w->right->color == 'B' && w->left->color == 'B'){
               w->color = 'R';
               x = x->parent;
            }
            else{
               if (w->left->color == 'B'){
                  w->right->color = 'B';
                  w->color = 'R';
                  leftRotate(w);
                  w = x->parent->left;
               }
               w->color = x->parent->color;
               x->parent->color = 'B';
               w->left->color = 'B';
               rightRotate(x->parent);
               x = root;
            }
         }
      }
   }
   x->color = 'B';
}

/*
 * @brief transplants two nodes
 *          
 * @param   two nodes to switch
 */
void RBTree::rbTransplant(Node*node_1, Node* node_2){
   if (node_1->parent == nil){
      root = node_2;
   }
   else if(node_1 == node_1->parent->left){
      node_1->parent->left = node_2;
   }
   else{
      node_1->parent->right = node_2;
      node_2->parent = node_2->parent;
   }
}

///// private mutators overloaded from public interface//////////////
/*
 * @brief insert node into subtree
 *          
 * @param  node to insert
 */
void RBTree::rbInsert(Node* z){

   RBTree::Node* y = nil;
   RBTree::Node* x = root; 

   z->left = nil;
   z->right = nil;
   z->parent = nil;

   while (x != nil){
      y = x;
      if (*(z->key) <= *(x->key)){
         x = x->left;
      }
      else{ 
         x = x->right;
      }
   }

   z->parent = y;
   if(y == nil){
      root = z;
   }

   else if(*(z->key) <= *(y->key)){
      y->left = z;
   }

   else{
      y->right = z;
   }

   z->left = nil;
   z->right = nil;
   z->color = 'R';
   
   rbInsertFixup(z);
}

/*
 * @brief delete node from treee
 *          
 * @param  node to delete
 */
void RBTree::rbDelete(Node* z){

   char original_color;
   Node* y = z;
   Node* x;

   original_color = y->color;

   if(z->left == nil){
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if(z->right == nil){
       x = z->left;
       rbTransplant(z, z->left);
    }
    else{
       y = rbTreeMaximum(z->left);
       original_color = y->color;
       x = y->left;
      if(y->parent == z){
         x->parent = y;
      }
      else{
         rbTransplant(y, y->left);
         y->left = z->left;
         y->left->parent = y;
      }
      rbTransplant(z, y);
      y->right = z->right;
      y->right->parent = y;
      y->color = z->color;
   }
   if (original_color == 'B'){
      rbDeleteFixup(x);
   }
   delete z;
}