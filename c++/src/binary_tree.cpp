/** 
* @file binary_tree.cpp
*
* @brief Binary tree implementation
* 
* @author Andrea Lorenzon
*
* @date 12/22/2018
*/

#include <memory>   // std::shared_ptr<>
#include <iostream> // std::cout, endl
template <class K, class T>
class Tree {

	struct Node	{
		K key; 						/*!< Node key, templated on K */
		T value; 					/*!< Node value, templated on T */
		std::shared_ptr<Node> left = nullptr; 		/*!< shared pointer to the left node */
		std::shared_ptr<Node> right = nullptr; 	/*!< shared pointer to the right node*/
		Node(): key(), value(), left(), right(){}; 			/*!< node constructor*/
		Node(K k, T val): key(k), value(val), left(), right(){}; 	/*!< node constructor by declared value*/
		Node * parent = nullptr;
	};
	
	std::shared_ptr<Node> root = nullptr; 			/*!< pointer to tree root node*/
	std::shared_ptr<Node> current = nullptr;		/*!< initialize a pointer to find, add, etc */

public:
	
	Tree():root(){};  					/*!< Tree constructor*/
	~Tree(){}; 							/*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	Tree(Tree&&) = default;  			/*!< Move c'tor*/
	Tree& operator =(Tree&&) = default ;  /*!< Operator = overload*/
	Tree(const Tree&) {}; 				/*!< copy c'tor*/
	
	//  Tree& operator =(const Tree&) {}; 	/*!<  const operator = overload */
	
	std::shared_ptr<Node> beg() { 
		std::shared_ptr<Node> min = root;
		if (!min) {return nullptr;}
		while (min->left) {min = min->left;};
		return min;
	}

	std::shared_ptr<Node> en() { 
		std::shared_ptr<Node> max = root;
		if (!max) {return nullptr;}
		while (max->right) {max = max->right;};
		return max;
	}

	std::shared_ptr<Node> treeroot() { /*!< Could be useful. Remove if unnecessary. */
		return root;
	}
/////////////////////////////// ITERATORS //////////////////////////////
// status: DRAFT! Currently unused / untested	
	
	class iterator : public std::iterator< std::forward_iterator_tag,std::shared_ptr<Node> > {
	    std::shared_ptr<Node> itr = nullptr;

	    public :

	    iterator (std::shared_ptr<Node> temp) : itr(temp) {}
	    iterator (const iterator& myitr) : itr(myitr->itr) {}
	    


	    bool operator== (const iterator& rhs) {
	        return itr == rhs.itr;
	    };

	    bool operator!= (const iterator& rhs) {
	        return itr != rhs.itr;
	    };

	    T& operator*() {
	        return itr;
    	};
	    
    };	

////////////////////// end iterators ///////////////////////////////////

	const std::shared_ptr<Node> addNode(const K key, const T value) {  

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



		if (!root) {
			root = std::make_shared<Node>(key, value);
			current = root;

			std::cout << "root settato con chiave "<< key << " a : " << root << std::endl;
			return root;
		}

		current = root;
        std::shared_ptr<Node> parent = nullptr;
        while (current) {
        	parent = current;
        	if (key > current->key) {
        		current = current->right;
        	}
        	else if (key < current->key) {
        		current = current-> left;
        	}
        	else {
        		current->value = value;    // BUG: does not update values!! why???
        		std::cout << "node updated with key " << current->key << " and value " << current->value << " and kept at " << current << std::endl;
        		return nullptr;
        	}
        }
		current = std::make_shared<Node>(key, value);
		current->parent = parent.get();

		if (!parent) {
			root = current;
		}
		else if (current->key == parent->key) {
			current-> value = value;

			std::cout << "node updated with key " << key << " and kept at " << current << std::endl;
		}
		else if (current->key > parent->key) {
			parent->right = current;
		} 
		else if (current->key < parent->key) {
			parent->left = current;
		}
		std::cout << "node created with key " << key << " and set at " << current << std::endl;
		return current;
	};   

	void removeNode(K key) {};   			/*!< remove a single node*/

	void listNodes() {          			/*!< shows all nodes (maybe in tree format print?) */
		return this->inorder();
	};

	bool destroy(){ 						/*!< tree deletion: later: set root to nullptr, destroy recursively all nodes*/
		this->root.reset();
		return true;}; 
	
	std::shared_ptr<Node> begin(){ 			/*!< must return an iterator to the first element */ 
		return beg();
	};		

	std::shared_ptr<Node> end(){ 			/*!< iterator to the element after the last, that is nullptr */
		return nullptr;
	};			

	const std::shared_ptr<Node> cbegin() const {		/*!< must return a const iterator to the first element */ 
		return beg();
	};

	const std::shared_ptr<Node> cend()const{			/*!< const iterator to the last element */
		return nullptr;
	};

	std::shared_ptr<Node> operator++() { 				/*!< this function must be written, this is a placeholder */
		std::shared_ptr<Node>  i = this; 
		if (i->left) {return i->left;}
		else if (i->right) {return i->right;}
		return i; 
	}
	
	void balance(){};   								/*!< tree balance*/
	
	std::shared_ptr<Node> find(T x){return root;};   	/*!< find by value public method  (calls private _find)*/

	
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

	void traversal_iterator(){

		return this.inorder();
	};

	void inorder () {
		inorder(root);
	}

	void inorder(std::shared_ptr<Node> t) {
		if (root == nullptr) {
            std::cout << "No elements in a tree to display" << std::endl;
            return;
        }
        
        if (t->left != nullptr)    
            inorder(t->left);

        std::cout << "{" << t->key <<":"<<t->value<<"}  ";
        
        if (t->right != nullptr)    
            inorder(t->right);
	}

	void printTree() {

	}

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
	
	std::cout<< "begin: " << test.begin() << "\nend: " << test.end() << std::endl;
	std::cout<< "max : " << test.en() << std::endl;
	
	auto r = test.treeroot();
	std::cout << r << " is root." << std::endl;
	test.listNodes();
	std::cout << "\nDeleting the tree..." << std::endl;
	test.destroy();
	test.listNodes();
	
	return 0;
}