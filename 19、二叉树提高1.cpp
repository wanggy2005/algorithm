//BFS——广度优先算法（Breadth First Search）
//一、二叉树的层序遍历（即逐层地，从左到右访问所有节点）https://leetcode.cn/problems/binary-tree-level-order-traversal/
//1.利用hashmap储存层信息+队列
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root != nullptr) {    
        queue<TreeNode*> q;// 使用队列来进行广度优先搜索
        unordered_map<TreeNode*, int> levels;// 用于存储每个节点的层数
        // 将根节点加入队列，并记录其层数为0
        q.push(root);
        levels[root] = 0;
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();// 从队列中取出当前节点
            int level = levels[cur];// 获取当前节点的层数
            // 如果当前层还不存在，则添加一个新的空层
            if (ans.size() == level) {
                ans.push_back(vector<int>());
            }
            ans[level].push_back(cur->val);// 将当前节点的值加入当前层
            if (cur->left != nullptr) {// 如果左子节点存在，将其加入队列并记录其层数
                q.push(cur->left);
                levels[cur->left] = level + 1;
            }
            if (cur->right != nullptr) {// 如果右子节点存在，将其加入队列并记录其层数
                q.push(cur->right);
                levels[cur->right] = level + 1;
            }
        }
    }
    return ans;
}
//2.进阶版：用数组代替队列，用size次数限制循环
const int MAXN = 2001; 
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;  // 存储每层的节点值
    if (root != nullptr) {
        int l = 0, r = 0;  // 队列的左右指针
        TreeNode* queue[MAXN];// 使用数组定义队列
        queue[r++] = root;  // 将根节点加入队列，并更新右指针
        while (l < r) {
            int size = r - l;  // 当前层的节点数
            vector<int> list;  // 存储当前层的节点值
            // 遍历当前层的所有节点
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = queue[l++];  // 从队列中取出当前节点，并更新左指针
                list.push_back(cur->val);  // 将当前节点的值添加到当前层的结果中
                if (cur->left != nullptr) {// 如果左子节点存在，将其加入队列，并更新右指针
                    queue[r++] = cur->left;
                }
                if (cur->right != nullptr) {// 如果右子节点存在，将其加入队列，并更新右指针
                    queue[r++] = cur->right;
                }
            }
            ans.push_back(list);// 将当前层的结果添加到最终结果中
        }
    }
    return ans;
}
//二、二叉树的锯齿形层序遍历 https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
//即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行
const int MAXN = 2001;
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans; 
    if (root != nullptr) {
        int l = 0, r = 0; 
        TreeNode* queue[MAXN];
        queue[r++] = root;  
        bool reverse = false;  // 标记是否需要反向遍历
        while (l < r) {
            int size = r - l;
            vector<int> list;
            // 遍历当前层的所有节点，根据 `reverse` 标记决定遍历方向
            for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k = 0; 
                k < size;
                i += j, ++k) {
                TreeNode* cur = queue[i];  // 取出当前节点
                list.push_back(cur->val);  // 将节点值添加到当前层的结果中
            }
            //下面正常收集子节点
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
            reverse = !reverse;// 切换遍历方向
        }
    }
    return ans; 
}
//三、二叉树的最大特殊宽度 https://leetcode.cn/problems/maximum-width-of-binary-tree/
/*给你一棵二叉树的根节点root，返回树的最大宽度。
树的最大宽度是所有层中最大的宽度 。每一层的宽度被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。
将这个二叉树视作与满二叉树结构相同，两端点间会出现一些延伸到这一层的null节点，这些null节点也计入长度。*/
//堆的节点编号+宽度优先遍历
#define MAXN 3001
class Solution {
public:
    TreeNode* nodeQueue[MAXN]; // 用于存储树节点的队列
    unsigned long long indexQueue[MAXN]; // 用于存储树节点的索引的队列
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        unsigned long long ans = 1; // 初始化最大宽度为1
        int l = 0, r = 0;
        //保证两个队列的下标始终保持同步
        nodeQueue[r] = root; // 根节点入队
        indexQueue[r++] = 1; // 根节点的索引为1
        while (l < r) {
            int size = r - l;
            ans = max(ans, indexQueue[r - 1] - indexQueue[l] + 1); // 更新最大宽度
            for (int i = 0; i < size; i++) {
                TreeNode* node = nodeQueue[l]; // 当前节点
                unsigned long long id = indexQueue[l++]; // 当前节点的索引
                if (node->left) { // 如果左子节点存在
                    nodeQueue[r] = node->left; // 左子节点入队
                    indexQueue[r++] = id * 2; // 左子节点的索引
                }
                if (node->right) { // 如果右子节点存在
                    nodeQueue[r] = node->right; // 右子节点入队
                    indexQueue[r++] = id * 2 + 1; // 右子节点的索引
                }
            }
        }
        return ans; // 返回最大宽度
    }
};


