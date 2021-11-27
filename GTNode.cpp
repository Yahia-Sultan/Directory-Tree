
#include <string>

using namespace std;

class GTNode {

	private:
		string name;
		GTNode* leftMostChild;
		GTNode* rightSibling;
		GTNode* parent;

	public:
		GTNode() {}
		GTNode(string name) {
			this->name = name;
			this->leftMostChild = NULL;
			this->rightSibling = NULL;
			this->parent = NULL;
		}
		GTNode(string name, GTNode* leftMostChild, GTNode* rightSibling, GTNode* parent) {
			this->name = name;
			this->leftMostChild = leftMostChild;
			this->rightSibling = rightSibling;
			this->parent = parent;
		}
		GTNode(const GTNode& other) {
			this->name = other.name;
			this->leftMostChild = other.leftMostChild;
			this->rightSibling = other.rightSibling;
			this->parent = other.parent;
		}
		~GTNode() {
			delete[] leftMostChild;
			delete[] rightSibling;
			delete[] parent;
		}

		string getName() {
			return name;
		}

		GTNode* getLeftMostChild() {
			return leftMostChild;
		}
		GTNode* getRightSibling() {
			return rightSibling;
		}
		GTNode* getParent() {
			return parent;
		}
		
		void setLeftMostChild(GTNode* node) {
			leftMostChild = node;
		}
		void setRightSibling(GTNode* node) {
			rightSibling = node;
		}
		void setParent(GTNode* node) {
			parent = node;
		}
		
};

