#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
//二叉树
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

//递归方法更简洁，但在大树情况下可能会导致栈溢出。迭代方法稍微复杂，但在处理大树时更为安全。
//利用递归实现：三种顺序遍历的顺序是一致的，不同的只是压入res栈的时机
//先序遍历 https://leetcode.cn/problems/binary-tree-preorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        res.push_back(node->val);//中
        traversal(node->left, res);//左
        traversal(node->right, res);//右
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};

//中序遍历 https://leetcode.cn/problems/binary-tree-inorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        traversal(node->left, res);//左
        res.push_back(node->val);//中
        traversal(node->right, res);//右
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
//后序遍历 https://leetcode.cn/problems/binary-tree-postorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        traversal(node->right, res);//右
        traversal(node->left, res);//左
        res.push_back(node->val);//中
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
/*master公式：在计算涉及递归的算法的时候，计算复杂度就会变得有些麻烦。Master公式就是用来进行剖析递归行为和递归行为时间复杂度的估算的
T(N) = a * T(N / b) + O(N ^ d)  n表示问题的规模，a表示递归的次数也就是生成的子问题数，N / b表示子问题的规模。O(N ^ d)表示除了递归操作以外其余操作的复杂度
①当d<logb a时，时间复杂度为O(N ^ (logb a))
②当d=logb a时，时间复杂度为O((N ^ d) * logN)
③当d>logb a时，时间复杂度为O(N ^ d)
注意：子问题规模必须等分，不管你是分成几部分
*/

//利用栈实现
//前序遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root != nullptr) {
            vector<TreeNode*> tree;
            tree.push_back(root);
            while (!tree.empty()) {
                root = tree.back();
                tree.pop_back();
                ans.push_back(root->val);

                // 右侧先入栈、晚弹出；左侧后入栈、先弹出
                if (root->right != nullptr) tree.push_back(root->right);
                if (root->left != nullptr) tree.push_back(root->left);
            }
        }
        return ans;
    }
};
//中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> tree;
        TreeNode* cur = root;
        while (cur != nullptr || !tree.empty()) {
            // 先将所有左子节点压入栈
            while (cur != nullptr) {
                tree.push(cur);
                cur = cur->left;
            }
            // 弹出栈顶节点并访问
            cur = tree.top();//cur得到了更新
            tree.pop();
            res.push_back(cur->val);
            // 处理右子树
            cur = cur->right;
        }
        return res;
    }
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root != nullptr) {
            vector<TreeNode*> tree;
            while (!tree.empty() || root != nullptr) {  //节点没有子树并且tree栈为空时停止
                if (root != nullptr) {
                    tree.push_back(root);//节点先进栈
                    root = root->left;//先从节点转到左子树
                }else {//当左子树为空时
                    root = tree.back();
                    tree.pop_back();//弹出左子树使上一级节点在栈顶
                    ans.push_back(root->val);//上一级节点先压入ans
                    root = root->right;//从节点的左子树转到右子树
                }
            }
        }
        return ans;
    }
};

//后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root != nullptr) {
            stack<TreeNode*> tree;
            tree.push(root);//节点先进栈最后输出
            while (!tree.empty()) {
                TreeNode* cur = tree.top();
                if ((cur->left != nullptr && root != cur->left && root != cur->right)) {
                    tree.push(cur->left);
                }else if (cur->right != nullptr && root != cur->right) {
                    tree.push(cur->right);
                }else {
                    ans.push_back(cur->val);
                    root = tree.top();
                    tree.pop();
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root != nullptr) {
            vector<TreeNode*> tree;
            tree.push_back(root);
            while (!tree.empty()) {
                root = tree.back();
                tree.pop_back();
                ans.push_back(root->val);
                if (root->left != nullptr) tree.push_back(root->left);
                if (root->right != nullptr) tree.push_back(root->right);
            }
        }
        // 前序遍历反转结果以获得后序遍历
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