//DFS——深度优先算法（Depth First Search）
//四、求二叉树的（1）最大深度 https://leetcode.cn/problems/maximum-depth-of-binary-tree/
//二叉树的最大深度是指从根节点到最远叶子节点的最长路径上的节点数。
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
//（2）最小深度 https://leetcode.cn/problems/minimum-depth-of-binary-tree/
//最小深度是从根节点到最近叶节点的最短路径上的节点数量。
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {//当前的树为空树
            return 0;
        }
        if (root->left == nullptr && root->right == nullptr) {//当前节点为叶节点
            return 1;
        }
        int min_depth = INT_MAX;//设为极值，在不影响比较的前提下保证下面比较形式的一致性
        if (root->left != nullptr) {
            min_depth = min(minDepth(root->left), min_depth);
        }
        if (root->right != nullptr) {
            min_depth = min(minDepth(root->right), min_depth);
        }
        return min_depth + 1;
    }
};
//使用广度优先搜索的方法，遍历整棵树。
//当我们找到一个叶子节点时，直接返回这个叶子节点的深度。广度优先搜索的性质保证了最先搜索到的叶子节点的深度一定最小。
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        queue<pair<TreeNode*, int> > que;
        que.emplace(root, 1);
/*empalce的特性：
当调用push或insert成员函数时，我们将元素类型的对象传递给它们，这些对象被拷贝到容器中。
而当我们调用一个emplace成员函数时，则是将参数传递给元素类型的构造函数。
emplace成员使用这些参数在容器管理的内存空间中直接构造元素。*/
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


//五、二叉树先序序列化和反序列化 https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
/*序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
  同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
  中序遍历不能进行序列化与反序列化，先序和后序遍历可以*/
/*https://blog.csdn.net/weixin_45031801/article/details/136921743
* 
补充：stringstream 定义于头文件 <sstream>,是C++提供的专门用于处理字符串的 输入输出 流类
<sstream>定义了三个类：istringstream、ostringstream和stringstream，分别用来进行流的输入、输出和输入输出操作。
1.构造
string s("hello stringstream");
stringstream ss;
ss << s;
cout << ss.str() << endl;
或者是
stringstream ss("hello stringstream");
cout << ss.str() << endl;、
2. stringstream  可以将存储于内部的字符串输出，需要调用 str() 函数，不可直接输出：
cout << ss.str() << endl;
3.利用 stringstream 去除字符串空格
stringstream 默认是以空格来分割字符串的，利用 stringstream 去除字符串空格非常方便：
int main(){
    stringstream ss("hello string and stringstream");
    string str;
    // 注意： stringstream 是一个单词一个单词 ”流入“ string 的
    while (ss >> str){
        cout << str << endl;
    }
    return 0;
}
输出：
    hello
    string
    and
    stringstream
4.类型转换
使用 stringstream 进行类型转换
以下是一个使用 stringstream 将数字转换为字符串的例子：
#include <sstream>
#include <iostream>
#include <string>
int main() {
    int num = 123;
    sstringstream ss;
    ss << num; // 将整数放入流中
    string str = ss.str(); // 使用str()函数 从流中提取字符串
    cout << str << endl; // 输出：123
}
反过来，也可以将字符串转换为数值类型：
int main() {
    string str = "456abc";
    stringstream ss(str); // 初始化stringstream
    int num;
    ss >> num; // 从流中提取整数
    cout << num << endl; // 输出：456
}

getline 是 C++ 标准库中一个用于从输入流（如文件、字符串流、标准输入等）中读取一行字符的函数
读取整行：getline 函数会从输入流中读取一行内容，直到遇到换行符（\n），但它不会将换行符包含在结果字符串中。
分隔符：getline 还可以接受第三个参数，指定行结束的分隔符。如果没有指定，默认为换行符。例如getline(cin, line, ',');这将会读取直到遇到逗号为止的内容。
返回值：getline 函数返回一个 istream& ，如果成功读取行，则返回流本身。如果遇到错误或 EOF（文件结束），则返回一个错误状态*/
class Codec {
private:
    void serializeHelper(TreeNode* root, stringstream& ss) {// 递归地将二叉树序列化为字符串
        if (root == nullptr) {
            ss << "#,";  // 如果节点为空，用 "#" 表示，并加上逗号作为分隔符
        }else {
            ss << root->val << ",";  // 将节点的值存入字符串流，并加上逗号
            serializeHelper(root->left, ss);  // 递归处理左子树
            serializeHelper(root->right, ss);  // 递归处理右子树
        }
    }
    TreeNode* deserializeHelper(const vector<string>& vals) {//递归地将字符串反序列化为二叉树
        if (index >= vals.size()) return nullptr;  // 防止数组越界
        string cur = vals[index++];  // 获取当前值并将索引后移
        if (cur == "#") {  // 如果当前值是 "#", 表示这是一个空节点
            return nullptr;
        }else {
            // 否则创建一个新的节点，并递归构建左、右子树
            TreeNode* node = new TreeNode(stoi(cur)); //stoi 是 C++11 标准中引入的一个函数，用于将字符串转换为整数（int）类型
            node->left = deserializeHelper(vals);  // 递归构建左子树
            node->right = deserializeHelper(vals);  // 递归构建右子树
            return node;
        }
    }
    int index = 0;  // 索引，用于追踪当前处理到的节点位置
public:
    string serialize(TreeNode* root) {// 将二叉树序列化为字符串
        stringstream ss;
        serializeHelper(root, ss);  
        return ss.str();  // 返回序列化后的字符串
    }
    TreeNode* deserialize(string data) {// 将字符串反序列化为二叉树
        vector<string> vals;
        stringstream ss(data);  // 将字符串转换为字符串流以便逐个解析
        string item;
        // 使用逗号分割字符串并存储到 vector 中
        while (getline(ss, item, ',')) {
            vals.push_back(item);
        }
        index = 0;  // 初始化索引
        return deserializeHelper(vals);  // 调用辅助函数进行递归反序列化
    }
};
//六、二叉树按层序列化和反序列化 https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
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
        int index = 0;//标志下一层新建的开始
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

