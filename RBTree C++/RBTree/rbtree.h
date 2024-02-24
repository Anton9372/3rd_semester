#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <limits>

namespace rbt
{
	template <typename T>
	class ConstRbtIterator;

	template <typename T>
	class RBTree final
	{
		enum Color { RED, BLACK };
		struct Node
		{
			T val;
			Node* left;
			Node* right;
			Node* parent;
			Color color;
			bool nil;		//if true, node = NIL
			//Constructor for NIL
			Node() : val(T()), left(nullptr), right(nullptr), parent(nullptr), color(BLACK), nil(true) {}
			//Constructor for Node
			//but after constructing you should call makeNils(node) to construct NILS
			explicit Node(T value) : val(value), left(nullptr), right(nullptr), parent(nullptr), color(RED), nil(false) {}
			bool isNil() const;
			Node* min();
			Node* max();
			Node* next();
			Node* prev();
		};
		Node* root_;
		int size_;
		friend class ConstRbtIterator<T>;
	private:
		void deleteTree(Node* node);
		void makeNils(Node* node);						//makes children NIL, but parent = nullptr
		bool isNil(Node* node) const;
		int count(Node* node, T value) const;
		Node* search(T value) const;					//if no node found returns nullptr
		void transplantNode(Node* from, Node* to);
		void leftRotate(Node* node);
		void rightRotate(Node* node);
		void insertBalanceTree(Node* newNode);
		void eraseBalanceTree(Node* deleted);
		bool isBST(Node* node, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) const;
		bool checkRedNode(Node* node) const;
		int sameBlackPath(Node* node) const;
		bool rootIsBlack() const;
		void printTree(Node* node, int level = 0) const;
	public:
		RBTree();
		template <typename Iterator>
		RBTree(Iterator begin, Iterator end);
		~RBTree();
		int size() const;
		bool empty() const;
		void clear();
		int count(T value) const;
		ConstRbtIterator<T> find(T value) const;
		void insert(T value);
		void erase(T value);
		void printTree() const;
		bool isRBT() const;
		ConstRbtIterator<T> begin() const;
		ConstRbtIterator<T> back() const;
		ConstRbtIterator<T> end() const;
	};

	//Node methods
	template <typename T>
	bool RBTree<T>::Node::isNil() const
	{
		return nil == true;
	}

	template <typename T>
	typename RBTree<T>::Node* RBTree<T>::Node::min()
	{
		if (isNil())
			return nullptr;
		Node* temp = this;
		while (!temp->left->isNil())
			temp = temp->left;
		return temp;
	}

	template <typename T>
	typename RBTree<T>::Node* RBTree<T>::Node::max()
	{
		if (isNil())
			return nullptr;
		Node* temp = this;
		while (!temp->right->isNil())
			temp = temp->right;
		return temp;
	}

	template <typename T>
	typename RBTree<T>::Node* RBTree<T>::Node::next()
	{
		if (isNil())
			return nullptr;
		else if (!right->isNil())
			return right->min();
		else if (parent == nullptr)
			return nullptr;
		else
		{
			Node* temp = this;
			while (temp->parent && temp == temp->parent->right)
				temp = temp->parent;
			return temp->parent;
		}
	}

	template <typename T>
	typename RBTree<T>::Node* RBTree<T>::Node::prev()
	{
		if (isNil())
			return nullptr;
		else if (!left->isNil())
			return left->max();
		else if (parent == nullptr)
			return nullptr;
		else
		{
			Node* temp = this;
			while (temp->parent && temp == temp->parent->left)
				temp = temp->parent;
			return temp->parent;
		}
	}

	//Tree methods
	template <typename T>
	RBTree<T>::RBTree()
	{
		root_ = new Node();
		size_ = 0;
	}

	template <typename T>
	template <typename Iterator>
	RBTree<T>::RBTree(Iterator begin, Iterator end) : RBTree()
	{
		for (auto it = begin, ite = end; it != ite; ++it)
			insert(*it);
	}

	template<typename T>
	void RBTree<T>::deleteTree(Node* node)
	{
		if (node == nullptr)
			return;
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}

	template<typename T>
	RBTree<T>::~RBTree()
	{
		deleteTree(root_);
	}

	template <typename T>
	int RBTree<T>::size() const
	{
		return size_;
	}

	template <typename T>
	bool RBTree<T>::empty() const
	{
		return isNil(root_);
	}

