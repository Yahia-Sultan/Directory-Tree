

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "GTNode.cpp"
using namespace std;


vector<string> names;

void del(GTNode* target, GTNode* parent) {
    target->setParent(NULL);
    if (parent->getLeftMostChild() == target) {
        if (target->getRightSibling() != NULL) {
            parent->setLeftMostChild(target->getRightSibling());
        }
        else {
            parent->setLeftMostChild(NULL);
        }
    }
    else {
        GTNode* temp = parent->getLeftMostChild();
        GTNode* left = parent->getLeftMostChild();
        while (temp->getRightSibling() != NULL) {
            temp = temp->getRightSibling();
            if (target == temp) {
                if (temp->getRightSibling() != NULL)
                    left->setRightSibling(temp->getRightSibling());
                else
                    left->setRightSibling(NULL);
                break;
            }
            left = left->getRightSibling();
        }
    }
    if (target->getLeftMostChild() != NULL) {
        GTNode* temp = target->getLeftMostChild();
        while (temp->getRightSibling() != NULL) {
            temp = temp->getRightSibling();
            del(temp, target);
        }
        del(target->getLeftMostChild(), target);
    }
    //got code from: https://stackoverflow.com/questions/14737780/how-do-i-remove-the-first-occurrence-of-a-value-from-a-vector/14737827
    //author: us2012 {
    auto it = find(names.begin(), names.end(), target->getName());
    if (it != names.end()) {
        names.erase(it);
    }
    // }
}

int count(GTNode* node) {
    int num = 0;
    if (node->getLeftMostChild() != NULL) {
        num++;
        GTNode* temp = node->getLeftMostChild();
        num += count(temp);
        while (temp->getRightSibling() != NULL) {
            temp = temp->getRightSibling();
            num++;
            num += count(temp);
        }
    }

    return num;
}

void preorder(GTNode* node, int space) {
    string spacing = "";
    for (int i = 0; i < space; i++)
        spacing += "\t";
    if (node->getLeftMostChild() != NULL) {
        GTNode* temp = node->getLeftMostChild();
        cout << spacing << temp->getName() << endl;
        preorder(temp, 1 + space);
        while (temp->getRightSibling() != NULL) {
            temp = temp->getRightSibling();
            cout << spacing << temp->getName() << endl;
            preorder(temp, 1 + space);
        }
    }
}

int main()
{

    GTNode* current = new GTNode("root");
    names.push_back(current->getName());

    while (1) {
        string primary;
        getline(cin, primary);
        string input;
        string arg;
        bool sp = false;
        for (int i = 0; i < primary.size(); i++) {
            if (sp) {
                arg += primary[i];
            }
            else {
                if ((!sp) && (isspace(primary[i]))) {
                    sp = true;
                }
                else {
                    input += primary[i];
                }   
            }
        }

        if (input == "cd") {   // Change directory to child directory // .. (for parent) ; Time complexity: O(n)
            if (arg == "..") {
                if (current->getParent() != NULL) {
                    current = current->getParent();
                }
                else {
                    cout << "You are in root directory" << endl;
                }
            }
            else {
                bool found = false;
                if (current->getLeftMostChild() != NULL) {
                    GTNode* temp = current->getLeftMostChild();
                    if (temp->getName() == arg) {
                        current = temp;
                        found = true;
                    }
                    else {
                        while (temp->getRightSibling() != NULL) {
                            temp = temp->getRightSibling();
                            if (temp->getName() == arg) {
                                current = temp;
                                found = true;
                                break;
                            }
                        }
                    }
                }
                if(!found)
                    cout << arg << " not found" << endl;
            }
        }
        else if (input == "ls") { // list all child directories; Time complexity: O(n)
            if (current->getLeftMostChild() != NULL) {
                GTNode* temp = current->getLeftMostChild();
                cout << temp->getName();
                while (temp->getRightSibling() != NULL) {
                    temp = temp->getRightSibling();
                    cout << "\t" << temp->getName();
                }
                cout << endl;
            }
            else {
                cout << "This directory is empty" << endl;
            }
        }
        else if (input == "pwd") { // name of current directory; Time complexity: O(1)
            cout << current->getName() << endl;
        }
        else if (input == "exists") { // check if directory exists anywhere; Time complexity: O(n)
            if (count(names.begin(), names.end(), arg)) {
                cout << arg << " exists" << endl;
            }
            else {
                cout << arg << " does not exist" << endl;
            }
        }
        else if (input == "mkdir") { // create new directory as a child of current directory; Time complexity: O(n)
            GTNode* newDir = new GTNode(arg);
            newDir->setParent(current);
            names.push_back(arg);
            if (current->getLeftMostChild() != NULL) {
                GTNode* temp = current->getLeftMostChild();
                while (temp->getRightSibling() != NULL) {
                    temp = temp->getRightSibling();
                }
                temp->setRightSibling(newDir);
            }
            else {
                current->setLeftMostChild(newDir);
            }
        }
        else if (input == "rmdir") { // Remove directory and all subsidies if directory is a child; Time complexity: O(n^2)
            bool found = false;
            if (current->getLeftMostChild() != NULL) {
                if (current->getLeftMostChild()->getName() == arg) {
                    found = true;
                    del(current->getLeftMostChild(), current);
                }
                else {
                    GTNode* temp = current->getLeftMostChild();
                    while (temp->getRightSibling() != NULL) {
                        temp = temp->getRightSibling();
                        if (temp->getName() == arg) {
                            found = true;
                            del(temp, current);
                            break;
                        }
                    }
                }
            }
            if(!found) {
                cout << arg << " not found" << endl;
            }
        }
        else if (input == "countdir") { // number of descendants of current directory; Time complexity: O(n^2)
            cout << (1 + count(current)) << endl;
        }
        else if (input == "showtree") { //show directory tree ; Time complexity : O(n)
            cout << current->getName() << endl;
            preorder(current, 1);
        }
        else if (input == "quit") {
            break;
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
    names.clear();

}
