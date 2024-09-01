#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
//������
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

//�ݹ鷽������࣬���ڴ�������¿��ܻᵼ��ջ���������������΢���ӣ����ڴ������ʱ��Ϊ��ȫ��
//���õݹ�ʵ�֣�����˳�������˳����һ�µģ���ͬ��ֻ��ѹ��resջ��ʱ��
//������� https://leetcode.cn/problems/binary-tree-preorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        res.push_back(node->val);//��
        traversal(node->left, res);//��
        traversal(node->right, res);//��
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};

//������� https://leetcode.cn/problems/binary-tree-inorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        traversal(node->left, res);//��
        res.push_back(node->val);//��
        traversal(node->right, res);//��
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
//������� https://leetcode.cn/problems/binary-tree-postorder-traversal/description/?envType=problem-list-v2&envId=lnOYkJdd&
class Solution {
private:
    void traversal(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        traversal(node->right, res);//��
        traversal(node->left, res);//��
        res.push_back(node->val);//��
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
/*master��ʽ���ڼ����漰�ݹ���㷨��ʱ�򣬼��㸴�ӶȾͻ�����Щ�鷳��Master��ʽ�����������������ݹ���Ϊ�͵ݹ���Ϊʱ�临�ӶȵĹ����
T(N) = a * T(N / b) + O(N ^ d)  n��ʾ����Ĺ�ģ��a��ʾ�ݹ�Ĵ���Ҳ�������ɵ�����������N / b��ʾ������Ĺ�ģ��O(N ^ d)��ʾ���˵ݹ����������������ĸ��Ӷ�
�ٵ�d<logb aʱ��ʱ�临�Ӷ�ΪO(N ^ (logb a))
�ڵ�d=logb aʱ��ʱ�临�Ӷ�ΪO((N ^ d) * logN)
�۵�d>logb aʱ��ʱ�临�Ӷ�ΪO(N ^ d)
ע�⣺�������ģ����ȷ֣��������Ƿֳɼ�����
*/

//����ջʵ��
//ǰ�����
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

                // �Ҳ�����ջ��������������ջ���ȵ���
                if (root->right != nullptr) tree.push_back(root->right);
                if (root->left != nullptr) tree.push_back(root->left);
            }
        }
        return ans;
    }
};
//�������
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> tree;
        TreeNode* cur = root;
        while (cur != nullptr || !tree.empty()) {
            // �Ƚ��������ӽڵ�ѹ��ջ
            while (cur != nullptr) {
                tree.push(cur);
                cur = cur->left;
            }
            // ����ջ���ڵ㲢����
            cur = tree.top();//cur�õ��˸���
            tree.pop();
            res.push_back(cur->val);
            // ����������
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
            while (!tree.empty() || root != nullptr) {  //�ڵ�û����������treeջΪ��ʱֹͣ
                if (root != nullptr) {
                    tree.push_back(root);//�ڵ��Ƚ�ջ
                    root = root->left;//�ȴӽڵ�ת��������
                }else {//��������Ϊ��ʱ
                    root = tree.back();
                    tree.pop_back();//����������ʹ��һ���ڵ���ջ��
                    ans.push_back(root->val);//��һ���ڵ���ѹ��ans
                    root = root->right;//�ӽڵ��������ת��������
                }
            }
        }
        return ans;
    }
};

//�������
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root != nullptr) {
            stack<TreeNode*> tree;
            tree.push(root);//�ڵ��Ƚ�ջ������
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
        // ǰ�������ת����Ի�ú������
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