	template <typename T>
	void RBTree<T>::clear()
	{
		deleteTree(root_);
		root_ = new Node();
	}

	template <typename T>
	void RBTree<T>::makeNils(Node* node)
	{
		Node* left = new Node();
		Node* right = new Node();
		node->left = left;
		node->right = right;
		node->left->parent = node;
		node->right->parent = node;
	}

	template <typename T>
	bool RBTree<T>::isNil(Node* node) const
	{
		return node->nil == true;
	}

	template <typename T>
	int RBTree<T>::count(Node* node, T value) const
	{
		if (isNil(node))
			return 0;
		if (node->val == value)
			return 1 + count(node->left, value) + count(node->right, value);
		else if (node->val < value)
			return count(node->right, value);
		else
			return count(node->left, value);
	}

	template <typename T>
	int RBTree<T>::count(T value) const
	{
		return count(root_, value);
	}

	template <typename T>
	typename RBTree<T>::Node* RBTree<T>::search(T value) const
	{
		Node* current = root_;
		while (!isNil(current))
		{
			if (value == current->val)
				return current;
			else if (value < current->val)
				current = current->left;
			else
				current = current->right;
		}
		return nullptr;
	}

	template <typename T>
	ConstRbtIterator<T> RBTree<T>::find(T value) const
	{
		Node* temp = search(value);
		return ConstRbtIterator<T>(temp);
	}

	template <typename T>
	void RBTree<T>::transplantNode(Node* from, Node* to)
	{
		if (to == root_)
			root_ = from;
		else if (to == to->parent->left)
			to->parent->left = from;
		else
			to->parent->right = from;
		from->parent = to->parent;
	}

	template <typename T>
	void RBTree<T>::leftRotate(Node* node)
	{
		if (isNil(node->right))
			return;
		Node* rightChild = node->right;
		node->right = rightChild->left;
		node->right->parent = node;
		rightChild->parent = node->parent;
		if (!node->parent)
			root_ = rightChild;
		else if (node == node->parent->left)
			node->parent->left = rightChild;
		else
			node->parent->right = rightChild;
		rightChild->left = node;
		node->parent = rightChild;
	}

	template <typename T>
	void RBTree<T>::rightRotate(Node* node)
	{
		if (isNil(node->left))
			return;
		Node* leftChild = node->left;
		node->left = leftChild->right;
		node->left->parent = node;
		leftChild->parent = node->parent;
		if (!node->parent)
			root_ = leftChild;
		else if (node == node->parent->left)
			node->parent->left = leftChild;
		else
			node->parent->right = leftChild;
		leftChild->right = node;
		node->parent = leftChild;
	}

	template <typename T>
	void RBTree<T>::insert(T value)
	{
		Node* newNode = new Node(value);
		makeNils(newNode);
		size_++;
		Node* current = root_;
		while (!isNil(current))
		{
			if (value < current->val)
				current = current->left;
			else
				current = current->right;
		}
		Node* parent = current->parent;
		delete current;
		newNode->parent = parent;
		if (!parent)
			root_ = newNode;
		else if (value < parent->val)
			parent->left = newNode;
		else
			parent->right = newNode;
		insertBalanceTree(newNode);
	}

	template <typename T>
	void RBTree<T>::insertBalanceTree(Node* newNode)
	{
		Node* parent = nullptr;
		Node* grandparent = nullptr;
		while (newNode != root_ && newNode->color != BLACK && newNode->parent->color != BLACK)
		{
			parent = newNode->parent;
			grandparent = parent->parent;
			Node* uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;
			if (uncle->color == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				grandparent->color = RED;
				newNode = grandparent;
			}
			else
			{
				if (newNode == parent->right && parent == grandparent->left)
				{
					leftRotate(parent);
					newNode = parent;
					parent = newNode->parent;
				}
				else if (newNode == parent->left && parent == grandparent->right)
				{
					rightRotate(parent);
					newNode = parent;
					parent = newNode->parent;
				}
				if (newNode == parent->left)
					rightRotate(grandparent);
				else
					leftRotate(grandparent);
				std::swap(parent->color, grandparent->color);
				newNode = parent;
			}
		}
		root_->color = BLACK;
	}

