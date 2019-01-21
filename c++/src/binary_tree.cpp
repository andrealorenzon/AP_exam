/**
* @file binary_tree.cpp
*
* @brief Binary tree implementation
*
* @author Andrea Lorenzon
*
* @date 12/22/2018
*/

#include <algorithm>
#include <memory>   // std::unique_ptr
#include <iomanip>
#include <iostream> // std::cout, endl

template <class K, class T>
class Tree {

    struct Node	{
        K key; 						/*!< Node key, templated on K */
        T value; 					/*!< Node value, templated on T */
        std::unique_ptr<Node> left = nullptr; 		/*!< unique pointer to the left node */
        std::unique_ptr<Node> right = nullptr; 	/*!< unique pointer to the right node*/
        Node * parent = nullptr;

        Node() = default;
        Node(K k, T val) : key(k), value(val) {} 	/*!< node constructor by declared value*/
    };

    std::unique_ptr<Node> root = nullptr; 			/*!< pointer to tree root node*/

public:
    static Node * allLeft(Node * node) {   /*!< helper function to traverse left nodes until there is any */
        while (node->left) { node = node->left.get(); }
        return node;
    }

    static Node * allRight(Node * node) {
        while (node->right) { node = node->right.get(); }
        return node;
    }

    static Node * successor(Node * node) {    /*!< helper function to return next node*/
        if (node->right) { return allLeft(node->right.get()); }

        Node * parent = node->parent;
        while (parent && node == parent->right.get()) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }

    Node * treeroot() { return root.get(); }

/////////////////////////////// ITERATORS //////////////////////////////
// status: DRAFT! Currently unused / untested

    class iterator : public std::iterator< std::forward_iterator_tag, Node> {
        Node * itr = nullptr;
    public :
        iterator() = default;     // will set to nullptr thanks to ` = nullptr` above
        explicit iterator(Node * ptr) : itr(ptr) {}
        iterator(const iterator&) = default;  //c'tor

        Node & operator*() { return *itr; };
        Node * operator->() { return itr; }

        iterator & operator++() {  // deve ritornare nodo.successor()
            itr = successor(itr);
            return *this;
        }

        iterator operator++(int) {
            auto old = *this;
            ++(*this);
            return old;
        }

        friend bool operator== (const iterator & lhs, const iterator & rhs) {
            return lhs.itr == rhs.itr;
        };
        friend bool operator!= (const iterator & lhs, const iterator & rhs) {
            return !(lhs == rhs);
        };
    };

////////////////////// end iterators ///////////////////////////////////


    iterator begin() { return iterator(allLeft(root.get())); }
    iterator end() { return iterator(nullptr); }





    Node * addNode(const K key, const T value) {

        /*!< creates a node provided key and value, and put it in the appropriate point of the tree*/

        //make_shared : Constructs an object of type T and wraps it in a std::shared_ptr<Type>
        //using args as the parameter list for the constructor of T.
        //ex. std::shared_ptr<Node> newnode = std::make_shared<Node>(key, value);

        /* @brief
        *
        * input: K key, T value. Must match tree K and T types.
        * output: shared_pointer to new node
        * actions: if root is nullptr, set the new node as root.
        * otherwise, recursively compares keys.
        * if equal, overwrites value.
        * if less or greater, recursively calls itself respectively on left or right child
        *
        *
        */
        Node * current = root.get();
        Node * parent = nullptr;

        while (current) {
            parent = current;
            if (key > current->key) {
                current = current->right.get();
            } else if (key < current->key) {
                current = current->left.get();
            } else {
                current->value = value;    // BUG: does not update values!! why???
                std::cout <<"updated node " <<current <<" with value " <<value <<std::endl;
                return current;
            }
        }

        auto newNode = std::make_unique<Node>(key, value);
        current = newNode.get();
        if (parent) {
            newNode->parent = parent;
            if (newNode->key > parent->key) {
                parent->right = std::move(newNode);
                std::cout <<"created node (" <<std::setw(3) <<key
                          <<", " <<std::setw(3) <<value <<") [" <<current
                          <<"] on right of " <<parent->key <<std::endl;
            } else {
                parent->left = std::move(newNode);
                std::cout <<"created node (" <<std::setw(3) <<key
                          <<", " <<std::setw(3) <<value <<") [" <<current
                          <<"] on left of " <<parent->key <<std::endl;
            }
        } else {
            root = std::move(newNode);
            std::cout <<"created node (" <<std::setw(3) <<key
                      <<", " <<std::setw(3) <<value <<") [" <<current
                      <<"] at root" <<std::endl;
        }
        return current;
    };

    void removeNode(K key) {};   			/*!< remove a single node*/

    void listNodes() {          			/*!< shows all nodes (maybe in tree format print?) */
        for (auto i = begin(); i != end(); ++i) {
      	  std::cout << "iterated node: (" <<i->key <<", " <<i->value <<")" << std::endl;
    	};
    };

    iterator find(K k) {

    	if(!root) {return end();}
	    Node * node = root.get();
	    while (true) {
	    	if (node->key == k) {return iterator(node);}
	     //if there, return
	    
	    	else if (k < node->key) { 
	        	if (node->left) {node=node->left.get();}
	        	else {return end();}
	        } 
	        else if (k > node->key) { 
	        	if (node->right) {node=node->right.get();}
	        	else {return end();} 
			}	    
		}
	};	

    void destroy(){ 						/*!< tree deletion: later: set root to nullptr, destroy recursively all nodes*/
        this->root = nullptr;
    }

    void balance(){};   								/*!< tree balance*/

   

    /**
    * In-order (LNR) traversal
    * In-order: A, B, C, D, E, F, G, H, I.
    * Check if the current node is empty or null.
    * Traverse the left subtree by recursively calling the in-order function.
    * Display the data part of the root (or current node).
    * Traverse the right subtree by recursively calling the in-order function.
    *
    * In a binary search tree, in-order traversal retrieves data in sorted order.
    *
    * Here'a void placeholder, we should write a separate iterator class to include, IMHO
    *
    */
};

int main()
{
    Tree<int,int> test;
    test.addNode(1,1);
    test.addNode(3,2);
    test.addNode(-4,2);
    test.addNode(13,2);
    test.addNode(-7,2);
    test.addNode(-2,2);
    test.addNode(4,2);
    test.addNode(8,2);
    test.addNode(11,2);
    test.addNode(-8,2);
    test.addNode(5,3);
    test.addNode(-1,5);
    test.addNode(1,10);
    test.addNode(1,20);

    auto r = test.treeroot();

    //test allLeft
    std::cout<< "test for allLeft: root = " << r << std::endl;
    std::cout << " ... the next node is: " << test.allLeft(r) <<std::endl;

    r = test.successor(r);

    std::cout<< "the next node is: " << r <<std::endl;


    std::cout << "ITERATORS TEST AREA" << std::endl;

    test.listNodes();

    std::cout << "\nFIND TEST AREA: showing all nodes up to key = 3" << std::endl;

    int i = 3;
     for (auto x=test.begin(); x!=test.find(i); ++x) {
     	std::cout << " seeing " << x->key << ":" << x->value << std::endl;
     }

    //optional:
    test.destroy();


    return 0;
}