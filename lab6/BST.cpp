

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <functional>

#define INCLUDE_PARENT

struct Node {
    int val;
    Node *l, *r;
    #ifdef INCLUDE_PARENT
    Node* parent;
    Node(int val=0, Node* l=nullptr, Node* r=nullptr, Node* parent=nullptr): val(val), l(l), r(r), parent(parent) {}
    #else
    Node(int val=0, Node* l=nullptr, Node* r=nullptr): val(val), l(l), r(r) {}
    #endif
};

bool checkNodeForBST(Node* n) {
    if (n == nullptr) return true;
    if (n->l != nullptr && n->l->val >= n->val) return false;
    if (n->r != nullptr && n->r->val <= n->val) return false;
    return checkNodeForBST(n->l) && checkNodeForBST(n->r);
}


void generateAllTrees(std::vector<int>& inorder, int start, int end, Node*& root, std::vector<Node*>& allTrees) {
    if (start > end) {
        allTrees.push_back(nullptr);
        return;
    }
    

    for (int i = start; i <= end; i++) {
        std::vector<Node*> leftTrees, rightTrees;
        

        generateAllTrees(inorder, start, i - 1, root, leftTrees);
        

        generateAllTrees(inorder, i + 1, end, root, rightTrees);
        

        for (Node* left : leftTrees) {
            for (Node* right : rightTrees) {
                Node* newRoot = new Node(inorder[i]);
                newRoot->l = left;
                newRoot->r = right;
                allTrees.push_back(newRoot);
            }
        }
    }
}

std::vector<Node*> getAllTreesWithInorder(std::vector<int>& inorder) {
    std::vector<Node*> result;
    Node* dummy = nullptr;
    generateAllTrees(inorder, 0, inorder.size() - 1, dummy, result);
    return result;
}


void verifyInorder(Node* root, std::vector<int>& result) {
    if (!root) return;
    verifyInorder(root->l, result);
    result.push_back(root->val);
    verifyInorder(root->r, result);
}

bool hasCorrectInorder(Node* root, const std::vector<int>& expectedInorder) {
    std::vector<int> actualInorder;
    verifyInorder(root, actualInorder);
    return actualInorder == expectedInorder;
}


Node* createTree1() {

    Node* root = new Node(1);
    root->r = new Node(2);
    root->r->r = new Node(3);
    return root;
}

Node* createTree2() {

    Node* root = new Node(1);
    root->l = new Node(2);
    root->l->l = new Node(3);
    return root;
}

Node* findLCA(Node* root, int x, int y) {
    if (!root) return nullptr;
    Node* curr = root;
    while (curr) {
        if (x < curr->val && y < curr->val) {
            curr = curr->l;
        } else if (x > curr->val && y > curr->val) {
            curr = curr->r;
        } else {
            return curr;
        }
    }
    return nullptr;
}

Node* findInorderSuccessor(Node* n) {
    Node* dummy = n->r;
    if (dummy == nullptr) return nullptr;
    while (dummy->l != nullptr) dummy = dummy->l;
    return dummy;
}

long totalPossibleBSTs(long n) {
    if (n <= 1) return 1;
    long res = 0;
    for (long i = 0; i < n; i++) {
        res += totalPossibleBSTs(i) * totalPossibleBSTs(n - i - 1);
    }
    return res;
}

int isBalancedHelper(Node* n, bool& b) {
    if (n == nullptr) return 0;
    int i = isBalancedHelper(n->l, b), j = isBalancedHelper(n->r, b);
    if (abs(i - j) > 1) {
        b = false;
        return 0;
    } else return std::max(i, j) + 1;
}

bool isBalanced(Node* n) {
    bool ans = true;
    isBalancedHelper(n, ans);
    return ans;
}

void printPostUsingPreIn(const std::vector<int>& pre, const std::vector<int>& in) {
    std::unordered_map<int, int> inorderMap;
    for (int i = 0; i < in.size(); i++) {
        inorderMap[in[i]] = i;
    }
    
    std::function<void(int, int, int)> printPost = [&](int preStart, int inStart, int size) -> void {
        if (size <= 0) return;
        int rootVal = pre[preStart];
        int rootInorderIdx = inorderMap[rootVal];
        int leftSize = rootInorderIdx - inStart;
        int rightSize = size - leftSize - 1;
        
        if (leftSize > 0) {
            printPost(preStart + 1, inStart, leftSize);
        }
        
        if (rightSize > 0) {
            printPost(preStart + 1 + leftSize, rootInorderIdx + 1, rightSize);
        }
        
        std::cout << rootVal << " ";
    };
    
    printPost(0, 0, pre.size());
}

