/**
* @file binary_tree.cpp
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

/*! namespace for things not directly able to interact with Tree */
namespace detail {

    template <class K, class T>
    struct Node {
        /*! Node key, templated on K */
        K key;
        /*! Node value, templated on T */
        T value;
        /*! unique pointer to the left node */
        std::unique_ptr<Node> left  = nullptr;
        /*! unique pointer to the right node*/
        std::unique_ptr<Node> right = nullptr;
        Node * parent = nullptr;


        Node() = default;
        /*! node constructor by declared value*/
        Node(K k, T val) 
        : key(k), 
          value(val) 
        {}
    };

    /*!clone a node, including children pointers and parent*/
    template <class K, class T>
    std::unique_ptr<Node<K, T>> clone(const Node<K, T> * old) {
        auto node = std::make_unique<Node<K, T>>(old->key, old->value);
        if (old->left) {
            node->left = clone(old->left.get());
            node->left->parent = node.get();
        };
        if (old->right) {
            node->right = clone(old->right.get());
            node->right->parent = node.get();
        };
        return node;
    }

    /*! helper function to traverse left nodes until there is any, giving the min(key) */
    template <typename NodeType>
    NodeType * allLeft(NodeType * node) noexcept {
        while (node->left) { node = node->left.get(); }
        return node;
    }

    /*! helper function to traverse right nodes until there is any, giving max(key)*/
    template <typename NodeType>
    NodeType * allRight(NodeType * node) noexcept {
        while (node->right) { node = node->right.get(); }
        return node;
    }

    /*! helper function to return next node*/
    template <typename NodeType>
    NodeType * successor(NodeType * node) noexcept {
        if (node->right) { return allLeft(node->right.get()); }
        auto * parent = node->parent;
        while (parent && node == parent->right.get()) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}


/*! Implements a binary search tree, templated on key and values */
template <class K, class T>
class Tree {
    

    using Node = detail::Node<K, T>;  // to use directly Node, from detail namespace

    /*! pointer to tree root node*/
    std::unique_ptr<Node> root = nullptr;

    Node * treeroot() noexcept {
        /*! Helper function: exposes a public interface to the private tree root.*/
        return root.get();
    }

    const Node * ctreeroot() const noexcept {
        /*! Helper function: exposes a public interface to the private tree root, const.*/
        return root.get();
    }

    /*! recursive helper function, called by balance() function*/
    void recursive_balancer(std::vector<std::pair<K,T>>vec) {       // to do: set to private.

        if (vec.size() < 3)
        {
            for(auto & item : vec)
                this->insert(item.first, item.second);
        }
        else
        {
            this->insert(vec[vec.size() / 2].first, vec[vec.size() / 2].second);
            std::vector<std::pair<K,T>> firstHalf(vec.begin(), vec.begin() + vec.size()/2);
            std::vector<std::pair<K,T>> secondHalf(vec.begin() + vec.size()/2 + 1, vec.end());
            recursive_balancer(firstHalf);
            recursive_balancer(secondHalf);
        }
    }

    std::vector <std::pair<K,T>> arrayOfNodes() {
    /*!  Helper function: creates an std::vector and push every pair(key,value) of the tree nodes in it.*/
        std::vector<std::pair<K,T>> v;
        for (auto i = begin(); i != end(); ++i) {
            auto data = std::make_pair(i->key, i->value);
            v.push_back(data);
        }

        std::cout << "Nodes have been stored into a vector. Rebuilding the tree..." << std::endl;
        return v;
    }

//////////////////////////////////////// PUBLIC /////////////////////////////
public:

    /*! constructor */
    Tree (){std::cout << "tree created with custom constructor\n";};

    /*! Move constructor*/
    Tree ( Tree <K,T>&& other) noexcept = default;
    
    /*! Copy assignment */
    Tree & operator=(Tree&& bt) noexcept = default;
    Tree & operator=(const Tree& bt) noexcept = default;

    /*! Copy constructor */
    Tree (const Tree & other)
    : root(clone(other.root.get())),
      height(other.height) 
    {};
        
    

    /*! default destructor */
    ~Tree() noexcept = default;



    /*! Helper function. True if root == nullptr*/
    bool isEmpty() const {

        bool emp = ((ctreeroot()==nullptr) ? (true) : (false));
        return emp;
    }

    /*! Returns tree height */
    size_t height = 0;




/////////////////////////////// ITERATOR TEMPLATE //////////////////////////////

