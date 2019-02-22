/**
* @file binary_tree.cpp
*
* @brief Binary tree implementation
*
* @author Andrea Lorenzon
*
* @date 12/22/2018
*/

#include <algorithm> // find_if
#include <memory>   // std::unique_ptr
#include <iomanip>  // cout alignment
#include <iostream> // std::cout, endl
#include <math.h>   // pow()
#include <vector>   // for tree balancing
#include <utility>  // pair

template <class K, class T>
class Tree {
	/*! Implements a binary search tree, templated on key and values */

    struct Node	{
        K key; 						/*! Node key, templated on K */
        T value; 					/*! Node value, templated on T */
        std::unique_ptr<Node> left = nullptr; 		/*! unique pointer to the left node */
        std::unique_ptr<Node> right = nullptr; 	    /*! unique pointer to the right node*/
        Node * parent = nullptr;

        Node() = default;
        Node(K k, T val) : key(k), value(val) {} 	/*! node constructor by declared value*/
    };

    std::unique_ptr<Node> root = nullptr; 			/*! pointer to tree root node*/

public:
    static Node * allLeft(Node * node) {   /*! helper function to traverse left nodes until there is any, giving the min(key) */
        while (node->left) { node = node->left.get(); }
        return node;
    }

    static Node * allRight(Node * node) {  /*! helper function to traverse right nodes until there is any, giving max(key)*/
        while (node->right) { node = node->right.get(); }
        return node;
    }

    static Node * successor(Node * node) {    /*! helper function to return next node*/
        
        if (node->right) { return allLeft(node->right.get()); }
        Node * parent = node->parent;
        while (parent && node == parent->right.get()) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }

    Node * treeroot() { 
    	/*! Helper function: exposes a public interface to the private tree root.*/
    	return root.get(); 
    }  

/////////////////////////////// ITERATORS //////////////////////////////

	/*! STL compliant forward_iterator class*/
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


    iterator begin()        { 
    	/*! iterator to the node with the lowest key*/
    	return iterator(allLeft(root.get())); 
    }

    iterator end()          { 
    	/*! iterator to the node after the one with the highest key (so nullptr)*/
    	return iterator(nullptr); 
    }				

	iterator cbegin() const { 
		/*! const iterator to the node with the lowest key*/
		return iterator(allLeft(root.get())); 
	} 	

    iterator cend()   const { 
    	/*! const iterator to the node after the one with the highest key (so nullptr)*/
    	return iterator(nullptr); 
    }				

    Node * addNode(const K key, const T value) { /*! add a node provided key and value compatible with the tree */

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
                // std::cout <<"created node (" <<std::setw(3) <<key
                //           <<", " <<std::setw(3) <<value <<") [" <<current
                //           <<"] on right of " <<parent->key <<std::endl;
            } else {
                parent->left = std::move(newNode);
                // std::cout <<"created node (" <<std::setw(3) <<key
                //           <<", " <<std::setw(3) <<value <<") [" <<current
                //           <<"] on left of " <<parent->key <<std::endl;
            }
        } else {
            root = std::move(newNode);
            // std::cout <<"created node (" <<std::setw(3) <<key
            //           <<", " <<std::setw(3) <<value <<") [" <<current
            //           <<"] at root" <<std::endl;
        }
        return current;
    };

    void removeNode(K key) {};   			/*! remove a single node*/

    void listNodes() {          			/*! iterates the tree in order */
        for (auto i = begin(); i != end(); ++i) {
      	  std::cout << "iterated node: (" <<i->key <<", " <<i->value <<")" << std::endl;
            
    	};
    };

    iterator find(K k) {   /*! traverse the tree looking for a key, otherwise return nullptr iterator, that is the same as end()*/
	    Node * node = root.get();
	    while (node && node->key != k) {
	        node = (k < node->key ? node->left : node->right).get();
	    }
	    return iterator(node);
	}

    void destroy(){ 						/*! tree deletion: later: set root to nullptr, destroy recursively all nodes*/
        this->root = nullptr;
    }

    std::vector <std::pair<K,T>> arrayOfNodes() 
    /*!<  Helper function: creates an std::vector and push every pair(key,value) of the tree nodes in it.*/

    {
        std::vector<std::pair<K,T>> v;
        for (auto i = begin(); i != end(); ++i) {
            auto data = std::make_pair(i->key, i->value);
            v.push_back(data);
        }
        std::cout << "Tree has been vectorized" << std::endl;
        return v;
    }

    void recursive_balancer() {
        //trova il centrale, lo mette nel tree
        // recursive_balancer(left half)
        // recursive_balancer(right half)
    }

    void balance()
    /*!< tree balance function. calls arrayOfNodes() to linearize the tree, then creates a balanced tree*/
    {
        std::vector<std::pair<K,T>> vector = this.arrayOfNodes();
        int length = vector.size();

    };   								

   

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


/*!< generates a random string of given length, for benchmarking purposes */
std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}



int main (int argc, char* argv[])
{
    // initialize random seed
    srand (time(NULL));

    //read iterations and string length from argv
    const  int iterations = std::atoi(argv[1]);
    const  int str_length = std::atoi(argv[2]);
    const int readtoo     = std::atoi(argv[3]);
    std::string dummy_value = "";

    //create an empty map
    Tree <int,std::string> myMap;
    std::cout << "begin: " << std::endl;

    //populate the map
    for (int counter = 0; counter < iterations; ++counter ) 
    {
        long long int index = std::rand();
        auto value = random_string(str_length);
        myMap.addNode(index, value);
    }
  
    std::cout << "Tree populated with " << iterations << " elements." << std::endl;

    // retrieve all data in random order if readtoo = 1
    if (readtoo) {
          myMap.listNodes();
    }


    //test
    auto v = myMap.arrayOfNodes();

  return 0;
}

