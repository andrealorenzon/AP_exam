/** 
* @file binary_tree.cpp
* @brief Binary tree implementation
* 
* test description
*
* @author Andrea Lorenzon
*
* @date 12/22/2018
*/


#include <binary_tree.h>

//remove method
template <typename T>
bool Tree<T>::remove(T x){
return remove(x, root);
}

//find method
template <typename T>
shared_ptr<Node> Tree<T>::find(T x) {
	//...find code here...//
}

//tree balance method
void Tree<T>::balance() {
	//..tree balance code here..//
}

// private remove method: this must be understood before being implemented
template <typename T>
bool Tree<T>::remove(T x, shared_ptr<Node>& p) {
	if(p && x < p->key)
		return remove(x, p->left);
	else if(p && x > p->key)
		return remove(x, p->right);
	else if(p && p->key == x) {
		if(!p->left)
			p = p->right;
		else if(!p->right) 
			p = p->left;
		else {
			shared_ptr<Node> q = p->left;
			while (q->right) q=q->right;
			p->key = q->key;
			remove(q->key, p->left);
			}
	return true;}
return false;}