    template <bool Const>
    class iterator_template {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t; //  is the signed integer type of the result of subtracting two pointers. 
        using reference = typename std::conditional_t<Const, const Node &, Node &>;  // conditional_t provides member typedef type, which is defined as T1 if B is true at compile time, or as T2 if B is false. 
        using pointer = typename std::conditional_t<Const, const Node *, Node *>;    // conditional_t provides member typedef type, which is defined as T1 if B is true at compile time, or as T2 if B is false. 

    public :
        iterator_template() = default;
        explicit iterator_template(pointer ptr) : itr(ptr) {}

        reference operator*() { return *itr; };
        pointer operator->() { return itr; }
        iterator_template & operator++() {
            itr = successor(itr);
            return *this;
        }
        iterator_template operator++(int) {
            auto old = *this;
            ++(*this);
            return old;
        }
        friend bool operator== (const iterator_template<Const> & lhs, const iterator_template<Const> & rhs) {
            return lhs.itr == rhs.itr;
        };
        friend bool operator!= (const iterator_template<Const> & lhs, const iterator_template<Const> & rhs) {
            return !(lhs == rhs);
        };
    

    protected:       // allows inheritance
        pointer itr = nullptr;
    };


    
    using iterator = iterator_template<false>;   // creates iterators
    using const_iterator = iterator_template<true>; // creates const_iterators

////////////////////// end iterators ///////////////////////////////////
// detail:: is automatically called by ADL (see Koenig lookup)

    
    /*! iterator to the node with the lowest key*/
    iterator       begin()        { return iterator(allLeft(root.get())); }
    /*! iterator to the node with the lowest key, for const Trees*/
    const_iterator begin()  const { return const_iterator(allLeft(root.get())); }
    /*! const iterator to the node with the lowest key, for const Trees*/
    const_iterator cbegin() const { return const_iterator(allLeft(root.get())); }

    /*! iterator to the node after the one with the highest key (so nullptr)*/
    iterator       end()          { return iterator(nullptr); }
    /*! iterator to the node after the one with the highest key (so nullptr), for const Trees*/
    const_iterator end()  const   { return const_iterator(nullptr);}
    /*! const iterator to the node after the one with the highest key (so nullptr), for const Trees*/
    const_iterator cend() const   { return const_iterator(nullptr); }

