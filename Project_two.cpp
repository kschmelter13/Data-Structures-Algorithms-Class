//============================================================================
// Name        : Project_two.cpp
// Author      : Kevin Schmelter
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course  {
     // unique identifier
    string courseId;
    string title;
    vector<string> prereqs;
    Course() {
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayCourse(Course course) {
    cout << course.courseId << ": " << course.title;
    for (unsigned int i = 0; i < course.prereqs.size(); i++) {
        cout << " | " << course.prereqs[i];
    }
    cout << endl;
    return;
}


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string bidId);
    Course Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    } // else
    else {
        // add Node root and bid
        addNode(root, course);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID
    root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root
    Node* curr = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (curr != nullptr) {
        // if match found, return current bid
        if (curr->course.courseId == courseId) {
            return curr->course;
        } // if bid is smaller than current node then traverse left
        else if (courseId < curr->course.courseId) {
            curr = curr->left;
        } // else larger so traverse right
        else {
            curr = curr->right;
        }
    }
    Course course;
    if (curr == nullptr) {
        return course;
    }
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (8) Implement inserting a bid into the tree
    // if node is larger then add to left 
    if (course.courseId < node->course.courseId) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        } // else recurse down the left node
        else {
            addNode(node->left, course);
        }
    } // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        } //else
        else {
            // recurse down the left node
            addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    // FixMe (9): Pre order root
    // if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        displayCourse(node->course);
        //InOder right
        inOrder(node->right);
    }
}

void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        displayCourse(node->course);
    }

}


void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        displayCourse(node->course);
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // if node is empty return
    if (node == nullptr) {
        return node;
    } // else if bid less than curr bid
    else if (courseId < node->course.courseId) {
        // recurse through left
        node->left = removeNode(node->left, courseId);
    } // else if bid larger than curr bid
    else if (courseId > node->course.courseId) {
        // recurse through right
        node->right = removeNode(node->right, courseId);
    } // else
    else {
        // if left and right node is empty delete node and make null
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } // else if left node is null node is right
        else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } // else of right is null node is left
        else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } // else change successor
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }
    return node;
}

//============================================================================
// Static methods used for testing
//============================================================================


/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    vector<Course> courses;
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    fstream file(csvPath, ios::in);
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    for (int i = 0; i < content.size(); i++)
    {
        // Create a data structure and add to the collection of bids
        Course course;
        course.courseId = content[i][0];
        course.title = content[i][1];

        displayCourse(course);
        
        

        // check if prerequisites exist and if they are valid
        if (content[i].size() > 2) {
            for (int j = 2; j < content[i].size(); j++) {
                course.prereqs.push_back(content[i][j]);
            }
        }
        // add the course to the vector
        courses.push_back(course);
    }

    // loop through each course
    for (int i = 0; i < courses.size(); i++) {
        // loop through each prereq
        for (int k = 0; k < courses[i].prereqs.size(); k++) {
            // set check to false
            bool prereq_valid = false;
            // loop though each course
            for (int j = 0; j < courses.size(); j++) {
                // check is prereq matches course ids
                if (courses[i].prereqs[k] == courses[j].courseId) {
                    prereq_valid = true;
                    break;
                }
            }
            // if prereq is not valid
            if (!prereq_valid) {
                cout << "Error: Invalid prerequisite course for " << courses[i].courseId << ": " << courses[i].prereqs[k] << endl;
                exit(1);
            }
        }
        
        // push this course to the end
        bst->Insert(courses[i]);
        
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, id;

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses In Order" << endl;
        cout << "  3. Display All Courses Pre Order" << endl;
        cout << "  4. Display All Courses Post Order" << endl;
        cout << "  5. Find Course" << endl;
        cout << "  6. Remove Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Please enter the file name: ";
            cin >> csvPath;

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadCourses(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            bst->PreOrder();
            break;

        case 4:
            bst->PostOrder();
            break;

        case 5:
            ticks = clock();
            cout << "Please enter the course Id: ";
            cin >> id;

            course = bst->Search(id);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Id " << id << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 6:
            bst->Remove(id);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
