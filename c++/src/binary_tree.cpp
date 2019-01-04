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

template <class K, class T>
class Tree {

	struct Node
	{
		K key; 						/*!< Node key, templated on K */
		T value; 					/*!< Node value, templated on T */
		std::shared_ptr<Node> left; 		/*!< shared pointer to the left node */
		std::shared_ptr<Node> right; 	/*!< shared pointer to the right node*/
		std::shared_ptr<Node> parent;    /*|< pointer to parent node, for quicker searching*/

		Node(): key(), value(), left(), right(){}; 			/*!< node constructor*/
		Node(T val): key(), value(val), left(), right(){}; 	/*!< node constructor by declared value*/

	};
	
	std::shared_ptr<Node> root; 			/*!< pointer to tree root node*/
	
	std::shared_ptr<Node> _find(T val);

public:
	
	Tree():root(){};  				/*!< Tree constructor*/
	
	~Tree(){}; 						/*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	
	Tree(Tree&&) = default;  	/*!< Additional semantics*/
	
	Tree& operator =(Tree&&) = default ;  			/*!< Operator = overload*/
	
	Tree(const Tree&) {}; 				/*!< move constructor*/
	
	Tree& operator =(const Tree&) {}; 	/*!<  const operator = overload */
	
	void addNode(K key, T value) {};    /*!< add a new node*/

	void removeNode(K key) {};    /*!< remove a node*/

	void listNodes() {};          /*!< shows all nodes (maybe in tree format print?) */

	bool clear(){ return true;};  					/*!< tree deletion*/
	
	std::shared_ptr<Node> begin(){ return root;};		/*!< must return an iterator to the first element */ 

	std::shared_ptr<Node> end(){return root;};			/*!< iterator to the last element */

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
	Tree<int,int> test2 = test;
	return 0;
}