//七、利用先序与中序遍历序列构造二叉树 https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
//给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
//利用先序遍历头一定在最前来划分左右树的范围
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
        // (...)是左树对应，[...]是右树的对应
        head->left = f(pre, l1 + 1, l1 + k - l2, in, l2, k - 1, map);
        head->right = f(pre, l1 + k - l2 + 1, r1, in, k + 1, r2, map);
        return head;
    }
};

//八、验证完全二叉树 https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
//在一棵 完全二叉树 中，除了最后一层外，所有层都被完全填满，并且最后一层中的所有节点都尽可能靠左。最后一层（第 h 层）中可以包含 1 到 2h 个节点。
const int MAXN = 101;  // 最大节点数量
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
        bool leaf = false;  // 是否遇到过非完全节点
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
                leaf = true;  // 标记为叶节点（或不完全节点）
            }
        }
        return true;
    }
};

//九、求完全二叉树的节点个数(要求时间复杂度低于O(n)) https://leetcode.cn/problems/count-complete-tree-nodes/
class Solution {
public:
    int countNodes(TreeNode* head) {
        if (head == nullptr) {
            return 0;
        }
        return f(head, 1, mostLeft(head, 1));
    }
private:
    // 计算以 cur 为根的子树的节点数
    int f(TreeNode* cur, int level, int h) {
        if (level == h) {
            return 1;
        }
        if (mostLeft(cur->right, level + 1) == h) {
            // 右子树的最左节点达到树的高度
            return (1 << (h - level)) /*左子树的节点数*/ + f(cur->right, level + 1, h);/*从右节点开始递归*/
        }else {
            // 右子树的最左节点没有达到树的高度
            return (1 << (h - level - 1)) /*右子树的节点数*/ + f(cur->left, level + 1, h);/*从左节点开始递归*/
        }
    }
    // 返回从 cur 节点开始，向左走能到达的最大层数
    int mostLeft(TreeNode* cur, int level) {
        while (cur != nullptr) {
            level++;
            cur = cur->left;
        }
        return level - 1;//cur为空时多算一次
    }
};

