//一、航班预订统计 https://leetcode.cn/problems/corporate-flight-bookings/
// 有一份航班预订表 bookings ，这里有 n 个航班，它们分别从 1 到 n 进行编号。
// 表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi]
// 意味着在从 firsti 到 lasti 
//（包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
// 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n, 0);
        for (int i = 0; i < bookings.size(); i++) {
            ans[bookings[i][0] - 1] += bookings[i][2];
            if (bookings[i][1] - 1 != n - 1) {
                ans[bookings[i][1]] -= bookings[i][2];
            }
        }
        for (int i = 1; i < n; i++) {
            ans[i] += ans[i - 1];
        }
        return ans;
    }
};

//等差数列差分：进行两边前缀和
/*每个操作调用set方法
所有操作完成后在arr上生成两遍前缀和，即调用build方法
arr里就是最终1~n范围上的每个数字 
void set(int l, int r, int s, int e, int d) {
    arr[l] += s;
    arr[l + 1] += d - s;
    arr[r + 1] -= d + e;
    arr[r + 2] += e;
}
void build() {
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }
}
*/
//二、P4231 三步必杀 https://www.luogu.com.cn/problem/P4231
// 一开始1~n范围上的数字都是0，一共有m个操作，每次操作为(l,r,s,e,d)
// 表示在l~r范围上依次加上首项为s、末项为e、公差为d的数列
// m个操作做完之后，统计1~n范围上所有数字的最大值和异或和
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXN = 10000005;
long long arr[MAXN];
int n, m;
void set(int l, int r, int s, int e, int d) {
    arr[l] += s;
    arr[l + 1] += d - s;
    arr[r + 1] -= d + e;
    arr[r + 2] += e;
}
void build() {
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0, l, r, s, e; i < m; i++) {
        cin >> l >> r >> s >> e;
        set(l, r, s, e, (e - s) / (r - l));
    }
    build();
    long long max_val = 0, xor_val = 0;
    for (int i = 1; i <= n; i++) {
        max_val = max(max_val, arr[i]);
        xor_val ^= arr[i];
    }
    cout << xor_val << " " << max_val << endl;
    return 0;
}

//三、一群人落水后求每个位置的水位高度 https://www.luogu.com.cn/problem/P5026
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int MAXN = 1000001;//题目保证 1 <= m <= 1000000
const int OFFSET = 30001;//题目保证 1 <= v <= 10000
// 定义数组大小为 OFFSET + MAXN + OFFSET
int arr[OFFSET + MAXN + OFFSET];
int n, m;
void set(int l, int r, int s, int e, int d) {
    // 为了防止出现负数下标，所有位置加上 OFFSET
    // 为了防止x - 3 * v + 1出现负数下标，进而有很多很烦的边界讨论
    // 所以任何位置，都加上一个较大的数字(OFFSET)
    // 这样一来，所有下标就都在0以上了，省去了大量边界讨论
    // 这就是为什么arr在初始化的时候要准备OFFSET + MAXN + OFFSET这么多的空间
    arr[l + OFFSET] += s;
    arr[l + 1 + OFFSET] += d - s;
    arr[r + 1 + OFFSET] -= d + e;
    arr[r + 2 + OFFSET] += e;
}
void fall(int v, int x) {
    set(x - 3 * v + 1, x - 2 * v, 1, v, 1);
    set(x - 2 * v + 1, x, v - 1, -v, -1);
    set(x + 1, x + 2 * v, -v + 1, v, 1);
    set(x + 2 * v + 1, x + 3 * v - 1, v - 1, 1, -1);
}
void build() {
    for (int i = 1; i <= m + OFFSET; i++) {
        arr[i] += arr[i - 1];
    }
    for (int i = 1; i <= m + OFFSET; i++) {
        arr[i] += arr[i - 1];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> m) {
        for (int i = 0, v, x; i < n; i++) {
            cin >> v >> x;
            fall(v, x);
        }
        build();
        int start = OFFSET + 1;
        //保证输出格式正确
        cout << arr[start++];
        for (int i = 2; i <= m; i++) {
            cout << " " << arr[start++];
        }
        cout << endl;
    }
    return 0;
}