void printPreorder(Node* root) {
    if (!root) return;
    std::cout << root->val << " ";
    printPreorder(root->l);
    printPreorder(root->r);
}

void printPostorder(Node* root) {
    if (!root) return;
    printPostorder(root->l);
    printPostorder(root->r);
    std::cout << root->val << " ";
}


void printPreUsingInPost(const std::vector<int>& in, const std::vector<int>& post) {
    std::unordered_map<int, int> inorderMap;
    for (int i = 0; i < in.size(); i++) {
        inorderMap[in[i]] = i;
    }
    
    std::function<void(int, int, int&)> printPre = [&](int inStart, int inEnd, int& postIdx) -> void {
        if (inStart > inEnd || postIdx < 0) return;
        
        int rootVal = post[postIdx];
        postIdx--;
        int rootInorderIdx = inorderMap[rootVal];
        
        std::cout << rootVal << " ";
        

        if (rootInorderIdx + 1 <= inEnd) {
            printPre(rootInorderIdx + 1, inEnd, postIdx);
        }
        

        if (inStart <= rootInorderIdx - 1) {
            printPre(inStart, rootInorderIdx - 1, postIdx);
        }
    };
    
    int postIdx = post.size() - 1;
    printPre(0, in.size() - 1, postIdx);
}

int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->l && !root->r) return 1;
    return countLeafNodes(root->l) + countLeafNodes(root->r);
}

static int diameterHelper(Node* node, int& maxDiam) {
    if (!node) return 0;
    int lh = diameterHelper(node->l, maxDiam);
    int rh = diameterHelper(node->r, maxDiam);
    maxDiam = std::max(maxDiam, lh + rh + 1);
    return std::max(lh, rh) + 1;
}

int diameter(Node* root) {
    int maxDiam = 0;
    diameterHelper(root, maxDiam);
    return maxDiam;
}

void serializeHelper(Node* node, std::ostringstream& out) {
    if (!node) {
        out << "#,";
        return;
    }
    
    out << node->val << ",";
    serializeHelper(node->l, out);
    serializeHelper(node->r, out);
}

std::string serialize(Node* root) {
    std::ostringstream out;
    serializeHelper(root, out);
    std::string s = out.str();
    if (!s.empty()) s.pop_back();
    return s;
}

Node* deserializeHelper(std::queue<std::string>& tokens) {
    if (tokens.empty()) return nullptr;
    std::string t = tokens.front(); 
    tokens.pop();
    if (t == "#") {
        return nullptr;
    }
    
    int val = std::stoi(t);
    Node* node = new Node(val);
    node->l = deserializeHelper(tokens);
    node->r = deserializeHelper(tokens);
    return node;
}

Node* deserialize(const std::string& data) {
    std::queue<std::string> tokens;
    std::istringstream in(data);
    std::string token;
    while (std::getline(in, token, ',')) {
        tokens.push(token);
    }
    
    return deserializeHelper(tokens);
}


void printTreeStructure(Node* root, int space = 0, int height = 4) {
    if (!root) return;
    
    space += height;
    printTreeStructure(root->r, space);
    
    std::cout << std::endl;
    for (int i = height; i < space; i++) std::cout << " ";
    std::cout << root->val << std::endl;
    
    printTreeStructure(root->l, space);
}


void printTreeStructureClear(Node* root, std::string indent = "", bool isRight = true) {
    if (!root) return;
    
    std::cout << indent;
    if (indent != "") {
        std::cout << (isRight ? "R── " : "L── ");
    }
    std::cout << root->val << std::endl;
    
    if (root->l || root->r) {
        if (root->l) {
            printTreeStructureClear(root->l, indent + "    ", false);
        }
        if (root->r) {
            printTreeStructureClear(root->r, indent + "    ", true);
        }
    }
}

class BST {
    Node* root;
    
    void inorder(Node* n) {
        if (n == nullptr) return;
        inorder(n->l);
        std::cout << n->val << " ";
        inorder(n->r);
    }
    
