/** 
* @file binary_tree.h
*
* @brief Binary tree implementation header file
* 
* @author Andrea Lorenzon
*
* @date 12/22/2018
*/

#include <memory>

template <Class K, Class T>
class Tree {

	struct Node
	{
		K key; 						/*!< Node key, templated on K */
		T value; 					/*!< Node value, templated on T */
		shared_ptr<Node> left; 		/*!< shared pointer to the left node */
		shared_ptr<Node> right; 	/*!< shared pointer to the right node*/
		Node(): key(), value(), left(), right(){}; 			/*!< node constructor*/
		Node(T val): key(), value(val), left(), right(){}; 	/*!< node constructor by declared value*/
	};
	
	shared_ptr<Node> root; 			/*!< pointer to tree root node*/

	shared_ptr<Node> _find(T val);

public:
	
	Tree():root(){};  				/*!< Tree constructor*/
	
	~Tree(){}; 						/*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	
	// Tree(Tree&&) = default;  	/*!< Additional semantics*/
	
	Tree& operator =(Tree&&) = default;  			/*!< Operator = overload*/
	
	Tree(const Tree&); 				/*!< move constructor*/
	
	Tree& operator =(const Tree&); 	/*!<  const operator = overload */
	
	// bool push(T);  /*!< push method */
	
	bool clear();  					/*!< tree deletion*/
	
	shared_ptr<Node> begin();		/*!< must return an iterator to the first element */ 

	shared_ptr<Node> end();			/*!< iterator to the last element */

	const shared_ptr<Node> cbegin();		/*!< must return a const iterator to the first element */ 

	const shared_ptr<Node> cend();		/*!< const iterator to the last element */


	void balance();   				/*!< tree balance*/
	
	shared_ptr<Node> find(T x);   	/*!< find by value public method  (calls private _find)*/

	T& operator[](const K& key);    /*!< optional: returns the value associated with a given key if present. If not present, creates a node with the given key */

	std::ostream& operator<< (std::ostream& stream, const Tree::Tree& tree);  /*!<  << operator overload: should print the contents of every K,V pair in ostream */

	void breath_first(); 			/*!< breath first search*/
	
	size_t height(){ 				/*!< returns tree height*/
		return height(root);
	};

};