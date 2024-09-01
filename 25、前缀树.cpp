//前缀树（字典树） trie
/*每个样本 都从头节点开始 根据 前缀字符或者前缀数字 建出来的一棵大树，就是前缀树
没有路就新建节点；已经有路了，就复用节点

前缀树的使用场景：需要根据前缀信息来查询的场景
前缀树的优点：根据前缀信息选择树上的分支，可以节省大量的时间
前缀树的缺点：比较浪费空间，和总字符数量有关，字符的种类有关
前缀树的定制：pass、end等信息	字符放在路上
*/

//一、用类描述实现前缀树 https://leetcode.cn/problems/implement-trie-ii-prefix-tree/
/*实现前缀树 Trie 类：
Trie() 初始化前缀树对象。
void insert(String word) 将字符串 word 插入前缀树中。
int countWordsEqualTo(String word) 返回前缀树中字符串 word 的实例个数。
int countWordsStartingWith(String prefix) 返回前缀树中以 prefix 为前缀的字符串个数。
void erase(String word) 从前缀树中移除字符串 word 。*/
class Trie {
private:
    class TrieNode {
    public:
        int pass;
        int end;
        vector<TrieNode*> nexts;//下级的路
        TrieNode() : pass(0), end(0), nexts(26, nullptr) {}
    };
    TrieNode* root;//前缀树的头结点
    void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (TrieNode* child : node->nexts) {
            deleteTrie(child);
        }
        delete node;
    }
public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        deleteTrie(root);
    } 
    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (int i = 0; i < word.length(); i++) { // 从左往右遍历字符
            int path = word[i] - 'a'; // 由字符，对应成走向哪条路
            if (node->nexts[path] == nullptr) {
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++;
    }
    //如果之前word插入过前缀树，删掉一次
    //如果之前word没有插入过前缀树，不做操作
    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) {
            TrieNode* node = root;
            node->pass--;
            for (int i = 0; i < word.length(); i++) {
                int path = word[i] - 'a';
                if (--node->nexts[path]->pass == 0) {
                    delete node->nexts[path];
                    node->nexts[path] = nullptr;//小心内存泄漏
                    return;
                }
                node = node->nexts[path];
            }
            node->end--;
        }
    }
    //查询前缀树里word出现了几次
    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); i++) {
            int path = word[i] - 'a';
            if (node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->end;
    }
    //查询前缀树里有多少单词以pre做前缀
    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (int i = 0; i < pre.length(); i++) {
            int path = pre[i] - 'a';
            if (node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
};

//用Hashmap储存路的信息
class Trie {
private:
    // TrieNode 类表示前缀树的节点
    class TrieNode {
    public:
        int pass;  // 经过当前节点的单词数量
        int end;   // 以当前节点为结尾的单词数量
        unordered_map<int, TrieNode*> nexts;  // 子节点指针映射，使用哈希映射来处理字符
        TrieNode() : pass(0), end(0) {}
    };
    TrieNode* root;  // 前缀树的根节点
    // 递归删除所有节点，防止内存泄漏
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        for (auto& pair : node->nexts) {
            deleteTrie(pair.second);
        }
        delete node;
    }
public:
    // 构造函数初始化前缀树
    Trie2() {
        root = new TrieNode();
    }
    // 析构函数，递归删除前缀树的所有节点
    ~Trie2() {
        deleteTrie(root);
    }
    // 插入单词到前缀树中
    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (int i = 0; i < word.length(); ++i) {
            int path = word[i];  // 使用字符的ASCII值作为key
            if (node->nexts.find(path) == node->nexts.end()) {
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++;
    }
    // 从前缀树中删除一个单词
    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) {
            TrieNode* node = root;
            TrieNode* next;
            node->pass--;
            for (int i = 0; i < word.length(); ++i) {
                int path = word[i];
                next = node->nexts[path];
                if (--next->pass == 0) {
                    delete node->nexts[path];
                    node->nexts.erase(path);
                    return;
                }
                node = next;
            }
            node->end--;
        }
    }
    // 查询前缀树中某个单词出现的次数
    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); ++i) {
            int path = word[i];
            if (node->nexts.find(path) == node->nexts.end()) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->end;
    }
    // 查询前缀树中以某个前缀开头的单词数量
    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (int i = 0; i < pre.length(); ++i) {
            int path = pre[i];
            if (node->nexts.find(path) == node->nexts.end()) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
};


