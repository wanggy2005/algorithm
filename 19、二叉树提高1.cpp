//BFS������������㷨��Breadth First Search��
//һ���������Ĳ�������������أ������ҷ������нڵ㣩https://leetcode.cn/problems/binary-tree-level-order-traversal/
//1.����hashmap�������Ϣ+����
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root != nullptr) {    
        queue<TreeNode*> q;// ʹ�ö��������й����������
        unordered_map<TreeNode*, int> levels;// ���ڴ洢ÿ���ڵ�Ĳ���
        // �����ڵ������У�����¼�����Ϊ0
        q.push(root);
        levels[root] = 0;
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();// �Ӷ�����ȡ����ǰ�ڵ�
            int level = levels[cur];// ��ȡ��ǰ�ڵ�Ĳ���
            // �����ǰ�㻹�����ڣ������һ���µĿղ�
            if (ans.size() == level) {
                ans.push_back(vector<int>());
            }
            ans[level].push_back(cur->val);// ����ǰ�ڵ��ֵ���뵱ǰ��
            if (cur->left != nullptr) {// ������ӽڵ���ڣ����������в���¼�����
                q.push(cur->left);
                levels[cur->left] = level + 1;
            }
            if (cur->right != nullptr) {// ������ӽڵ���ڣ����������в���¼�����
                q.push(cur->right);
                levels[cur->right] = level + 1;
            }
        }
    }
    return ans;
}
//2.���װ棺�����������У���size��������ѭ��
const int MAXN = 2001; 
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;  // �洢ÿ��Ľڵ�ֵ
    if (root != nullptr) {
        int l = 0, r = 0;  // ���е�����ָ��
        TreeNode* queue[MAXN];// ʹ�����鶨�����
        queue[r++] = root;  // �����ڵ������У���������ָ��
        while (l < r) {
            int size = r - l;  // ��ǰ��Ľڵ���
            vector<int> list;  // �洢��ǰ��Ľڵ�ֵ
            // ������ǰ������нڵ�
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = queue[l++];  // �Ӷ�����ȡ����ǰ�ڵ㣬��������ָ��
                list.push_back(cur->val);  // ����ǰ�ڵ��ֵ��ӵ���ǰ��Ľ����
                if (cur->left != nullptr) {// ������ӽڵ���ڣ����������У���������ָ��
                    queue[r++] = cur->left;
                }
                if (cur->right != nullptr) {// ������ӽڵ���ڣ����������У���������ָ��
                    queue[r++] = cur->right;
                }
            }
            ans.push_back(list);// ����ǰ��Ľ����ӵ����ս����
        }
    }
    return ans;
}
//�����������ľ���β������ https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
//���ȴ������ң��ٴ������������һ��������Դ����ƣ������֮�佻�����
const int MAXN = 2001;
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans; 
    if (root != nullptr) {
        int l = 0, r = 0; 
        TreeNode* queue[MAXN];
        queue[r++] = root;  
        bool reverse = false;  // ����Ƿ���Ҫ�������
        while (l < r) {
            int size = r - l;
            vector<int> list;
            // ������ǰ������нڵ㣬���� `reverse` ��Ǿ�����������
            for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k = 0; 
                k < size;
                i += j, ++k) {
                TreeNode* cur = queue[i];  // ȡ����ǰ�ڵ�
                list.push_back(cur->val);  // ���ڵ�ֵ��ӵ���ǰ��Ľ����
            }
            //���������ռ��ӽڵ�
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = queue[l++];  
                if (cur->left != nullptr) {
                    queue[r++] = cur->left;  
                }
                if (cur->right != nullptr) {
                    queue[r++] = cur->right; 
                }
            }
            ans.push_back(list);
            reverse = !reverse;// �л���������
        }
    }
    return ans; 
}
//��������������������� https://leetcode.cn/problems/maximum-width-of-binary-tree/
/*����һ�ö������ĸ��ڵ�root��������������ȡ�
��������������в������Ŀ�� ��ÿһ��Ŀ�ȱ�����Ϊ�ò���������ҵķǿսڵ㣨���������˵㣩֮��ĳ��ȡ�
��������������������������ṹ��ͬ�����˵������һЩ���쵽��һ���null�ڵ㣬��Щnull�ڵ�Ҳ���볤�ȡ�*/
//�ѵĽڵ���+������ȱ���
#define MAXN 3001
class Solution {
public:
    TreeNode* nodeQueue[MAXN]; // ���ڴ洢���ڵ�Ķ���
    unsigned long long indexQueue[MAXN]; // ���ڴ洢���ڵ�������Ķ���
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        unsigned long long ans = 1; // ��ʼ�������Ϊ1
        int l = 0, r = 0;
        //��֤�������е��±�ʼ�ձ���ͬ��
        nodeQueue[r] = root; // ���ڵ����
        indexQueue[r++] = 1; // ���ڵ������Ϊ1
        while (l < r) {
            int size = r - l;
            ans = max(ans, indexQueue[r - 1] - indexQueue[l] + 1); // ���������
            for (int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue[l]; // ��ǰ�ڵ�
                unsigned long long id = indexQueue[l++]; // ��ǰ�ڵ������
                if (node->left) { // ������ӽڵ����
                    nodeQueue[r] = node->left; // ���ӽڵ����
                    indexQueue[r++] = id * 2; // ���ӽڵ������
                }
                if (node->right) { // ������ӽڵ����
                    nodeQueue[r] = node->right; // ���ӽڵ����
                    indexQueue[r++] = id * 2 + 1; // ���ӽڵ������
                }
            }
        }
        return ans; // ���������
    }
};


