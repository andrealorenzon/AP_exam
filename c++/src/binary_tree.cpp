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
	
	std::shared_ptr<Node> root; 			/*!< pointer to tree root node*/
	
	std::shared_ptr<Node> _find(T val);

	

public:
	
	Tree():root(){};  				/*!< Tree constructor*/
	
	~Tree(){}; 						/*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	
	Tree(Tree&&) = default;  	/*!< Additional semantics*/
	
	Tree& operator =(Tree&&) = default ;  			/*!< Operator = overload*/
	
	Tree(const Tree&) {}; 				/*!< move constructor*/
	
	Tree& operator =(const Tree&) {}; 	/*!<  const operator = overload */
	
	const std::shared_ptr<Node> addNode(const K key, const T value) {  /*!< creates a node provided key and value, and put it in the appropriate point of the tree*/

		std::shared_ptr<Node> current = root;
		std::shared_ptr<Node> parent = nullptr;
		
		//make_shared : Constructs an object of type T and wraps it in a std::shared_ptr 
		//using args as the parameter list for the constructor of T. 
		newnode = std::make_shared<Node>(key, value);
		//ora bisogna posizionarlo a dovere...
		
		//std::cout << key << " " << value << " " << current << " " << parent << std::endl;  //debug, ok
		

		return current;
	
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
	
	return 0;
}