	template <typename T>
	void RBTree<T>::erase(T value)
	{
		Node* deleted = search(value);
		if (deleted == nullptr)
			return;
		Node* child = nullptr;
		Color deletedNodeColor = deleted->color;
		Node* deletedNil;
		if (isNil(deleted->left) || isNil(deleted->right))
		{
			child = !isNil(deleted->left) ? deleted->left : deleted->right;
			deletedNil = (child == deleted->left) ? deleted->right : deleted->left;
			transplantNode(child, deleted);
			delete deleted;
		}
		else
		{
			Node* heir = deleted->right->min();
			deleted->val = heir->val;
			deletedNodeColor = heir->color;
			child = !isNil(heir->left) ? heir->left : heir->right;
			deletedNil = (child == heir->left) ? heir->right : heir->left;
			transplantNode(child, heir);
			delete heir;
		}
		delete deletedNil;
		size_--;
		if (deletedNodeColor == BLACK)
			eraseBalanceTree(child);
	}

	template <typename T>
	void RBTree<T>::eraseBalanceTree(Node* node)
	{
		while (node != root_ && node->color == BLACK)
		{
			Node* brother;
			if (node == node->parent->left)
			{
				brother = node->parent->right;
				if (brother->color == RED)
				{
					brother->color = BLACK;
					node->parent->color = RED;
					leftRotate(node->parent);
					brother = node->parent->right;
				}
				if (brother->left->color == BLACK && brother->right->color == BLACK)
				{
					brother->color = RED;
					node = node->parent;
				}
				else
				{
					if (brother->right->color == BLACK)
					{
						brother->left->color = BLACK;
						brother->color = RED;
						rightRotate(brother);
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = BLACK;
					brother->right->color = BLACK;
					leftRotate(node->parent);
					node = root_;
				}
			}
			else
			{
				brother = node->parent->left;
				if (brother->color == RED)
				{
					brother->color = BLACK;
					node->parent->color = RED;
					rightRotate(node->parent);
					brother = node->parent->left;
				}
				if (brother->left->color == BLACK && brother->right->color == BLACK)
				{
					brother->color = RED;
					node = node->parent;
				}
				else
				{
					if (brother->left->color == BLACK)
					{
						brother->right->color = BLACK;
						brother->color = RED;
						leftRotate(brother);
						brother = node->parent->left;
					}
					brother->color = node->parent->color;
					node->parent->color = BLACK;
					brother->left->color = BLACK;
					rightRotate(node->parent);
					node = root_;
				}
			}
		}
		node->color = BLACK;
	}

	template <typename T>
	bool RBTree<T>::isBST(Node* node, T min, T max) const
	{
		if (isNil(node))
			return true;
		else if (node->val < min || node->val > max)
			return false;
		else
			return isBST(node->left, min, node->val) && isBST(node->right, node->val, max);
	}

	template <typename T>
	bool RBTree<T>::checkRedNode(Node* node) const
	{
		if (isNil(node))
			return true;
		if (node->color == RED && node->left->color != BLACK && node->right->color != BLACK)
			return false;
		return checkRedNode(node->left) && checkRedNode(node->right);
	}

	template <typename T>
	int RBTree<T>::sameBlackPath(Node* node) const
	{
		if (isNil(node))
			return 1;
		int left = sameBlackPath(node->left);
		int right = sameBlackPath(node->right);
		if (left == 0 || right == 0 || left != right)
			return 0;
		if (node->color == BLACK)
			left++;
		return left;
	}

	template <typename T>
	bool RBTree<T>::rootIsBlack() const
	{
		return root_->color == BLACK;
	}

	template <typename T>
	bool RBTree<T>::isRBT() const
	{
		return isBST(root_) && checkRedNode(root_) && sameBlackPath(root_) && rootIsBlack();
	}

	template <typename T>
	void RBTree<T>::printTree(Node* node, int level) const
	{
		if (isNil(node))
			return;
		char c;
		c = (node->color == BLACK) ? 'b' : 'r';
		printTree(node->right, level + 1);
		std::cout << std::string(level * 4, ' ') << node->val << c << std::endl;
		printTree(node->left, level + 1);
	}

	template <typename T>
	void RBTree<T>::printTree() const
	{
		printTree(root_);
	}

	template <typename T>
	ConstRbtIterator<T> RBTree<T>::begin() const
	{
		return ConstRbtIterator<T>(root_->min());
	}

	template <typename T>
	ConstRbtIterator<T> RBTree<T>::back() const
	{
		return ConstRbtIterator<T>(root_->max());
	}

	template <typename T>
	ConstRbtIterator<T> RBTree<T>::end() const
	{
		return ConstRbtIterator<T>();
	}
}

#endif