    void preorder(Node* n) {
        if (n == nullptr) return;
        std::cout << n->val << " ";
        preorder(n->l);
        preorder(n->r);
    }
    
    void postorder(Node* n) {
        if (n == nullptr) return;
        postorder(n->l);
        postorder(n->r);
        std::cout << n->val << " ";
    }
    
    void calc_depth(Node* n, int cur_depth = 0) {
        if (n == nullptr) return;
        std::cout << n->val << " has depth " << cur_depth << std::endl;
        calc_depth(n->l, cur_depth + 1);
        calc_depth(n->r, cur_depth + 1);
    }
    
    int calc_height(Node* n) {
        if (n == nullptr) return 0;
        int val = std::max(calc_height(n->l), calc_height(n->r)) + 1;
        std::cout << n->val << " has height " << val - 1 << std::endl;
        return val;
    }
    
    void free(Node* node) {
        if (node == nullptr) return;
        free(node->l);
        free(node->r);
        delete node;
    }
    
    int calc_root_height(Node* n) {
        if (n == nullptr) return 0;
        return std::max(calc_root_height(n->l), calc_root_height(n->r)) + 1;
    }
    
public:

    BST() : root(nullptr) {}
    

    BST(const std::vector<int>& nodes) : root(nullptr) {
        for (auto i : nodes) {
            insert(i);
        }
    }
    
    Node* searchNode(int x) {
        Node* dummy = root;
        while (dummy != nullptr) {
            if (dummy->val > x) dummy = dummy->l;
            else if (dummy->val < x) dummy = dummy->r;
            else break;
        }
        return dummy;
    }
    
    Node* getroot() {
        return root;
    }
    
    int calc_root_height() {
        return calc_root_height(root);
    }
    
    void insert(int x) {
        if (root == nullptr) {
            root = new Node(x);
        } else {
            auto dummy = root;
            while (true) {
                if (x < dummy->val) {
                    if (dummy->l == nullptr) {
                        dummy->l = new Node(x);
                        #ifdef INCLUDE_PARENT
                        dummy->l->parent = dummy;
                        #endif
                        break;
                    } else dummy = dummy->l;
                } else {
                    if (dummy->r == nullptr) {
                        dummy->r = new Node(x);
                        #ifdef INCLUDE_PARENT
                        dummy->r->parent = dummy;
                        #endif
                        break;
                    } else dummy = dummy->r;
                }
            }
        }
    }
    
    void search(int x) {
        Node* dummy = root;
        while (dummy != nullptr) {
            if (dummy->val > x) dummy = dummy->l;
            else if (dummy->val < x) dummy = dummy->r;
            else {
                std::cout << "Value: " << dummy->val << " found" << std::endl;
                return;
            }
        }
        std::cout << "Value: " << x << " not found" << std::endl;
    }
    
    int min() {
        Node* dummy = root;
        if (dummy == nullptr) return -1;
        while (dummy->l != nullptr) {
            dummy = dummy->l;
        }
        return dummy->val;
    }
    
    void printLevelOrder() {
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            std::cout << curr->val << " ";
            if (curr->l != nullptr) q.push(curr->l);
            if (curr->r != nullptr) q.push(curr->r);
        }
        std::cout << std::endl;
    }
    
    int max() {
        Node* dummy = root;
        if (dummy == nullptr) return -1;
        while (dummy->r != nullptr) {
            dummy = dummy->r;
        }
        return dummy->val;
    }
    
    void inorder() {
        inorder(root);
        std::cout << std::endl;
    }
    
    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }
    
    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }
    

    void calc_height() {
        calc_height(root);
    }
    
    void calc_depth() {
        calc_depth(root);
    }
    

    void del(int x) {
        Node* current = root;
        Node* parent = nullptr;
        
        while (current != nullptr && current->val != x) {
            parent = current;
            if (x < current->val) {
                current = current->l;
            } else {
                current = current->r;
            }
        }
        
        if (current == nullptr) return;
        
        Node* replacement = nullptr;
        if (current->l == nullptr && current->r == nullptr) {
            replacement = nullptr;
        }
        else if (current->l == nullptr) {
            replacement = current->r;
        }
        else if (current->r == nullptr) {
            replacement = current->l;
        }
        else {
            Node* successor = current->r;
            Node* successorParent = current;
            while (successor->l != nullptr) {
                successorParent = successor;
                successor = successor->l;
            }
            
            current->val = successor->val;
            if (successorParent == current) {
                successorParent->r = successor->r;
            } else {
                successorParent->l = successor->r;
            }
            
            #ifdef INCLUDE_PARENT
            if (successor->r != nullptr) {
                successor->r->parent = successorParent;
            }
            #endif
            delete successor;
            return;
        }
        
        if (parent == nullptr) {
            root = replacement;
        } else if (parent->l == current) {
            parent->l = replacement;
        } else {
            parent->r = replacement;
        }
        
        #ifdef INCLUDE_PARENT
        if (replacement != nullptr) {
            replacement->parent = parent;
        }
        #endif
        delete current;
    }
    
    ~BST() {
        free(root);
    }
};