//DFS������������㷨��Depth First Search��
//�ġ���������ģ�1�������� https://leetcode.cn/problems/maximum-depth-of-binary-tree/
//����������������ָ�Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
//��2����С��� https://leetcode.cn/problems/minimum-depth-of-binary-tree/
//��С����ǴӸ��ڵ㵽���Ҷ�ڵ�����·���ϵĽڵ�������
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {//��ǰ����Ϊ����
            return 0;
        }
        if (root->left == nullptr && root->right == nullptr) {//��ǰ�ڵ�ΪҶ�ڵ�
            return 1;
        }
        int min_depth = INT_MAX;//��Ϊ��ֵ���ڲ�Ӱ��Ƚϵ�ǰ���±�֤����Ƚ���ʽ��һ����
        if (root->left != nullptr) {
            min_depth = min(minDepth(root->left), min_depth);
        }
        if (root->right != nullptr) {
            min_depth = min(minDepth(root->right), min_depth);
        }
        return min_depth + 1;
    }
};
//ʹ�ù�����������ķ�����������������
//�������ҵ�һ��Ҷ�ӽڵ�ʱ��ֱ�ӷ������Ҷ�ӽڵ����ȡ�����������������ʱ�֤��������������Ҷ�ӽڵ�����һ����С��
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        queue<pair<TreeNode*, int> > que;
        que.emplace(root, 1);
/*empalce�����ԣ�
������push��insert��Ա����ʱ�����ǽ�Ԫ�����͵Ķ��󴫵ݸ����ǣ���Щ���󱻿����������С�
�������ǵ���һ��emplace��Ա����ʱ�����ǽ��������ݸ�Ԫ�����͵Ĺ��캯����
emplace��Աʹ����Щ����������������ڴ�ռ���ֱ�ӹ���Ԫ�ء�*/
        while (!que.empty()) {
            TreeNode* node = que.front().first;
            int depth = que.front().second;
            que.pop();
            if (node->left == nullptr && node->right == nullptr) {
                return depth;
            }
            if (node->left != nullptr) {
                que.emplace(node->left, depth + 1);
            }
            if (node->right != nullptr) {
                que.emplace(node->right, depth + 1);
            }
        }
        return 0;
    }
};


//�塢�������������л��ͷ����л� https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
/*���л��ǽ�һ�����ݽṹ���߶���ת��Ϊ�����ı���λ�Ĳ������������Խ�ת��������ݴ洢��һ���ļ������ڴ��У�
  ͬʱҲ����ͨ�����紫�䵽��һ���������������ȡ�෴��ʽ�ع��õ�ԭ���ݡ�
  ����������ܽ������л��뷴���л�������ͺ����������*/
