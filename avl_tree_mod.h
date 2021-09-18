//Sam Gustafsson

#ifndef AVL_TREE_MOD
#define AVL_TREE_MOD

#include "dsexceptions.h"
#include "sequence_map.h"

#include <algorithm>
#include <iostream> 
#include <string>

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    
    // void locate(const Comparable &x){
    //     locate(x, root);
    // }
    // int nodeCount(){
    //     return numberOfNodes;
    // }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    void locate(const Comparable &x){
        locate(x, root);
    }

    int nodeCount(){
        return nodeCount(root); //rule of thumb for counting for trees, always count from the root
    }
    
    float averageDepth(){
        return calculateDepth(0, root) / nodeCount();
    }

    int findMatches(const string & x) const{
        int n = 0;
        return findMatches(n, root, x);
    }

    int findCalls(const string & x){
        int n = 0;
        findMatches(n, root, x);
        return n;
    }
    int removeT(int & n, const string & x){
        return removeT(n, root, x);
    }



  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;  

    int nodeCount( AvlNode* node ) const {
        //check if tree is empty
        if(node == nullptr) //no children
            return 0;
        //if not empty, traverse plus 1 everytime
        else{
            return 1 + nodeCount(node->left) + nodeCount(node->right);
        }
    }
    float calculateDepth(float depth, AvlNode * node){
        if (node == nullptr){
            return 0;
        }
        else {
            depth = depth + calculateDepth(depth + 1, node -> left) + calculateDepth(depth + 1, node -> right);
        }
        return depth;
    }

    int findMatches(int & n, AvlNode * node, const string & x) const{
        n++; //number of calls
        if (node == nullptr){
            return 0;
        }
        else if(x < node->element.getSequence()){
            return findMatches(n ,node->left, x);
        }
        else if(x > node->element.getSequence()){
            return findMatches(n ,node->right, x);
        }
        else{
            return 1;
        }
    }

    int removeT(int& n, AvlNode * &node, const string& x){
        n++;
        if (node == nullptr){ //item isn't found, so return
            return 0;
        }
        else if(x < node->element.getSequence()){
            return removeT(n ,node->left, x);
        }
        else if(x > node->element.getSequence()){
            return removeT(n ,node->right, x);
        }
        
        else if(node->left !=nullptr && node->right != nullptr){ //two children here
        // we found the target
            node->element = findMin(node->right)->element;
            return removeT(n, node->right, node->element.getSequence());
        }

        AvlNode *oldNode = node;
        node = (node->left != nullptr) ? node->left : node->right; //Conditional / Ternary Operator
       
        delete oldNode;
        return 1;
        balance(node);
    }


    int numberOfNodes = 0;
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr ){
            t = new AvlNode{ x, nullptr, nullptr };
            numberOfNodes++;
        }
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else{
            t->element.Merge(x);
        }
        
        balance( t );
    }
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr ){
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
            numberOfNodes++;
        }
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else{
            t->element.Merge(x);
        }
        
        balance( t );
    }

    void locate(const Comparable &x, AvlNode * & t){
        //std::string a = "Not Found";
        if (t == nullptr){
            std::cout << "Not Found" << std::endl;
        }
        else if (x < t->element){
            locate(x, t->left);
        }
        else if (t->element < x){
            locate(x, t->right);
        }
        else if (x.sameRec(t->element) == true){
            std::cout << t->element << std::endl;
        }
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   //item not found, so do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) //two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    //----------------------------2.3----------------------------
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & third )
    {
        //rotateWithRightChild( third->left );
        //rotateWithLeftChild( third );
        // set *first to third->left
        AvlNode *first = third->left;

        //rotateWithRightChild part here
        AvlNode *second = first->right;
        first->right = second->left;
        second->left = first;

        //rotateWithLeftChild part here
        third->left = second->right;
        second->right = third;

        //updating heights
        first->height = max(height(first->left), height(first->right)) + 1;
        third->height = max(height(third->left), height(third->right)) + 1;

        second->height = max(first->height, third->height) + 1;

        third = second; //update root
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & first )
    {
        //rotateWithLeftChild( k1->right );
        //rotateWithRightChild( k1 );
        // set *second to first->right
        AvlNode *second = first->right;

        //rotateWithLeftChild part here
        AvlNode *third = second->left;
        second->left = third->right;
        third->right = second;

        //rotateWithRightChild part here
        first->right = third->left;
        third->left = first;

        //updating heights
        first->height = max(height(first->left), height(first->right)) + 1;
        second->height = max(height(second->left), height(second->right)) + 1;

        third->height = max(first->height, second->height) + 1;

        first = third; //update root
    }
};

#endif
