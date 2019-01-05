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

	struct Node
	{
		K key; 						/*!< Node key, templated on K */
		T value; 					/*!< Node value, templated on T */
		std::shared_ptr<Node> left = nullptr; 		/*!< shared pointer to the left node */
		std::shared_ptr<Node> right = nullptr; 	/*!< shared pointer to the right node*/
		std::shared_ptr<Node> parent = nullptr;    /*|< pointer to parent node, for quicker searching*/

		Node(): key(), value(), left(), right(){}; 			/*!< node constructor*/
		Node(K k, T val): key(k), value(val), left(), right(){}; 	/*!< node constructor by declared value*/

	};
	
	std::shared_ptr<Node> root = nullptr; 			/*!< pointer to tree root node*/
	std::shared_ptr<Node> current = nullptr;		/*!< initialize a pointer to find, add, etc */

	std::shared_ptr<Node> _find(T val);

	

public:
	
	Tree():root(){};  				/*!< Tree constructor*/
	
	~Tree(){}; 						/*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	
	Tree(Tree&&) = default;  	/*!< Additional semantics*/
	
	Tree& operator =(Tree&&) = default ;  			/*!< Operator = overload*/
	
	Tree(const Tree&) {}; 				/*!< move constructor*/
	
	Tree& operator =(const Tree&) {}; 	/*!<  const operator = overload */
	
	const std::shared_ptr<Node> addNode(const K key, const T value) {  /*!< creates a node provided key and value, and put it in the appropriate point of the tree*/

		//make_shared : Constructs an object of type T and wraps it in a std::shared_ptr 
		//using args as the parameter list for the constructor of T. 
		//std::shared_ptr<Node> newnode = std::make_shared<Node>(key, value);
		
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
			std::cout << "root settato a : " << root << std::endl;
			return root;
		}

		
		
		if (current->key == key) {
			std::cout << "current = " << current << "\nstessa chiave: setto current->value a " << value << std::endl;
			current->value = value;
			std::cout << "creo il returnNode : " << std::endl;
			std::shared_ptr<Node> returnNode;
			std::cout << "creato : returnNode =  " << returnNode << "\n ora setto il returnNode a current"<< std::endl;
			returnNode = current;
			std::cout << "Fatto. ora setto current a root:  " << root << std::endl;
			current = root;
			std::cout << "fatto. returno."<< std::endl;
			return returnNode;
		
		}
		else if (key <  current->key) {
			if (current->left) {
				
				current = current->left;
				addNode(key,value);
			}
			else {
				std::shared_ptr<Node> newnode = std::make_shared<Node>(key, value);
				newnode->parent = current;
				current->left = newnode;
				current = root;
				return newnode;
			}
		}
		else  {
			std::cout << "chiave maggiore! \n "  << std::endl;
			if (current->right) {
				std::cout << "c'è già un right child "<< current->right << std::endl;
				std::cout << "setto current a current->right " << std::endl;
				current = current->right;
				std::cout << "richiamo addNode " << std::endl;
				addNode(key,value);
			}
			else {
				std::cout << "non c'è ancora un right child! creo un newnode. "  << std::endl;
				std::shared_ptr<Node> newnode = std::make_shared<Node>(key, value);
				std::cout << "assegno a newnode->parent il valore di current : " << current << std::endl;
				newnode->parent = current;
				std::cout << "assegno a current->right il valore di newnode : " << newnode << std::endl;
				current->right = newnode;
				std::cout << "riporto current a root " << root << std::endl;
				current = root;
				std::cout << "provo a returnare newnode: "<< newnode <<" ed esplodo" << std::endl;
				return nullptr;				
			}

		}
	};   

	void removeNode(K key) {};    /*!< remove a node*/

	void listNodes() {};          /*!< shows all nodes (maybe in tree format print?) */

	bool destroy(){ return true;};  					/*!< tree deletion*/
	
	std::shared_ptr<Node> begin(){ return root;};		/*!< must return an iterator to the first element */ 

	std::shared_ptr<Node> end(){

		// for every node, if node->right == nullptr, return a pointer to the node, else return end(node->right)
	
	return root;};			/*!< iterator to the last element */

	const std::shared_ptr<Node> cbegin(){return root;};		/*!< must return a const iterator to the first element */ 

	const std::shared_ptr<Node> cend(){return root;};		/*!< const iterator to the last element */

	
	void balance(){};   				/*!< tree balance*/
	
	std::shared_ptr<Node> find(T x){return root;};   	/*!< find by value public method  (calls private _find)*/

	//T& operator[](const K& key){};    /*!< optional: returns the value associated with a given key if present. If not present, creates a node with the given key */

	//std::ostream& operator<< (std::ostream& stream, const Tree::Tree& tree){};  /*!<  << operator overload: should print the contents of every K,V pair in ostream */

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

	void traversal_iterator(){};

	

};

int main()
{
	Tree<int,int> test;
	test.addNode(1,1);
	test.addNode(1,2);
	test.addNode(1,1);
	test.addNode(3,2);
	test.addNode(4,3);
	
	return 0;
}