//十、普通二叉树上寻找两个节点的最近公共祖先(lca问题) https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
//对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。
//自顶部向下搜索，搜索到p、q再向上回溯
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            // 如果当前节点为空，或者是 p 或 q，直接返回当前节点
            return root;
        }
        // 递归搜索左子树和右子树
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr) {
            // 如果左右子树都找到节点 p 或 q，则当前节点就是它们的最近公共祖先
            return root;
        }
        if (left == nullptr && right == nullptr) {
            // 如果左右子树都未找到节点 p 或 q，则返回空
            return nullptr;
        }
        // 如果左子树或右子树找到节点 p 或 q，返回找到的那个节点
        return left != nullptr ? left : right;
    }
};
//十一、搜索二叉树上寻找两个节点的最近公共祖先 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
/*搜索二叉树的定义：
若它的左子树不为空，左子树上所有节点的值都小于它的根节点。
若它的右子树不为空，右子树上所有的节点的值都大于它的根节点。
它的左、右子树也都是二分搜索树。*/
//利用节点之间的大小关系：
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // root从上到下
    // 如果先遇到了p，说明p是答案
    // 如果先遇到了q，说明q是答案
    // 如果root在p~q的值之间，不用管p和q谁大谁小，只要root在中间，那么此时的root就是答案
    // 如果root在p~q的值的左侧，那么root往右移动
    // 如果root在p~q的值的右侧，那么root往左移动
    while (root->val != p->val && root->val != q->val) {
        if (min(p->val, q->val) < root->val && root->val < max(p->val, q->val)) {
            break;
        }
        root = root->val < min(p->val, q->val) ? root->right : root->left;
    }
    return root;
}

//十二、收集累加和等于aim的所有路径 https://leetcode.cn/problems/path-sum-ii/
//递归+回溯
class Solution {
private:
    vector<vector<int>> ans;
    void f(TreeNode* root, int target, int sum, vector<int>& list) {
        if (root == nullptr) return;
        sum += root->val;
        list.push_back(root->val);
        // 当达到叶子节点且路径和等于目标值时，将路径加入答案中
        if (sum == target && !root->left && !root->right) {
            ans.push_back(list);
        }
        // 递归搜索左子树和右子树
        if (root->left) {
            f(root->left, target, sum, list);
        }
        if (root->right) {
            f(root->right, target, sum, list);
        }
        // 回溯，撤销当前节点的选择
        list.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> list;
        f(root, targetSum, 0, list);
        return ans;
    }
};

//十三、验证平衡二叉树 https://leetcode.cn/problems/balanced-binary-tree/
//平衡二叉树:该树所有节点的左右子树的深度相差不超过 1。
class Solution {
private:
    bool ans = true;
    int f(TreeNode* root) {
        if (!root) return 0;
        int leftHeight = f(root->left);
        int rightHeight = f(root->right);
        // 判断当前节点的左右子树高度差是否超过1
        if (abs(leftHeight - rightHeight) > 1) {
            ans = false;
        }
        // 返回当前节点的高度
        return max(leftHeight, rightHeight) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        f(root);
        return ans;
    }
};

//十四、验证搜索二叉树 https://leetcode.cn/problems/validate-binary-search-tree/
//1.将二叉树按中序遍历，如果节点递增为搜索二叉树
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
//2.全局变量法递归 使用long避免int边界判断异常
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

//十五、修剪 搜索 二叉树 https://leetcode.cn/problems/trim-a-binary-search-tree/
//利用搜索二叉树的性质递归
class Solution {
public:
    TreeNode* trimBST(TreeNode* cur, int low, int high) {
        if (cur == nullptr) {
            return nullptr;
        }
        if (cur->val < low) {//该节点的左侧直接不用看了
            return trimBST(cur->right, low, high);
        }
        if (cur->val > high) {//该节点的右侧直接不用看了
            return trimBST(cur->left, low, high);
        }
        // cur在范围中
        cur->left = trimBST(cur->left, low, high);
        cur->right = trimBST(cur->right, low, high);
        return cur;
    }
};

//十六、二叉树打家劫舍问题 https://leetcode.cn/problems/house-robber-iii/
//对于某个单独的节点来说，总共情况就分为两种：偷该节点Yes 、不偷该节点No
//如果某个节点被偷过，下个节点必是No；如果此节点没被偷过，下面的节点可以是Yes也可以是No
//利用此完成递归
class Solution {
public:
    int rob(TreeNode* root) {
        auto result = f(root);
        return max(result.first, result.second);
    }
private:
    // f 函数返回一对值，第一个值是偷窃当前节点的最大收益，第二个值是不偷窃当前节点的最大收益
    pair<int, int> f(TreeNode* root) {
        if (root == nullptr) {
            return { 0, 0 }; // {yes, no}
        }
        auto left = f(root->left);
        auto right = f(root->right);
        // 当前节点偷窃的收益
        int yes = root->val + left.second + right.second;
        // 当前节点不偷窃的收益
        int no = max(left.first, left.second) + max(right.first, right.second);
        return { yes, no };
    }
};

//将Yes和No作为全局变量处理
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