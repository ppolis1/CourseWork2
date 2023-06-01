#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <queue> 
using namespace std;

ofstream ans("ans.txt");

struct Node {
	int key; 
	Node* left; 
	Node* right;
};

void addElement(int value, Node*& root){
	if (!root) { 
		root = new Node;
		root->key = value;
		root->left = 0;
		root->right = 0;
		return;
	}
	if (root->key > value) { 
			addElement(value, root->left);
		}
	else if (root->key < value)	{ 
			addElement(value, root->right);
		};
}
Node* searchElement(Node* root, int value) {
	if (!root) {
		return 0;
	}
	else {
		if (value == root->key) {
			return root;
		}
		if (value > root->key) {
			return searchElement(root->right, value);
		}
		else {
			return searchElement(root->left, value);
		}
	}
}
void printTree(Node* node, ostream& file, string const& rpref = "", string const& cpref = "", string const& lpref = "") {
	if (!node) return;
	if (node->right)
		printTree(node->right, file, rpref + "   ", rpref + "/-->", rpref + "|   ");
	file << cpref << to_string(node->key) << endl;
	if (node->left)
		printTree(node->left, file, lpref + "|   ", lpref + "\\-->", lpref + "    ");
}

void preOrderTravers(Node*& root){
	if (root) {
		cout << root->key << " ";
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}
void postOrderTravers(Node* root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		cout << root->key << " ";
	}
}
void breadthSearch(Node* root) {
	queue<Node*> nodeQueue;
	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		root = nodeQueue.front();
		cout << root->key << " ";
		nodeQueue.pop();
		if (root->left) {
			nodeQueue.push(root->left); 
		}
		if (root->right) {
			nodeQueue.push(root->right); 
		}
	}
}

Node* delElement(Node*& root, int aData) {
	if (root == NULL)
		return root;
	if (aData == root->key) {
		Node* tmp;
		if (root->right == NULL)
			tmp = root->left;
		else {
			Node* ptr = root->right;
			if (ptr->left == NULL) {
				ptr->left = root->left;
				tmp = ptr;
			}
			else {
				Node* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = root->left;
				pmin->right = root->right;
				tmp = pmin;
			}
		}
		delete root;
		return tmp;
	}
	else if (aData < root->key)
		root->left = delElement(root->left, aData);
	else
		root->right = delElement(root->right, aData);
	return root;
}

int main()
{
	Node* root = 0;
	cout << "Input list: \n";
	int num;
	while (cin >> num) {
		addElement(num, root);
	}
	printTree(root, cout);
	ans << "Tree after creation:\n";
	printTree(root, ans);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bool flag = true;
	while (flag) {
		cout <<
			"\n1)Insert an element\n"
			"2)Delete an element\n"
			"3)Search an element\n"
			"4)Direct search\n"
			"5)Reverse search\n"
			"6)Search in width\n"
			"0)exit\n";
		int type;
		cin >> type;
		int num;
		switch (type) {
		case 0:
			flag = false;
			break;
		case 1:
			cout << "Enter an element: ";
			ans << "Tree after add elements:\n";
			cin >> num;
			addElement(num, root);
			break;
		case 2:
			cout << "Enter an element: ";
			ans << "Tree after delete elements:\n";
			cin >> num;
			if (!searchElement(root, num))
				cout << "Element" << num << " not found!\n";
			else {
				root = delElement(root, num);
			}
			break;
		case 3:
			cout << "Enter an element: ";
			cin >> num;
			if (searchElement(root, num)) {
				cout << "The element " << num << " is found!";
				ans << "The element " << num << " is found!\n";
			}
			else {
				cout << "Element" << num << " not found!"; 
				ans << "Element" << num << " not found!\n";
			}
			break;
		case 4:
			cout << "Direct search: ";
			preOrderTravers(root);
			break;
		case 5:
			cout << "Reverse search: ";
			postOrderTravers(root);
			break;
		case 6:
			cout << "Search in width: ";
			breadthSearch(root);
			break;
		default:
			cout << "Error input!";
		}
		cout << "\n\n";
		ans << "\n\n";
		printTree(root, cout);
		printTree(root, ans);
		cout << endl;
		ans << endl;
	}

	return 0;
}