/*https://blog.csdn.net/weixin_45031801/article/details/136921743
* 
���䣺stringstream ������ͷ�ļ� <sstream>,��C++�ṩ��ר�����ڴ����ַ����� ������� ����
<sstream>�����������ࣺistringstream��ostringstream��stringstream���ֱ����������������롢������������������
1.����
string s("hello stringstream");
stringstream ss;
ss << s;
cout << ss.str() << endl;
������
stringstream ss("hello stringstream");
cout << ss.str() << endl;��
2. stringstream  ���Խ��洢���ڲ����ַ����������Ҫ���� str() ����������ֱ�������
cout << ss.str() << endl;
3.���� stringstream ȥ���ַ����ո�
stringstream Ĭ�����Կո����ָ��ַ����ģ����� stringstream ȥ���ַ����ո�ǳ����㣺
int main(){
    stringstream ss("hello string and stringstream");
    string str;
    // ע�⣺ stringstream ��һ������һ������ �����롰 string ��
    while (ss >> str){
        cout << str << endl;
    }
    return 0;
}
�����
    hello
    string
    and
    stringstream
4.����ת��
ʹ�� stringstream ��������ת��
������һ��ʹ�� stringstream ������ת��Ϊ�ַ��������ӣ�
#include <sstream>
#include <iostream>
#include <string>
int main() {
    int num = 123;
    sstringstream ss;
    ss << num; // ��������������
    string str = ss.str(); // ʹ��str()���� ��������ȡ�ַ���
    cout << str << endl; // �����123
}
��������Ҳ���Խ��ַ���ת��Ϊ��ֵ���ͣ�
int main() {
    string str = "456abc";
    stringstream ss(str); // ��ʼ��stringstream
    int num;
    ss >> num; // ��������ȡ����
    cout << num << endl; // �����456
}

getline �� C++ ��׼����һ�����ڴ������������ļ����ַ���������׼����ȣ��ж�ȡһ���ַ��ĺ���
��ȡ���У�getline ��������������ж�ȡһ�����ݣ�ֱ���������з���\n�����������Ὣ���з������ڽ���ַ����С�
�ָ�����getline �����Խ��ܵ�����������ָ���н����ķָ��������û��ָ����Ĭ��Ϊ���з�������getline(cin, line, ',');�⽫���ȡֱ����������Ϊֹ�����ݡ�
����ֵ��getline ��������һ�� istream& ������ɹ���ȡ�У��򷵻������������������� EOF���ļ����������򷵻�һ������״̬*/
class Codec {
private:
    void serializeHelper(TreeNode* root, stringstream& ss) {// �ݹ�ؽ����������л�Ϊ�ַ���
        if (root == nullptr) {
            ss << "#,";  // ����ڵ�Ϊ�գ��� "#" ��ʾ�������϶�����Ϊ�ָ���
        }else {
            ss << root->val << ",";  // ���ڵ��ֵ�����ַ������������϶���
            serializeHelper(root->left, ss);  // �ݹ鴦��������
            serializeHelper(root->right, ss);  // �ݹ鴦��������
        }
    }
    TreeNode* deserializeHelper(const vector<string>& vals) {//�ݹ�ؽ��ַ��������л�Ϊ������
        if (index >= vals.size()) return nullptr;  // ��ֹ����Խ��
        string cur = vals[index++];  // ��ȡ��ǰֵ������������
        if (cur == "#") {  // �����ǰֵ�� "#", ��ʾ����һ���սڵ�
            return nullptr;
        }else {
            // ���򴴽�һ���µĽڵ㣬���ݹ鹹����������
            TreeNode* node = new TreeNode(stoi(cur)); //stoi �� C++11 ��׼�������һ�����������ڽ��ַ���ת��Ϊ������int������
            node->left = deserializeHelper(vals);  // �ݹ鹹��������
            node->right = deserializeHelper(vals);  // �ݹ鹹��������
            return node;
        }
    }
    int index = 0;  // ����������׷�ٵ�ǰ�����Ľڵ�λ��
public:
    string serialize(TreeNode* root) {// �����������л�Ϊ�ַ���
        stringstream ss;
        serializeHelper(root, ss);  
        return ss.str();  // �������л�����ַ���
    }
    TreeNode* deserialize(string data) {// ���ַ��������л�Ϊ������
        vector<string> vals;
        stringstream ss(data);  // ���ַ���ת��Ϊ�ַ������Ա��������
        string item;
        // ʹ�ö��ŷָ��ַ������洢�� vector ��
        while (getline(ss, item, ',')) {
            vals.push_back(item);
        }
        index = 0;  // ��ʼ������
        return deserializeHelper(vals);  // ���ø����������еݹ鷴���л�
    }
};
//�����������������л��ͷ����л� https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
class Codec {
private:
    TreeNode* generate(const string& val) {
        return val == "#" ? nullptr : new TreeNode(stoi(val));
    }
public:
    string serialize(TreeNode* root) {
        stringstream builder;
        if (root != nullptr) {
            builder << root->val << ",";
            queue<TreeNode*> q;
            q.push(root);
            while (!q.empty()) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left != nullptr) {
                    builder << node->left->val << ",";
                    q.push(node->left);
                }else {
                    builder << "#,";
                }
                if (node->right != nullptr) {
                    builder << node->right->val << ",";
                    q.push(node->right);
                }else {
                    builder << "#,";
                }
            }
        }
        return builder.str();
    }
    TreeNode* deserialize(const string& data) {
        if (data.empty()) {
            return nullptr;
        }
        stringstream ss(data);
        string item;
        vector<string> nodes;
        while (getline(ss, item, ',')) {
            nodes.push_back(item);
        }
        int index = 0;//��־��һ���½��Ŀ�ʼ
        TreeNode* root = generate(nodes[index++]);
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();
            cur->left = generate(nodes[index++]);
            cur->right = generate(nodes[index++]);
            if (cur->left != nullptr) {
                q.push(cur->left);
            }
            if (cur->right != nullptr) {
                q.push(cur->right);
            }
        }
        return root;
    }
};

