#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <vector>
#define INCLUDE_PARENT
struct Node {
    int val;
    Node *l,*r;
#ifdef INCLUDE_PARENT
    Node* parent;
    Node(int val=0,Node* l=nullptr,Node* r=nullptr,Node* parent=nullptr): val(val),l(l),r(r),parent(parent) {}
#else
    Node(int val=0,Node* l=nullptr,Node* r=nullptr): val(val),l(l),r(r) {}
#endif
};
bool checkNodeForBST(Node* n) {
    if (n==nullptr) return true;
    if ((n->l==nullptr||n->l->val>n->val)&&(n->r==nullptr||n->r->val<n->val)) return false;
    else return checkNodeForBST(n->r)&&checkNodeForBST(n->l);
}
Node* findInorderSuccessor(Node* n) {
    Node* dummy=n->r;
    if (dummy==nullptr) return nullptr;
    while (dummy->l!=nullptr) dummy=dummy->l;
    return dummy;
}
long totalPossibleBSTs(long n) {
    if (n<=1) return 1;
    long res=0;
    for (long i=0;i<n;i++) res+=totalPossibleBSTs(i)*totalPossibleBSTs(n-i-1);
    return res;
}
int isBalancedHelper(Node* n,bool& b) {
    if (!b||n==nullptr) return 0;
    int i=isBalancedHelper(n->l,b),j=isBalancedHelper(n->r,b);
    if (abs(i-j)>1) {
        b=0;
        return 0;
    } else return std::max(i,j)+1;
}
bool isBalanced(Node* n) {
    bool ans=true;
    isBalancedHelper(n,ans);
    return ans;
}
void printPostUsingPreIn(const std::vector<int>& pre, const std::vector<int>& in) {
    std::unordered_map<int,int> inorderMap;
    for (int i=0;i<in.size();i++) {
        inorderMap[in[i]]=i;
    }
    std::function<void(int,int,int)> printPost=[&](int preStart,int inStart,int size)->void {
        if (size<=0) return;
        int rootVal=pre[preStart];
        int rootInorderIdx=inorderMap[rootVal];
        int leftSize=rootInorderIdx-inStart;
        int rightSize=size-leftSize-1;
        if (leftSize>0) {
            printPost(preStart+1,inStart,leftSize);
        }
        if (rightSize>0) {
            printPost(preStart+1+leftSize,rootInorderIdx+1,rightSize);
        }
        std::cout<<rootVal<<" ";
    };
    printPost(0,0,pre.size());
}
void printPreUsingInPost(const std::vector<int>& in, const std::vector<int>& post) {
    std::unordered_map<int,int> inorderMap;
    for (int i=0;i<in.size();i++) {
        inorderMap[in[i]]=i;
    }
    std::function<void(int,int,int,int&)> printPre=[&](int inStart,int inEnd,int postEnd,int& postIdx)->void {
        if (inStart>inEnd) return;
        int rootVal=post[postIdx];
        postIdx--;
        int rootInorderIdx=inorderMap[rootVal];
        int leftSize=rootInorderIdx-inStart;
        int rightSize=inEnd-rootInorderIdx;
        std::cout<<rootVal<<" ";
        if (leftSize>0) {
            printPre(inStart,rootInorderIdx-1,postEnd-rightSize-1,postIdx);
        }
        if (rightSize>0) {
            printPre(rootInorderIdx+1,inEnd,postEnd-1,postIdx);
        }
    };
    int postIdx=post.size()-1;
    printPre(0,in.size()-1,post.size()-1,postIdx);
}

int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->l && !root->r) return 1;
    return countLeafNodes(root->l) + countLeafNodes(root->r);
}

// 14. Compute diameter of a binary tree.
// Returns the diameter (number of nodes on longest path).
// Uses a helper to compute height and track max diameter.
static int diameterHelper(Node* node, int& maxDiam) {
    if (!node) return 0;
    int lh = diameterHelper(node->l, maxDiam);
    int rh = diameterHelper(node->r, maxDiam);
    // path through this node = lh + rh + 1
    maxDiam = std::max(maxDiam, lh + rh + 1);
    // height of this node
    return std::max(lh, rh) + 1;
}

int diameter(Node* root) {
    int maxDiam = 0;
    diameterHelper(root, maxDiam);
    return maxDiam;
}

