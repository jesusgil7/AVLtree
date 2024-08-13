#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    //Creating variables for nodes
    string UFID;
    string student_name;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(string id, string name) : UFID(id), student_name(name), left(nullptr), right(nullptr), height(1){}

};
//Update the heigh of the pass node
void updateheight(TreeNode* root){
    root->height = 1 + std::max((root->right == nullptr ? 0 : root->right->height), (root->left == nullptr ? 0 : root->left->height));
}

//Print the height of the root
void printLevelCount(TreeNode* root){
    if(root == nullptr){
        cout << 0 <<endl;
    }
    else{
        cout << root->height << endl;
    }
}
//Get the balance factor of the node, utitlize to know when to do rotations
int balanceFactor(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    //Get the height from left then from right and substract
    int leftHeight = (root->left == nullptr) ? 0 : root->left->height;
    int rightHeight = (root->right == nullptr) ? 0 : root->right->height;
    return leftHeight - rightHeight;
}
//Rotation to the left
TreeNode* rotateLeft(TreeNode* root){
    TreeNode* newParent = root->right;
    TreeNode* grandchild = newParent->left;

    newParent->left = root;
    root->right = grandchild;
    updateheight(root);
    updateheight(newParent);
    return newParent;
}
//rotation to the right
TreeNode* rotateRight(TreeNode* root){
    TreeNode* newParent = root->left;
    TreeNode* grandchild = newParent->right;

    newParent->right = root;
    root->left = grandchild;
    updateheight(root);
    updateheight(newParent);

    return newParent;
}

//Insert a node a check if the tree needs a balance
TreeNode* insert(TreeNode* root, string name, string id) {
    // Insertion
    if (root == nullptr) {
        cout << "successful" << endl;
        return new TreeNode(id, name);
    }
    if (stoi(id) < stoi(root->UFID)) {
        root->left = insert(root->left, name, id);
    } else if (stoi(id) > stoi(root->UFID)) {
        root->right = insert(root->right, name, id);
    } else {
        cout << "unsuccessful" << endl;
        return root; // Node with the same key already exists, so return root
    }

    updateheight(root);
    int balance = balanceFactor(root);

    //left left -> right
    if (balance > 1){
        if(stoi(id) < stoi(root->left->UFID)){
            root = rotateRight(root);
            return root;
        }
        else{
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
            return root;
        }

    }
    //right right -> left
    if (balance < -1){
        if(stoi(id)  > stoi(root->right->UFID)) {
            root = rotateLeft(root);
            return root;
        }
        else{
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
            return root;
        }

    }
    return root;
}
//Itrates to find a node with a similar name
void searchID(TreeNode* root, string id_value){
    while(root != nullptr){
        if(stoi(id_value) < stoi(root->UFID)){
            root = root->left;
        }
        else if (stoi(id_value) > stoi(root->UFID)){
            root = root->right;
        }
        else{
            string quotedString = root->student_name;
            string unquotedString;

            // Remove the quotes from the string
            for (char c : quotedString) {
                if (c != '"') {
                    unquotedString += c;
                }
            }
            cout << unquotedString << endl;
            return;
        }
    }
    cout << "unsuccessful" <<endl;
}


void preorderhelper(TreeNode* root, bool& isFirst){
    if(root == nullptr){
        return;
    }
    string quotedString = root->student_name;
    string unquotedString;

    // Loop to remove the quotes from the string
    for (char c : quotedString) {
        if (c != '"') {
            unquotedString += c;
        }
    }

    if (!isFirst) {
        cout << ", ";
    }
    cout << unquotedString;
    isFirst = false;
    preorderhelper(root->left, isFirst);
    preorderhelper(root->right, isFirst);

}
void printPreorder(TreeNode* root){
    // Boolean to track if it's the first node
    bool isFirst = true;
    preorderhelper(root, isFirst);
}
void inorderHelper(TreeNode* root, bool& isfirst, string& names){
    if(root == nullptr){
        cout << "" ;
    }
    else{
        inorderHelper(root->left, isfirst, names);
        string quotedString = root->student_name;
        string unquotedString;

        // Loop to remove the quotes from the string
        for (char c : quotedString) {
            if (c != '"') {
                unquotedString += c;
            }
        }

        if (!isfirst) {
            names += ", ";
        }
        names += unquotedString;
        inorderHelper(root->right, isfirst, names);
        isfirst = false;
    }
}
string printInorder(TreeNode* root) {
    // Boolean to track if it's the first node
    string inorder;
    bool isFirst = true;
    inorderHelper(root, isFirst, inorder);
    return inorder;
}