//�ߡ���������������������й�������� https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
//���������������� preorder �� inorder ������ preorder �Ƕ���������������� inorder ��ͬһ����������������빹�����������������ڵ㡣
//�����������ͷһ������ǰ�������������ķ�Χ
class Solution {
public:
    TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
        if (pre.empty() || in.empty() || pre.size() != in.size()) {
            return nullptr;
        }
        unordered_map<int, int> map;
        for (int i = 0; i < in.size(); i++) {
            map[in[i]] = i;
        }
        return f(pre, 0, pre.size() - 1, in, 0, in.size() - 1, map);
    }
private:
    TreeNode* f(vector<int>& pre, int l1, int r1, vector<int>& in, int l2, int r2, unordered_map<int, int>& map) {
        if (l1 > r1) {
            return nullptr;
        }
        TreeNode* head = new TreeNode(pre[l1]);
        int k = map[pre[l1]];
        // pre : l1(........)[.......r1]
        // in  : (l2......)k[........r2]
        // (...)��������Ӧ��[...]�������Ķ�Ӧ
        head->left = f(pre, l1 + 1, l1 + k - l2, in, l2, k - 1, map);
        head->right = f(pre, l1 + k - l2 + 1, r1, in, k + 1, r2, map);
        return head;
    }
};

//�ˡ���֤��ȫ������ https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
//��һ�� ��ȫ������ �У��������һ���⣬���в㶼����ȫ�������������һ���е����нڵ㶼�����ܿ������һ�㣨�� h �㣩�п��԰��� 1 �� 2h ���ڵ㡣
const int MAXN = 101;  // ���ڵ�����
class Solution {
public:
    TreeNode* queue[MAXN]; 
    int l, r;  
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        l = r = 0;
        queue[r++] = root;
        bool leaf = false;  // �Ƿ�����������ȫ�ڵ�
        while (l < r) {
            root = queue[l++];
            if ((root->left == nullptr && root->right != nullptr) ||
                (leaf && (root->left != nullptr || root->right != nullptr))) {
                return false;
            }
            if (root->left != nullptr) {
                queue[r++] = root->left;
            }
            if (root->right != nullptr) {
                queue[r++] = root->right;
            }
            if (root->left == nullptr || root->right == nullptr) {
                leaf = true;  // ���ΪҶ�ڵ㣨����ȫ�ڵ㣩
            }
        }
        return true;
    }
};