// 15. Serialize and deserialize a binary tree using preorder with '#' for null.
// Preorder serialization
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
    if (!s.empty()) s.pop_back(); // remove trailing comma
    return s;
}

// Deserialization helper
Node* deserializeHelper(std::queue<std::string>& tokens) {
    if (tokens.empty()) return nullptr;
    std::string t = tokens.front(); tokens.pop();
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
class BST {
    Node* root;
    void inorder(Node* n) {
        if (n==nullptr) return;
        inorder(n->l);
        std::cout<<n->val<<" ";
        inorder(n->r);
    }
    void preorder(Node* n) {
        if (n==nullptr) return;
        std::cout<<n->val<<" ";
        preorder(n->l);
        preorder(n->r);
    }
    void postorder(Node* n) {
        if (n==nullptr) return;
        postorder(n->l);
        postorder(n->r);
        std::cout<<n->val<<" ";
    }
    Node* searchNode(int x) {
        Node* dummy=root;
        while (dummy!=nullptr) {
            if (dummy->val>x) dummy=dummy->l;
            else if (dummy->val<x) dummy=dummy->r;
            else break;
        }
        return dummy;
    }
    void calc_depth(Node* n,int cur_depth=0) {
        if (n==nullptr) return;
        std::cout<<n->val<<" has depth "<<cur_depth++<<std::endl;
        calc_depth(n->l,cur_depth);
        calc_depth(n->r,cur_depth);
    }
    int calc_height(Node* n) {
        if (n==nullptr) return 0;
        int val=std::max(calc_height(n->l),calc_height(n->r))+1;
        std::cout<<n->val<<" has height "<<val<<std::endl;
        return val;
    }
    void free(Node* node) {
        if (node==nullptr) return;
        free(node->l);
        free(node->r);
        delete node;
    }
public:
    Node* getroot() {
        return root;
    }
    void insert(int x) {
        if (root==nullptr) {
            root=new Node(x);
        } else {
            auto dummy=root;
            while (true) {
                if (x<dummy->val) {
                    if (dummy->l==nullptr) {
                        dummy->l=new Node(x);
#ifdef INCLUDE_PARENT
                        dummy->l->parent=dummy;
#endif
                        break;
                    } else dummy=dummy->l;
                } else {
                    if (dummy->r==nullptr) {
                        dummy->r=new Node(x);
#ifdef INCLUDE_PARENT
                        dummy->r->parent=dummy;
#endif
                        break;
                    } else dummy=dummy->r;
                }
            }
        }
    }
    void search(int x) {
        Node* dummy=root;
        while (dummy!=nullptr) {
            if (dummy->val>x) dummy=dummy->l;
            else if (dummy->val<x) dummy=dummy->r;
            else {
                std::cout<<"Value: "<<x<<" found!"<<std::endl;
                return;
            }
        }
        std::cout<<"Value: "<<x<<" not found!"<<std::endl;
    }
    Node* lowestCommonAncestor(int x, int y) {
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
    int min() {
        Node* dummy=root;
        if (dummy==nullptr) return -1;
        while (dummy->l!=nullptr) {
            dummy=dummy->l;
        }
        return dummy->val;
    }
    void printLevelOrder() {
        if (root==nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr=q.front();
            q.pop();
            std::cout<<curr->val<<" ";
            if (curr->l!=nullptr) q.push(curr->l);
            if (curr->r!=nullptr) q.push(curr->r);
        }
        std::cout << std::endl;
    }
    int max() {
        Node* dummy=root;
        if (dummy==nullptr) return -1;
        while (dummy->r!=nullptr) {
            dummy=dummy->r;
        }
        return dummy->val;
    }
    void inorder() {
        inorder(root);
        std::cout<<std::endl;
    }
    void preorder() {
        preorder(root);
        std::cout<<std::endl;
    }
    void postorder() {
        postorder(root);
        std::cout<<std::endl;
    }
    void calc_depth() {
        calc_depth(root);
    }
    void calc_height() {
        calc_height(root);
    }
    void deleteNode(int x) {
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
    BST(std::vector<int>& nodes) {
        for (auto i:nodes) {
            insert(i);
        }
    }
    ~BST() {
        free(root);
    }
};