//二、用静态数组实现（推荐）https://www.nowcoder.com/practice/7f8a8553ddbf4eaab749ec988726702b
//利用cnt所代表的节点编号来代替指针结构
#include<string>
#include<iostream>
#include<cstring>
using namespace std;

const int MAXN = 150001;
// 定义全局变量
int tree[MAXN][26];  // 前缀树，第二个参数为字符的种类数
int endCnt[MAXN];       // 记录以某节点为结束的单词数量
int pass[MAXN];      // 记录经过某节点的单词数量
int cnt;             // 节点计数器 原来树节点的编号
// 初始化前缀树
void build() {
    cnt = 1;  // 根节点从1开始计数
}
// 插入单词到前缀树中
void insert(const string& word) {
    int cur = 1;//从头结点上开始插入
    pass[cur]++;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {//如果word中下一个字符代表的节点为空
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];//找到下一个节点的cnt值
        pass[cur]++;
    }
    endCnt[cur]++;
}
// 搜索单词是否存在于前缀树中
int search(const string& word) {
    int cur = 1;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return endCnt[cur];
}
// 查询前缀树中以某个前缀开头的单词数量
int prefixNumber(const string& pre) {
    int cur = 1;
    for (int i = 0, path; i < pre.length(); i++) {
        path = pre[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}
// 删除单词
void del(const string& word) {
    if (search(word) > 0) {
        int cur = 1;
        for (int i = 0, path; i < word.length(); i++) {
            path = word[i] - 'a';
            if (--pass[tree[cur][path]] == 0) {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
        endCnt[cur]--;
    }
}
// 清除前缀树
void clear() {
    for (int i = 1; i <= cnt; i++) {
        memset(tree[i], 0, sizeof(tree[i]));
        endCnt[i] = 0;
        pass[i] = 0;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, op;
    string word;
    while (cin >> m) {
        build();
        for (int i = 1; i <= m; i++) {
            cin >> op >> word;
            if (op == 1) {
                insert(word);
            }else if (op == 2) {
                del(word);
            }else if (op == 3) {
                cout << (search(word) > 0 ? "YES" : "NO") << endl;
            }else if (op == 4) {
                cout << prefixNumber(word) << endl;
            }
        }
        clear();
    }
    return 0;
}

//前缀树相关题目：
//一、接头密匙 https://www.nowcoder.com/practice/c552d3b4dfda49ccb883a6371d9a6932
// 牛牛和他的朋友们约定了一套接头密匙系统，用于确认彼此身份
// 密匙由一组数字序列表示，如果满足以下条件,两个密匙被认为是一致的:
// 密匙 b 的长度不超过密匙 a 的长度。
// 对于任意 0 <= i < length(b)，有b[i+1] - b[i] == a[i+1] - a[i]
// 现在给定了m个密匙 b 的数组，以及n个密匙 a 的数组。请你返回一个长度为 m 的结果数组 ans，表示每个密匙b都有多少一致的密匙
// 数组 a 和数组 b 中的元素个数均不超过 10^5   1 <= m, n <= 1000
//当path的种类比较多时（比如数字），将其转为字符串来处理单个字符，以减少其数量

// 定义全局变量
const int MAXN = 2000001;
int tree[MAXN][12];  // 前缀树
int pass[MAXN];      // 记录经过某节点的次数
int cnt;             // 节点计数器
// 初始化前缀树
void build() {
    cnt = 1;  // 根节点从1开始计数
}
// 根据字符返回路径值
int getPath(char cha) {
    if (cha == '#') {
        return 10;
    }
    if (cha == '-') {
        return 11;
    }
    return cha - '0';
}
// 插入字符串到前缀树中
void insert(const string& word) {
    int cur = 1;
    pass[cur]++;
    for (int i = 0, path; i < word.length(); i++) {
        path = getPath(word[i]);
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
}
// 统计前缀出现的次数
int count(const string& pre) {
    int cur = 1;
    for (int i = 0, path; i < pre.length(); i++) {
        path = getPath(pre[i]);
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}
// 清除前缀树
void clear() {
    for (int i = 1; i <= cnt; i++) {
        memset(tree[i], 0, sizeof(tree[i]));
        pass[i] = 0;
    }
}
// 统计一致的键数量
vector<int> countConsistentKeys(const vector<vector<int>>& b, const vector<vector<int>>& a) {
    build();
    string builder;
    vector<int> ans(b.size());
    // 插入所有a数组的转换字符串
    for (const auto& nums : a) {
        builder.clear();
        for (int i = 1; i < nums.size(); i++) {
            builder += to_string(nums[i] - nums[i - 1]) + "#";
        }
        insert(builder);
    }
    // 计算每个b数组的转换字符串在前缀树中的出现次数
    for (int i = 0; i < b.size(); i++) {
        builder.clear();
        const auto& nums = b[i];
        for (int j = 1; j < nums.size(); j++) {
            builder += to_string(nums[j] - nums[j - 1]) + "#";
        }
        ans[i] = count(builder);
    }
    clear();
    return ans;
}

//二、数组中两个数的最大异或值 https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
// 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0<=i<=j<=n
// 1 <= nums.length <= 2 * 10^5     0 <= nums[i] <= 2^31 - 1

//前缀树+贪心
const int MAXN = 3000001;
int tree[MAXN][2];  // 前缀树
int cnt;            // 前缀树目前使用了多少空间
int high;           // 数字需要从哪一位开始考虑
void build(const vector<int>& nums) {// 初始化前缀树
    cnt = 1;
    // 找到数组中的最大值
    int maxVal = *max_element(nums.begin(), nums.end());
    // 计算最大值的二进制长度，确定从第几位开始考虑
    high = 31 - __builtin_clz(maxVal);
    //__builtin_clz 是 GCC 和 Clang 提供的一个内建函数，用于计算一个无符号整数的前导零的个数（即在最高有效位之前的零的数量）
    for (int num : nums) {// 将所有数字插入前缀树中
        insert(num);
    }
}
// 插入数字到前缀树中
void insert(int num) {
    int cur = 1;
    for (int i = high; i >= 0; i--) {
        int path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
}
// 计算num在前缀树中能获得的最大异或值
int maxXor(int num) {
    int ans = 0;
    int cur = 1;
    for (int i = high; i >= 0; i--) {
        int status = (num >> i) & 1;
        int want = status ^ 1;
        if (tree[cur][want] == 0) {//贪心所要求的最大值达不到
            want ^= 1;//只能退而求其次
        }
        ans |= (status ^ want) << i;
        cur = tree[cur][want];
    }
    return ans;
}
// 清空前缀树
void clear() {
    for (int i = 1; i <= cnt; i++) {
        tree[i][0] = tree[i][1] = 0;
    }
}
// 计算数组中能获得的最大异或值
int findMaximumXOR(const vector<int>& nums) {
    build(nums);
    int ans = 0;
    for (int num : nums) {
        ans = max(ans, maxXor(num));
    }
    clear();
    return ans;
}


//Hashmap+贪心
int findMaximumXOR(const vector<int>& nums) {
    if (nums.empty()) return 0;  // 如果数组为空，直接返回0
    int max_num = *max_element(nums.begin(), nums.end());// 找到数组中的最大值
    if (max_num == 0) return 0;
    int ans = 0;
    unordered_set<int> set;
    // 计算表示最大值所需的位数
    int high = 31 - __builtin_clz(max_num);

    // 从最高位到最低位遍历
    for (int i = high; i >= 0; --i) {
        int better = ans | (1 << i);//如果当前位是1就好了
        set.clear();

        // 将所有nums中数的前缀添加到集合中，看有没有能够得到better的
        for (int num : nums) {
            int num_prefix = num & (~((1 << i) - 1));//等效于(num>>i)<<i，获取每个数的前缀
            set.insert(num_prefix);
            // 检查是否存在一个前缀能使得异或结果达到目标
            if (set.count(better ^ num_prefix)) {//利用异或运算的性质 x^num_prefix==better，则better^num_prefix==x
                ans = better; 
                break;
            }
        }
    }
    return ans;
}


//三、在二维字符数组中搜索可能的单词 https://leetcode.cn/problems/word-search-ii/
// 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words
// 返回所有二维网格上的单词。单词必须按照字母顺序，通过 相邻的单元格 内的字母构成
// 其中“相邻”单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母在一个单词中不允许被重复使用
// 1 <= m, n <= 12
// 1 <= words.length <= 3 * 10^4
// 1 <= words[i].length <= 10

//DFS+前缀树:
//前缀树的两个妙用：1、利用前缀树本身性质来剪枝  2、利用end直接返回搜索到末尾的字符串    3、利用pass和fix信息再次剪枝，向上返回fix，节点的pass再-fix
class Solution {
public:
    static const int MAXN = 10001;
    int tree[MAXN][26];
    int pass[MAXN];
    string end[MAXN];//end[i] 存储以节点 i 结束的字符串，用于在找到完整的单词时进行收集
    int cnt;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        build(words); // 构建前缀树
        vector<string> ans; 
        for (int i = 0; i < board.size(); i++) { 
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, i, j, 1, ans); 
            }
        }
        clear(); // 清理前缀树
        return ans;
    }
private:
    // 深度优先搜索函数，从网格的 (i, j) 位置开始，沿着前缀树进行搜索
    int dfs(vector<vector<char>>& board, int i, int j, int cur, vector<string>& ans) {
        // 判断是否越界或是否已经访问过此位置（board[i][j] == 0）
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == 0) {
            return 0;
        }
        char tmp = board[i][j];
        int road = tmp - 'a';
        cur = tree[cur][road];// 在前缀树中移动到下一个节点
        if (pass[cur] == 0) {// 如果已经走过相同的路或此路不通
            return 0;
        }
        int fix = 0; // 记录从当前位置开始收集到的单词数量
        if (!end[cur].empty()) {// 如果在当前节点发现了一个完整的单词
            fix++;
            ans.push_back(end[cur]); // 将单词添加到结果列表
            end[cur].clear(); // 清除已找到的单词，防止重复添加
        }
        board[i][j] = 0;// 将当前位置的字符置为 0，防止重复访问
        // 对四个方向进行递归搜索
        fix += dfs(board, i - 1, j, t, ans); // 向上
        fix += dfs(board, i + 1, j, t, ans); // 向下
        fix += dfs(board, i, j - 1, t, ans); // 向左
        fix += dfs(board, i, j + 1, t, ans); // 向右
        pass[cur] -= fix;// 更新经过当前节点的字符串数量
        board[i][j] = tmp;// 恢复当前位置的字符
        return fix;
    }
    // 构建前缀树
    void build(const vector<string>& words) {
        cnt = 1;
        for (const auto& word : words) { 
            int cur = 1; 
            pass[cur]++;
            for (int i = 0, path; i < word.length(); i++) {
                path = word[i] - 'a'; 
                if (tree[cur][path] == 0) { 
                    tree[cur][path] = ++cnt;
                }
                cur = tree[cur][path];
                pass[cur]++;
            }
            end[cur] = word; // 将单词存储在最后一个节点
        }
    }
    // 清理前缀树，重置所有数据
    void clear() {
        for (int i = 1; i <= cnt; i++) {
            memset(tree[i], 0, sizeof(tree[i]));
            pass[i] = 0;
            end[i].clear(); 
        }
    }
};

