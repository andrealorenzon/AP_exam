/**
* @file binary_tree.h
*
* @brief Binary tree implementation
*
* @author Andrea Lorenzon, Francesco Cicala
*
* 
*/

#include <algorithm> // find_if
#include <memory>    // std::unique_ptr
#include <iomanip>   // cout alignment
#include <iostream>  // std::cout, endl
#include <math.h>    // pow()
#include <vector>    // for tree balancing
#include <utility>   // pair
#include <random>    // llRand, custom size_t random generator
#include <chrono>    // benchmarking purposes

template <class K, class T>
class Tree {

    struct Node	{
        K key; 						
        T value; 					
        std::unique_ptr<Node> left; 		
        std::unique_ptr<Node> right; 	    
        Node * parent;
        

        Node();
        Node(K k, T val); 	
    };
    std::unique_ptr<Node> root; 			
    Node * treeroot() noexcept;  
    const Node * ctreeroot() const noexcept;
    void recursive_balancer(std::vector<std::pair<K,T>>vec);
    static Node * allLeft(Node * node) noexcept;
    static Node * allRight(Node * node) noexcept;
    static const Node * successor(const Node * node) noexcept;
    static Node * successor(Node * node) noexcept;
    std::vector <std::pair<K,T>> arrayOfNodes();
    
public:
    bool isEmpty() const;
    size_t height;             
    class iterator : public std::iterator< std::forward_iterator_tag, Node> { 
        Node * itr;
    public :
        iterator();     
        explicit iterator(Node * ptr) : itr(ptr);
        iterator(const iterator&);                    
        Node & operator*();
        Node * operator->();
        iterator & operator++();
        iterator operator++(int);
        friend bool operator== (const iterator & lhs, const iterator & rhs);
        friend bool operator!= (const iterator & lhs, const iterator & rhs);
    };

    class const_iterator : public std::iterator< std::forward_iterator_tag, Node> {
        const Node * itr;
    public :
        const_iterator();     
        explicit const_iterator(const Node * ptr) : itr(ptr);
        const_iterator(const const_iterator&);
        const Node & operator*();
        const Node * operator->();
        const_iterator & operator++();
        const_iterator operator++(int);
        friend bool operator== (const const_iterator & lhs, const const_iterator & rhs);
        friend bool operator!= (const const_iterator & lhs, const const_iterator & rhs);        
    };
    iterator       begin();         
    const_iterator begin();  
    const_iterator cbegin(); 
    iterator       end();			        
	const_iterator end();
    const_iterator cend();

    void insert(const K key, const T value);
    void removeNode(K k);
    void listNodes();
    iterator find(K k);
    void balance();
};

std::string random_string( size_t length );
size_t llRand();

template<class K, class T>                                                       ///   DA FINIRE! 
std::ostream& operator<<(std::ostream& ostream, const Tree<K,T>& tree);
