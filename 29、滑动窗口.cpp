/*滑动窗口：维持左、右边界都不回退的一段范围，来求解很多子数组（串）的相关问题滑动窗口的关键：找到 范围 和 答案指标 之间的 单调性关系（类似贪心）滑动过程：滑动窗口可以用 简单变量 或者 结构 来 维护信息求解大流程：求子数组在 每个位置 开头 或 结尾 情况下的答案（开头还是结尾在于个人习惯）*///一、长度最小的子数组 https://leetcode.cn/problems/minimum-size-subarray-sum/// 给定一个含有 n 个正整数的数组和一个正整数 target// 找到累加和 >= target 的长度最小的子数组并返回其长度,如果不存在符合条件的子数组返回0// 此题用前缀和会超时class Solution {public:    int minSubArrayLen(int target, vector<int>& nums) {        int ans = INT_MAX;        int sum = 0;        for (int left = 0, right = 0; right < nums.size(); right++) {            sum += nums[right];            while (sum >= target) {                ans = min(ans, right - left + 1);                sum -= nums[left++];            }        }        return ans == INT_MAX ? 0 : ans;    }};//二、无重复字符的最长子串 https://leetcode.cn/problems/longest-substring-without-repeating-characters/// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。class Solution {public:    int lengthOfLongestSubstring(string s) {        int last[256]; // 每个字符上次出现的位置        fill(last, last + 256, -1); // 初始化为-1        int ans = 0;        for (int l = 0, r = 0; r < s.length(); r++) {            l = max(l, last[s[r]] + 1); // 更新左边界            ans = max(ans, r - l + 1); // 更新最大长度            last[s[r]] = r; // 更新字符的上次出现位置        }        return ans;    }};//三、最小覆盖子串 https://leetcode.cn/problems/minimum-window-substring/// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。