//�š�����ȫ�������Ľڵ����(Ҫ��ʱ�临�Ӷȵ���O(n)) https://leetcode.cn/problems/count-complete-tree-nodes/
class Solution {
public:
    int countNodes(TreeNode* head) {
        if (head == nullptr) {
            return 0;
        }
        return f(head, 1, mostLeft(head, 1));
    }
private:
    // ������ cur Ϊ���������Ľڵ���
    int f(TreeNode* cur, int level, int h) {
        if (level == h) {
            return 1;
        }
        if (mostLeft(cur->right, level + 1) == h) {
            // ������������ڵ�ﵽ���ĸ߶�
            return (1 << (h - level)) /*�������Ľڵ���*/ + f(cur->right, level + 1, h);/*���ҽڵ㿪ʼ�ݹ�*/
        }else {
            // ������������ڵ�û�дﵽ���ĸ߶�
            return (1 << (h - level - 1)) /*�������Ľڵ���*/ + f(cur->left, level + 1, h);/*����ڵ㿪ʼ�ݹ�*/
        }
    }
    // ���ش� cur �ڵ㿪ʼ���������ܵ����������
    int mostLeft(TreeNode* cur, int level) {
        while (cur != nullptr) {
            level++;
            cur = cur->left;
        }
        return level - 1;//curΪ��ʱ����һ��
    }
};

//ʮ����ͨ��������Ѱ�������ڵ�������������(lca����) https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
//�����и��� T �������ڵ� p��q������������ȱ�ʾΪһ���ڵ� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ���
//�Զ�������������������p��q�����ϻ���
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            // �����ǰ�ڵ�Ϊ�գ������� p �� q��ֱ�ӷ��ص�ǰ�ڵ�
            return root;
        }
        // �ݹ�������������������
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr) {
            // ��������������ҵ��ڵ� p �� q����ǰ�ڵ�������ǵ������������
            return root;
        }
        if (left == nullptr && right == nullptr) {
            // �������������δ�ҵ��ڵ� p �� q���򷵻ؿ�
            return nullptr;
        }
        // ������������������ҵ��ڵ� p �� q�������ҵ����Ǹ��ڵ�
        return left != nullptr ? left : right;
    }
};
//ʮһ��������������Ѱ�������ڵ������������� https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
/*�����������Ķ��壺
��������������Ϊ�գ������������нڵ��ֵ��С�����ĸ��ڵ㡣
��������������Ϊ�գ������������еĽڵ��ֵ���������ĸ��ڵ㡣
������������Ҳ���Ƕ�����������*/
//���ýڵ�֮��Ĵ�С��ϵ��
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // root���ϵ���
    // �����������p��˵��p�Ǵ�
    // �����������q��˵��q�Ǵ�
    // ���root��p~q��ֵ֮�䣬���ù�p��q˭��˭С��ֻҪroot���м䣬��ô��ʱ��root���Ǵ�
    // ���root��p~q��ֵ����࣬��ôroot�����ƶ�
    // ���root��p~q��ֵ���Ҳ࣬��ôroot�����ƶ�
    while (root->val != p->val && root->val != q->val) {
        if (min(p->val, q->val) < root->val && root->val < max(p->val, q->val)) {
            break;
        }
        root = root->val < min(p->val, q->val) ? root->right : root->left;
    }
    return root;
}

//ʮ�����ռ��ۼӺ͵���aim������·�� https://leetcode.cn/problems/path-sum-ii/
//�ݹ�+����
class Solution {
private:
    vector<vector<int>> ans;
    void f(TreeNode* root, int target, int sum, vector<int>& list) {
        if (root == nullptr) return;
        sum += root->val;
        list.push_back(root->val);
        // ���ﵽҶ�ӽڵ���·���͵���Ŀ��ֵʱ����·���������
        if (sum == target && !root->left && !root->right) {
            ans.push_back(list);
        }
        // �ݹ�������������������
        if (root->left) {
            f(root->left, target, sum, list);
        }
        if (root->right) {
            f(root->right, target, sum, list);
        }
        // ���ݣ�������ǰ�ڵ��ѡ��
        list.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> list;
        f(root, targetSum, 0, list);
        return ans;
    }
};

//ʮ������֤ƽ������� https://leetcode.cn/problems/balanced-binary-tree/
//ƽ�������:�������нڵ��������������������� 1��
class Solution {
private:
    bool ans = true;
    int f(TreeNode* root) {
        if (!root) return 0;
        int leftHeight = f(root->left);
        int rightHeight = f(root->right);
        // �жϵ�ǰ�ڵ�����������߶Ȳ��Ƿ񳬹�1
        if (abs(leftHeight - rightHeight) > 1) {
            ans = false;
        }
        // ���ص�ǰ�ڵ�ĸ߶�
        return max(leftHeight, rightHeight) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        f(root);
        return ans;
    }
};

