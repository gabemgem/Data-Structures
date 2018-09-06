/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <algorithm>

using namespace std;

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only, this is actually bad to have because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,size_t low,size_t high);
	vector<T> keys;
	vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,size_t low,size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree {
public:
	BPlusTree() : root(NULL), b(0) {}

	BPlusTree(unsigned int num) : root(NULL), b(num) {}

	BPlusTree(const BPlusTree<T>& old) : b(old.b) {
		root = copy_tree(old.root);
	}

	~BPlusTree() { this->destroy(root); root=NULL; }

	bool insert(const T& val) { return insert(val,root); }

	BPlusTreeNode<T>* find(const T& val) { return find(val,root); }

	void print_sideways(ostream& outfile) const {
		print_sideways(outfile,root,0); }

	void print_BFS(ofstream& outfile) const {
		print_BFS(outfile,root,true); }

private:
	BPlusTreeNode<T>* root;
	unsigned int b;


	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* oroot) {
		if(!oroot)
			return NULL;
		BPlusTreeNode<T>* r = new BPlusTreeNode<T>();
		r->keys=oroot->keys;

		for(unsigned int i=0; i<oroot->children.size(); i++)
			r->children.push_back(copy_tree(oroot->children[i]));
		for(unsigned int j=0; j<r->children.size(); j++)
			r->children[j]->parent=r;

		return r;
	}

	void destroy(BPlusTreeNode<T>* p) {
		if(!p)
			return;

		for(unsigned int i=0; i<p->children.size(); i++)
			destroy(p->children[i]);

		delete p;
	}

	void split(BPlusTreeNode<T>* p) {
		if(!p) {
			cout<<"Something's wrong\n\n";
			return;
		}

		BPlusTreeNode<T>* first = new BPlusTreeNode<T>();
		BPlusTreeNode<T>* second = new BPlusTreeNode<T>();


		if(p==root) {
			bool dontdel = p->is_leaf();
			BPlusTreeNode<T>* par=new BPlusTreeNode<T>();
			root=par;
			par->children.push_back(first);
			par->children.push_back(second);
			first->parent=par;
			second->parent=par;
			for(unsigned int i=0; i<p->keys.size(); i++) {
				if(i<p->keys.size()/2)
					first->keys.push_back(p->keys[i]);
				else
					second->keys.push_back(p->keys[i]);
			}
			par->keys.push_back(second->keys[0]);

			if(!dontdel)
				second->keys.erase(second->keys.begin());

			for(unsigned int j=0; j<p->children.size(); j++) {
				if(j<p->children.size()/2)
					first->children.push_back(p->children[j]);
				else
					second->children.push_back(p->children[j]);
			}

			for(unsigned int k=0; k<first->children.size(); k++) {
				first->children[k]->parent=first;
			}

			for(unsigned int l=0; l<second->children.size(); l++) {
				second->children[l]->parent=second;
			}

			delete p;
		}

		else if(p->is_leaf()) {


			first->parent=p->parent;
			second->parent=p->parent;

			for(unsigned int i=0; i<p->keys.size(); i++) {
				if(i<p->keys.size()/2)
					first->keys.push_back(p->keys[i]);
				else
					second->keys.push_back(p->keys[i]);
			}

			vector<BPlusTreeNode<T>*> tempv;
			BPlusTreeNode<T>* tempn;

			for(unsigned int j=0; j<p->parent->children.size(); j++) {
				tempn=p->parent->children[j];
				if(tempn==p) {
					tempv.push_back(first);
					tempv.push_back(second);
				}
				else
					tempv.push_back(tempn);
			}

			p->parent->children=tempv;

			p->parent->keys.push_back(second->keys[0]);

			sort(p->parent->keys.begin(), p->parent->keys.end());
			if(p->parent->keys.size()>=b)
				split(p->parent);
			delete p;
			p=NULL;
		}
		

		

		else {
			
			first->parent=p->parent;
			second->parent=p->parent;

			for(unsigned int i=0; i<p->keys.size(); i++) {
				if(i<p->keys.size()/2)
					first->keys.push_back(p->keys[i]);
				else
					second->keys.push_back(p->keys[i]);
			}

			p->parent->keys.push_back(second->keys[0]);
			second->keys.erase(second->keys.begin());
			sort(p->parent->keys.begin(),p->parent->keys.end());

			vector<BPlusTreeNode<T>*> tempv;
			BPlusTreeNode<T>* tempn;

			for(unsigned int x=0; x<p->parent->children.size(); x++) {
				tempn=p->parent->children[x];
				if(tempn==p) {
					tempv.push_back(first);
					tempv.push_back(second);
				}
				else
					tempv.push_back(tempn);
			}

			p->parent->children=tempv;
			delete tempn;

			for(unsigned int j=0; j<p->children.size(); j++) {
				if(j<p->children.size()/2)
					first->children.push_back(p->children[j]);
				else
					second->children.push_back(p->children[j]);
			}

			for(unsigned int k=0; k<first->children.size(); k++) {
				first->children[k]->parent=first;
			}

			for(unsigned int l=0; l<second->children.size(); l++) {
				second->children[l]->parent=second;
			}

			delete p;
			if(first->parent->keys.size()>=b)
				split(first->parent);
		}
	}

	bool insert(const T& val, BPlusTreeNode<T>* r) {

		if(!r) {
			BPlusTreeNode<T>* nroot = new BPlusTreeNode<T>();
			nroot->keys.push_back(val);
			root=nroot;
			return true;
		}
		else if(r->is_leaf()) {
			r->keys.push_back(val);
			sort(r->keys.begin(), r->keys.end());
			if(r->keys.size()>=b)
				split(r);
			return true;
		}
		else {
			for(unsigned int i=0; i<r->children.size(); i++) {
				if(i==r->children.size()-1)
					return insert(val, r->children[i]);
				else if(i==0 && val<r->children[0]->keys[0])
					return insert(val, r->children[0]);
				else if(val<r->children[i]->keys[0])
					return insert(val, r->children[i-1]);
			}
		}
		return false;

	}

	BPlusTreeNode<T>* find(const T& val, BPlusTreeNode<T>* r) {

		if(!r) {
			return NULL;
		}
		
		if(r->is_leaf())
			return r;

		for(unsigned int i=0; i<r->children.size(); i++) {
			if(i==0 && val<=r->children[0]->keys[0])
				return find(val, r->children[0]);
			else if(val<r->children[i]->keys[0]) {
				if(r->children[i]->is_leaf())
					return find(val, r->children[i-1]);
				else
					return find(val, r->children[i]);
			}
			else if(i==r->children.size()-1)
				return find(val, r->children[i]);
		}
		return NULL;//first condition in loop above will make this never happen
	}

	void print_sideways(ostream& outfile, const BPlusTreeNode<T>* r,int depth) const {
		if (r) {
			for(unsigned int i=0; i<r->children.size()/2; i++)
				print_sideways(outfile, r->children[i], depth+1);
			for(int j=0; j<depth; j++) outfile<<"\t";
			outfile<<r->keys[0];
			for(unsigned int k=1; k<r->keys.size(); k++) outfile<<","<<r->keys[k];
			outfile<<endl;
			for(unsigned int l=r->children.size()/2; l<r->children.size(); l++)
				print_sideways(outfile, r->children[l], depth+1);
  
		}
		else
			outfile<<"Tree is empty.\n";
	}

	void printNode(ofstream& outfile, const BPlusTreeNode<T>* n) const {
		if(n) {
			outfile<<n->keys[0];
			for(unsigned int k=1; k<n->keys.size(); k++) 
				outfile<<","<<n->keys[k];
		}
	}

	void print_BFS(ofstream& outfile, const BPlusTreeNode<T>* r, bool newLine) const {

		if(r) {
			if(newLine) {
				printNode(outfile, r);
				outfile<<endl;
			}
			

			if(!r->children.empty()) {
				if(r->parent && r!=r->parent->children[0])
					outfile<<"\t";
				printNode(outfile,r->children[0]);
				for(unsigned int i=1; i<r->children.size(); i++) {
					outfile<<"\t";
					printNode(outfile, r->children[i]);
				}
				if(!r->parent || r==r->parent->children[r->parent->children.size()-1])
					outfile<<endl;
				for(unsigned int j=0; j<r->children.size(); j++) {
					print_BFS(outfile, r->children[j], false);
				}
			}


		}
		else
			outfile<<"Tree is empty.\n";

	}
};

#endif