    void insert(const K key, const T value) { /*! add a node provided key and value compatible with the tree */

       /* @brief
        *
        * input: K key, T value. Must match tree K and T types.
        * output: none
        * actions: if root is nullptr, set the new node as root.
        * otherwise, recursively compares keys.
        * if equal, overwrites value.
        * if less or greater, recursively calls itself respectively on left or right child
        *
        *
        */
        Node * current = root.get();
        Node * parent = nullptr;

        size_t temp_height = 0;
        while (current) {
            parent = current;
            if (key > current->key) {
                current = current->right.get();
                temp_height++;
                if (temp_height > this->height) { this->height = temp_height;}
            } else if (key < current->key) {
                current = current->left.get();
                temp_height++;
                if (temp_height > this->height) { this->height = temp_height;}
            } else {
                current->value = value;
                return;
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
        return;
    };

    void removeNode(K k) {/*! remove the node corresponding to the given key */
        /* @brief
        *
        * input: K k, the key corresponding to the node to be removed.
        * output: none.
        *
        */

        if (&*find(k) == nullptr) return;

        Node* toBeRemoved{&*find(k)};

        /* CASE 0: the node is root */
        if (toBeRemoved->parent == nullptr) {
          std::cout << "\nCase 0\n";
          destroy();
        }

        else {
          /* Is it the left child or right child? */
          int leftOrRight{0};
          if (toBeRemoved->parent->right.get() == toBeRemoved)
            leftOrRight = 1;

          /* CASE 1: the node is a leaf */
          if (!(toBeRemoved->left || toBeRemoved->right)) {
            if (toBeRemoved->parent->left.get() == toBeRemoved)
              toBeRemoved->parent->left = std::move(nullptr);
            else
              toBeRemoved->parent->right = std::move(nullptr);
          }
          /* CASE 2: the node has two children */
          else if (toBeRemoved->left && toBeRemoved->right) {
            Node* next{successor(toBeRemoved)};
            toBeRemoved->key = next->key;
            toBeRemoved->value = next->value;

            if (!(next->left || next->right)) {
              if (next->parent->left.get() == next)
                next->parent->left = std::move(nullptr);
              else
                next->parent->right = std::move(nullptr);

            } else {
              if (next->right) {
                next->right->parent = next->parent; // reassign parent to child

                // reassign child to parent
                if (leftOrRight) next->parent->right = std::move(next->right);
                else next->parent->left = std::move(next->right);

              } else {
                next->left->parent = next->parent; // reassign parent to child

                // reassign child to parent
                if (leftOrRight) next->parent->right = std::move(next->left);
                else next->parent->left = std::move(next->left);
              }
            }
          }
        }
    }

    void listNodes() {                      /*! iterates the tree in order, printing key-value entries */
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
    /*! tree deletion: sets root to nullptr, destroy recursively all nodes*/
    void destroy(){
        this->root = nullptr;
    }



    /*!< tree balance function. calls arrayOfNodes() to linearize the tree, then creates a balanced tree*/
    void balance()
    {
        this->height = 0;
        std::vector<std::pair<K,T>> vector = this->arrayOfNodes(); //salviamo i nodi iterati in  un vector, in ordine di key
        this->root = nullptr;  // cancelliamo tutti i nodi senza distruggere l'albero
        this->recursive_balancer(vector); // ricreiamo l'albero dal vector
    };
};

std::string random_string( size_t length ) /*!< generates a random string of given length, for benchmarking purposes */
{
    auto randchar = []() -> char  //neat lambda function
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

size_t llRand()   // random number between 0 and 10^18
{
    std::random_device rd;              //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<size_t> dis(1, 1000000000000000);   // 1-10^15

    return dis(gen);
}

template<class K, class T>                                                       ///   DA FINIRE!
std::ostream& operator<<(std::ostream& ostream, const Tree<K,T>& tree) {

    if (tree.isEmpty()) {
        ostream << "Error: printing empty tree";
        return ostream;
    }
    for (auto t=tree.cbegin();t!=tree.cend();++t){
        ostream << std::left << std::setw(12)<< t->key << ":" << t->value << "\n";
    }
  return ostream;
}

int main (int argc, char* argv[])
{

    //test removeNode

        std::cout << "\nTEST remove node with two children:\n";
        Tree<int, int> tree2;
        tree2.insert(10, 1);
        tree2.insert(6, 1);
        tree2.insert(16,1);
        tree2.insert(14, 1);
        tree2.insert(18, 1);
        tree2.insert(4, 1);
        tree2.insert(2, 1);
        tree2.insert(19, 1);

    std::cout << "Remove node 212 and 18.\n";
        tree2.removeNode(212);
        tree2.removeNode(18);
        tree2.listNodes();
    std::cout << "\nremoveNode test completed\n";
    //test llRand
    //std::cout << "llRand test: --> " << llRand() << std::endl;

    //read iterations and string length from argv
    const  int iterations = std::atoi(argv[1]);
    const  int str_length = std::atoi(argv[2]);
    const  int readtoo    = std::atoi(argv[3]);
    std::string dummy_value = "";

    //create an empty tree
    Tree <size_t,std::string> myMap;



    //populate the map
    for (int counter = 0; counter < iterations; ++counter )
    {
        size_t index = llRand();
        auto value = random_string(str_length);
        myMap.insert(index, value);
    }

    size_t testKey = 424242424242424242;

    myMap.insert(testKey,"These are indeed the droids you are looking for.");
/*
    std::cout << "Tree populated with " << iterations << " elements." << std::endl;

    // retrieve all data in random order if readtoo = 1
    if (readtoo) {
          std::cout << "My tree: \n ---------- \n" << myMap << std::endl;
    }

    // lookup time before balance:

    std::cout << "looking for my droids before tree balance... " ;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << myMap.find(testKey)->value << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "The droids found with a lookup time of "  ;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanosec" << std::endl;


    //test
    //auto v = myMap.arrayOfNodes();
    std::cout << "Tree height before balance: " << myMap.height << std::endl;
    myMap.balance();
    std::cout << "Tree height after balance: " << myMap.height << std::endl;

    // benchmark for lookup time after balance

    std::cout << "looking for my droids after balance... " ;
    //std::cout << std::chrono::high_resolution_clock::period::den << std::endl;
    auto start_time2 = std::chrono::high_resolution_clock::now();
    std::cout << myMap.find(testKey)->value << std::endl;
    auto end_time2 = std::chrono::high_resolution_clock::now();
    std::cout << "The droids found with a lookup time of "  ;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time2 - start_time2).count() << " nanoseconds" << std::endl;
*/
    std::cout << " ---------- copy/move semantics test -----------" << std::endl;
    
    auto tree3(myMap);
    
    std::cout << tree3 << " --- \n" << tree3.height;
    tree3.balance();
    std::cout << "balanced : " << tree3.height << std::endl;
  return 0;
}