//ʮ�ġ���֤���������� https://leetcode.cn/problems/validate-binary-search-tree/
//1.�����������������������ڵ����Ϊ����������
class Solution {
private:
    vector<int> ans;
    void mid(TreeNode* root) {
        if (root->left) { mid(root->left); }
        ans.push_back(root->val);
        if (root->right) { mid(root->right); }
    }
    bool check() {
        bool C = true;
        for (int i = 0; i < ans.size() - 1; i++) {
            if (ans[i] >= ans[i + 1]) {
                C = false;
            }
        }
        return C;
    }
public:
    bool isValidBST(TreeNode* root) {
        mid(root);
        return check();
    }
};
//2.ȫ�ֱ������ݹ� ʹ��long����int�߽��ж��쳣
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long minVal = LONG_MAX;
        long maxVal = LONG_MIN;
        return isValidBSTHelper(root, minVal, maxVal);
    }
private:
    bool isValidBSTHelper(TreeNode* head, long& minVal, long& maxVal) {
        if (head == nullptr) {
            minVal = LONG_MAX;
            maxVal = LONG_MIN;
            return true;
        }
        long leftMin, leftMax, rightMin, rightMax;
        bool leftValid = isValidBSTHelper(head->left, leftMin, leftMax);
        bool rightValid = isValidBSTHelper(head->right, rightMin, rightMax);
        minVal = min({ leftMin, rightMin, (long)head->val });
        maxVal = max({ leftMax, rightMax, (long)head->val });
        return leftValid && rightValid && (head->left == nullptr || leftMax < head->val) 
            && (head->right == nullptr || head->val < rightMin);
    }
};

//ʮ�塢�޼� ���� ������ https://leetcode.cn/problems/trim-a-binary-search-tree/
//�������������������ʵݹ�
class Solution {
public:
    TreeNode* trimBST(TreeNode* cur, int low, int high) {
        if (cur == nullptr) {
            return nullptr;
        }
        if (cur->val < low) {//�ýڵ�����ֱ�Ӳ��ÿ���
            return trimBST(cur->right, low, high);
        }
        if (cur->val > high) {//�ýڵ���Ҳ�ֱ�Ӳ��ÿ���
            return trimBST(cur->left, low, high);
        }
        // cur�ڷ�Χ��
        cur->left = trimBST(cur->left, low, high);
        cur->right = trimBST(cur->right, low, high);
        return cur;
    }
};

//ʮ������������ҽ������� https://leetcode.cn/problems/house-robber-iii/
//����ĳ�������Ľڵ���˵���ܹ�����ͷ�Ϊ���֣�͵�ýڵ�Yes ����͵�ýڵ�No
//���ĳ���ڵ㱻͵�����¸��ڵ����No������˽ڵ�û��͵��������Ľڵ������YesҲ������No
//���ô���ɵݹ�
class Solution {
public:
    int rob(TreeNode* root) {
        auto result = f(root);
        return max(result.first, result.second);
    }
private:
    // f ��������һ��ֵ����һ��ֵ��͵�Ե�ǰ�ڵ��������棬�ڶ���ֵ�ǲ�͵�Ե�ǰ�ڵ���������
    pair<int, int> f(TreeNode* root) {
        if (root == nullptr) {
            return { 0, 0 }; // {yes, no}
        }
        auto left = f(root->left);
        auto right = f(root->right);
        // ��ǰ�ڵ�͵�Ե�����
        int yes = root->val + left.second + right.second;
        // ��ǰ�ڵ㲻͵�Ե�����
        int no = max(left.first, left.second) + max(right.first, right.second);
        return { yes, no };
    }
};

//��Yes��No��Ϊȫ�ֱ�������
class Solution {
public:
    int rob(TreeNode* root) {
        f(root);
        return max(yes, no);
    }
    int yes;
    int no;
    void f(TreeNode* root) {
        if (!root) {
            yes = 0;
            no = 0;
        }else {
            int y = root->val;
            int n = 0;
            f(root->left);
            y += no;
            n += max(yes, no);
            f(root->right);
            y += no;
            n += max(yes, no);
            yes = y;
            no = n;
        }
    }
};