void postorderHelper(TreeNode* node, bool& isFirst) {
    if (node == nullptr) return;

    // Traverse the left and right subtree
    postorderHelper(node->left, isFirst);
    postorderHelper(node->right, isFirst);

    // Visit the current node (root)
    string unquotedString;

    // Loop to remove the quotes from the string
    for (char c : node->student_name) {
        if (c != '"') {
            unquotedString += c;
        }
    }

    // Print the node's name followed by a comma if it's not the first node
    if (!isFirst) {
        cout << ", ";
    }
    cout << unquotedString;

    // Update isFirst to false after printing the first node
    isFirst = false;
}
void printPostorder(TreeNode* root) {
    // Boolean to track if it's the first node
    bool isFirst = true;
    postorderHelper(root, isFirst);
}

//Function to find the successor utilize to remove a node with two childs effectily
TreeNode* inorderSuccessor(TreeNode* node) {
    TreeNode* current = node->right;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

TreeNode* Remove(TreeNode* root, string id) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    // If the ID is less than the root's ID, search in the left subtree
    if (stoi(id) < stoi(root->UFID)) {
        root->left = Remove(root->left, id);
    }
        // If the ID is greater than the root's ID, search in the right subtree
    else if (stoi(id) > stoi(root->UFID)) {
        root->right = Remove(root->right, id);
    }

    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        else{
            TreeNode* temp = inorderSuccessor(root);
            root->UFID = temp->UFID;
            root->student_name = temp->student_name;
            root->right = Remove(root->right, temp->UFID);
        }
    }
    return root;
}
TreeNode* removeInorderHelper(TreeNode* root, int& count, int N) {
    if (root == nullptr) {
        return nullptr;
    }

    // Traverse the left subtree
    root->left = removeInorderHelper(root->left, count, N);

    if (count == N) {
        //Node with only one child or no child
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            cout << "successful" << endl;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        //  Node with two children
        TreeNode* temp = inorderSuccessor(root->right); // Find inorder successor
        root->UFID = temp->UFID;
        root->student_name = temp->student_name;
        root->right = removeInorderHelper(root->right, count, stoi(temp->UFID));
        cout << "successful" << endl;
        return root;
    }
    count++;

    // If the current node is not the Nth node, continue traversing the right subtree
    root->right = removeInorderHelper(root->right, count, N);

    return root;
}

//Function to pass a count to the helper function
TreeNode* removeInorder(TreeNode* root, int N) {
    int count = 0; // Initialize count to 0
    return removeInorderHelper(root, count, N);
}

void searchName(TreeNode* root, string name) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    bool node_found = false;
    string print_names;
    stack<TreeNode*> names;
    names.push(root);
    while(!names.empty()){
        TreeNode * curr = names.top();
        names.pop();

        if(curr->student_name == name){
            print_names += curr->UFID + "\n";
            node_found = true;
        }
        if(curr->right != nullptr){
            names.push(curr->right);
        }
        if(curr->left != nullptr){
            names.push(curr->left);
        }
    }
    if(node_found == false){
        cout << "unsuccessful" << endl;
    } else{
        cout << print_names;
    }

}
int main() {
    TreeNode *root = nullptr;
    string input;
    getline(cin, input);
    int num_loop = stoi(input);

    for(int i =0;i<num_loop;i++){
        string method;
        getline(cin, method);
        istringstream iss(method);

        vector<std::string> tokens;
        string token;

        while (getline(iss, token, ' ')) {
            tokens.push_back(token);
        }
        if(tokens[0] == "insert"){
            root = insert(root, tokens[1], tokens[2]);
        }
        else if (tokens[0] == "printInorder"){
            cout << printInorder(root);
            cout << endl;
        }
        else if (tokens[0] == "printPreorder"){
            printPreorder(root);
            cout << endl;
        }
        else if (tokens[0] == "printPostorder"){
            printPostorder(root);
            cout << endl;
        }
        else if (tokens[0] == "search") {
          try{
              stoi(tokens[1]);
              searchID(root, tokens[1]);
          }
          catch (const std::invalid_argument&){
              searchName(root, tokens[1]);
          }
        }
        else if(tokens[0] == "remove"){
            root = Remove(root, tokens[1]);
        }
        else if(tokens[0] == "removeInorder"){
            removeInorder(root, stoi(tokens[1]));
        }
        else if(tokens[0] == "printLevelCount"){
            printLevelCount(root);
        }
        else{
            cout << "unsuccessfull" << endl;
        }
    }
}