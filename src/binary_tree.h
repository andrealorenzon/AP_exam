#include <memory>

template <Class T>



class BLT {

	struct Node
	{
		T key; /*!< Node key, templated */
		shared_ptr<Node> left; /*!< shared pointer to the left node */
		shared_ptr<Node> right; /*!< shared pointer to the right node*/
		Node(): key(), left(), right(){}; /*!< node constructor*/
		Node(T val): key(val), left(), right(){}; /*!< node constructor by declared value*/
	};
shared_ptr<Node> root; /*!< pointer to tree root node*/

public:
	Tree():root(){};  /*!< Tree constructor*/
	~Tree(); /*!< Tree destructor. Smart pointers makes unnecessary the explicit destruction of all nodes*/
	// Tree(Tree&&) = default;  /*!< Additional semantics*/
	Tree& operator =(Tree&&) = default;  /*!< Operator = overload*/
	Tree(const Tree&); /*!< copy constructor*/
	Tree& operator =(const Tree&);  /*!<  const operator = overload */
	// bool push(T);  /*!< push method */
	bool remove(T);   /*!< tree deletion*/
	void balance();   /*! tree balance*/
	shared_ptr<Node> find(T x) {       /*! find public method  (calls private find)*/
		return find(x, root);
	};
	void breath_first(); /*!< breath first search*/
	size_t height(){ /*!< returns tree height*/
		return height(root);
	}

};