void measurePerformance(BST& bst, const std::vector<int>& testData, const std::string& testName) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int val : testData) {
        bst.search(val);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << testName << " - Search time: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Tree height: " << bst.calc_root_height() << std::endl;
}

int main() {
    

    std::cout << "\n--- Question 1 ---" << std::endl;
    Node* testNode = new Node(10);
    std::cout << "Created node with value: " << testNode->val << std::endl;
    #ifdef INCLUDE_PARENT
    std::cout << "Node has parent pointer support: Enabled" << std::endl;
    #else
    std::cout << "Node has parent pointer support: Disabled" << std::endl;
    #endif
    

    std::cout << "\n--- Question 2 ---" << std::endl;
    std::vector<int> bstValues = {50, 30, 70, 20, 40, 60, 80};
    BST bst(bstValues);
    std::cout << "Created BST with values: ";
    for (int val : bstValues) std::cout << val << " ";
    std::cout << std::endl;
    std::cout << "Is valid BST: " << (checkNodeForBST(bst.getroot()) ? "Yes" : "No") << std::endl;
    

    std::cout << "\n--- Question 3 ---" << std::endl;
    Node* node30 = bst.searchNode(30);
    if (node30) {
        Node* successor = findInorderSuccessor(node30);
        std::cout << "Inorder successor of 30: " << (successor ? std::to_string(successor->val) : "None") << std::endl;
    }
    

    std::cout << "\n--- Question 4 ---" << std::endl;
    for (int n = 1; n <= 5; n++) {
        std::cout << "BSTs possible with " << n << " nodes: " << totalPossibleBSTs(n) << std::endl;
    }
    

    std::cout << "\n--- Question 5 ---" << std::endl;
    std::vector<int> preorder = {3, 9, 20, 15, 7};
    std::vector<int> inorder = {9, 3, 15, 20, 7};
    std::cout << "Preorder: ";
    for (int val : preorder) std::cout << val << " ";
    std::cout << "\nInorder: ";
    for (int val : inorder) std::cout << val << " ";
    std::cout << "\nReconstructed Postorder: ";
    printPostUsingPreIn(preorder, inorder);
    std::cout << std::endl;
    

    std::cout << "\n--- Question 6 ---" << std::endl;
    std::vector<int> postorder = {9, 15, 7, 20, 3};
    std::cout << "Inorder: ";
    for (int val : inorder) std::cout << val << " ";
    std::cout << "\nPostorder: ";
    for (int val : postorder) std::cout << val << " ";
    std::cout << "\nReconstructed Preorder: ";
    printPreUsingInPost(inorder, postorder);
    std::cout << std::endl;
    

    std::cout << "\n--- Question 7 ---" << std::endl;
    std::vector<int> threeNodes = {1, 2, 3};
    std::cout << "Target inorder sequence: ";
    for (int val : threeNodes) std::cout << val << " ";
    std::cout << std::endl;
    
    std::vector<Node*> allTrees = getAllTreesWithInorder(threeNodes);
    std::cout << "Total structurally distinct trees: " << allTrees.size() << std::endl;
    std::cout << "Expected: 5 trees (Catalan number C_3 = 5)" << std::endl;
    

    for (size_t i = 0; i < allTrees.size(); i++) {
        std::cout << "\n  Tree " << (i + 1) << ":" << std::endl;
        printTreeStructureClear(allTrees[i], "    ");
        

        bool isCorrect = hasCorrectInorder(allTrees[i], threeNodes);
        std::cout << "    Inorder verification: " << (isCorrect ? "PASS [1,2,3]" : "FAIL") << std::endl;
    }
    

    std::cout << "\n--- Question 8 ---" << std::endl;
    
    Node* tree1 = createTree1();
    Node* tree2 = createTree2();
    
    std::cout << "\n  Right Chain Tree:" << std::endl;
    printTreeStructureClear(tree1, "    ");
    std::cout << "    Preorder: ";
    printPreorder(tree1);
    std::cout << "\n    Postorder: ";
    printPostorder(tree1);
    
    std::cout << "\n\n  Left Chain Tree:" << std::endl;
    printTreeStructureClear(tree2, "    ");
    std::cout << "    Preorder: ";
    printPreorder(tree2);
    std::cout << "\n    Postorder: ";
    printPostorder(tree2);
    
    

    std::cout << "\n--- Question 9 ---" << std::endl;
    std::vector<int> balancedData = {50, 25, 75, 12, 37, 62, 87};
    BST balancedBST(balancedData);
    std::vector<int> skewedData = {1, 2, 3, 4, 5, 6, 7};
    BST skewedBST(skewedData);
    std::vector<int> searchKeys = {25, 50, 75, 37};
    
    std::cout << "Performance comparison:" << std::endl;
    measurePerformance(balancedBST, searchKeys, "Balanced BST");
    measurePerformance(skewedBST, searchKeys, "Skewed BST");
    

    std::cout << "\n--- Question 10 ---" << std::endl;
    std::cout << "Node structure includes parent pointers" << std::endl;
    std::cout << "All BST operations maintain parent relationships" << std::endl;
    

    std::cout << "\n--- Question 11 ---" << std::endl;
    std::cout << "Balanced BST is height-balanced: " << (isBalanced(balancedBST.getroot()) ? "Yes" : "No") << std::endl;
    std::cout << "Skewed BST is height-balanced: " << (isBalanced(skewedBST.getroot()) ? "Yes" : "No") << std::endl;
    

    std::cout << "\n--- Question 12 ---" << std::endl;
    Node* lca = findLCA(bst.getroot(), 20, 40);
    std::cout << "LCA of nodes 20 and 40: " << (lca ? std::to_string(lca->val) : "Not found") << std::endl;
    lca = findLCA(bst.getroot(), 60, 80);
    std::cout << "LCA of nodes 60 and 80: " << (lca ? std::to_string(lca->val) : "Not found") << std::endl;
    

    std::cout << "\n--- Question 13 ---" << std::endl;
    std::cout << "Number of leaf nodes in BST: " << countLeafNodes(bst.getroot()) << std::endl;
    

    std::cout << "\n--- Question 14 ---" << std::endl;
    std::cout << "Diameter of BST: " << diameter(bst.getroot()) << std::endl;
    

    std::cout << "\n--- Question 15 ---" << std::endl;
    std::string serialized = serialize(bst.getroot());
    std::cout << "Serialized BST: " << serialized << std::endl;
    Node* deserialized = deserialize(serialized);
    std::cout << "Successfully deserialized tree" << std::endl;
    

    std::cout << "\n--- Basic BST Operations Demonstration ---" << std::endl;
    BST demoBST;
    
    std::cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::vector<int> demoValues = {50, 30, 70, 20, 40, 60, 80};
    for (int val : demoValues) {
        demoBST.insert(val);
    }
    
    std::cout << "Inorder traversal: ";
    demoBST.inorder();
    std::cout << "Preorder traversal: ";
    demoBST.preorder();
    std::cout << "Postorder traversal: ";
    demoBST.postorder();
    std::cout << "Level-order traversal: ";
    demoBST.printLevelOrder();
    std::cout << "Minimum value: " << demoBST.min() << std::endl;
    std::cout << "Maximum value: " << demoBST.max() << std::endl;
    
    std::cout << "Searching for 40: ";
    demoBST.search(40);
    std::cout << "Searching for 25: ";
    demoBST.search(25);
    
    std::cout << "\nHeight and depth calculation:" << std::endl;
    demoBST.calc_height();
    std::cout << "\nDepth calculation:" << std::endl;
    demoBST.calc_depth();
    
    std::cout << "\nDeleting node 30..." << std::endl;
    demoBST.del(30);
    std::cout << "Inorder after deletion: ";
    demoBST.inorder();
    
    

    delete testNode;
    
    return 0;
}