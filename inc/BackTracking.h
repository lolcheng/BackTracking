#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <unordered_set>

// 回溯算法的本质是带有剪枝操作的暴力搜索算法，但其优点是可以解决变化多样而使用嵌套for循环无法解决的问题，且代码基于递归而相当精简
// 回溯算法的基本架构
// 1.函数参数的返回值
// 2.确定终止条件
// 3.单层搜索逻辑
// 任何回溯算法都可以看作是一棵回溯树，树的深度为回溯的终止条件，树的宽度为某一层中的元素个数
// for循环可以理解是横向遍历，backtracking（递归）是纵向遍历
// 回溯算法的优化通常包含剪枝操作
// void backtracking(参数)
// {
//     if (终⽌条件)
//     {
//         存放结果;
//         return;
//     }
//     for (选择：本层集合中元素（树中节点孩⼦的数量就是集合的⼤⼩）)
//     {
//         处理节点;
//         backtracking(路径，选择列表); // 递归
//         回溯，撤销处理结果
//     }
// }

class CombineSolution
{
public:
    // 组合数
    std::vector<std::vector<int>> CombineNum(int n, int k)
    {
        result.clear();
        path.clear();
        BackTrackingForCombineNum(n, k, 1);
        return result;
    }
    // 组合总和
    std::vector<std::vector<int>> CombineNumSum(int n, int k)
    {
        result.clear();
        path.clear();
        BackTrackingForCombineNumSum(n, k, 0, 1);
        return result;
    }
    // 允许结果中有重复元素
    std::vector<std::vector<int>> CombineNumSumWithDuplication(std::vector<int> &candidates, int target)
    {
        result.clear();
        path.clear();
        sort(candidates.begin(), candidates.end()); // 需要排序
        BackTrackingForCombineNumSumWithDuplication(candidates, target, 0, 0);
        return result;
    }
    // 允许集合中有重复元素
    std::vector<std::vector<int>> CombineNumSumWithDuplication2(std::vector<int> &candidates, int target)
    {
        std::vector<bool> used(candidates.size(), false);
        path.clear();
        result.clear();
        // ⾸先把给candidates排序，让其相同的元素都挨在⼀起。
        sort(candidates.begin(), candidates.end());
        BackTrackingForCombineNumSumWithDuplication2(candidates, target, 0, 0, used);
        return result;
    }

private:
    std::vector<std::vector<int>> result;                        // 存放符合条件结果的集合
    std::vector<int> path;                                       // ⽤来存放符合条件结果
    void BackTrackingForCombineNum(int n, int k, int startIndex) // n为总数，k为取数
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) // 剪枝前：n ；剪枝后： n - (k - path.size()) + 1
        {
            path.push_back(i);                      // 处理节点
            BackTrackingForCombineNum(n, k, i + 1); // 递归
            path.pop_back();                        // 回溯，撤销处理的节点
        }
    }
    void BackTrackingForCombineNumSum(int targetSum, int k, int sum, int startIndex)
    {
        if (sum > targetSum) // 剪枝
            return;
        if (path.size() == k)
        {
            if (sum == targetSum)
                result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++)
        {             // 剪枝
            sum += i; // 处理
            path.push_back(i);
            BackTrackingForCombineNumSum(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
            sum -= i;                                               // 回溯
            path.pop_back();
        }
    }
    void BackTrackingForCombineNumSumWithDuplication(std::vector<int> &candidates, int target, int sum, int startIndex)
    {
        if (sum > target)
            return;
        if (sum == target)
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) // sum + candidates[i] <= target剪枝
        {
            sum += candidates[i];
            path.push_back(candidates[i]);
            BackTrackingForCombineNumSumWithDuplication(candidates, target, sum, i); // 不⽤i+1了，表示可以重复读取当前的数
            sum -= candidates[i];
            path.pop_back();
        }
    }
    void BackTrackingForCombineNumSumWithDuplication2(std::vector<int> &candidates, int target, int sum, int startIndex, std::vector<bool> &used)
    {
        if (sum > target)
            return;
        if (sum == target)
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++)
        {
            // 去重
            // used[i - 1] == true，说明同⼀树枝candidates[i - 1]使⽤过
            // used[i - 1] == false，说明同⼀树层candidates[i - 1]使⽤过
            // 要对同⼀树层使⽤过的元素进⾏跳过
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)
                continue;
            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            BackTrackingForCombineNumSumWithDuplication2(candidates, target, sum, i + 1, used);
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }
};

// 关键概念：如何表示切割符切割字符串
class StringDivision
{
public:
    std::vector<std::vector<std::string>> Partition(std::string s)
    {
        result.clear();
        path.clear();
        BackTrackingForPartition(s, 0);
        return result;
    }
    std::vector<std::vector<std::string>> MoslemsPartition(std::string s)
    {
        result.clear();
        path.clear();
        BackTrackingForMoslemsPartition(s, 0);
        return result;
    }
    std::vector<std::vector<std::string>> IpPartition(std::string s)
    {
        result.clear();
        path.clear();
        BackTrackingForIPPartition(s, 0, 0);
        return result;
    }

private:
    void BackTrackingForPartition(const std::string &s, int startIndex)
    {
        // 如果起始位置已经⼤于s的⼤⼩，说明已经找到了⼀组分割⽅案了
        if (startIndex >= s.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++)
        {
            std::string str = s.substr(startIndex, i - startIndex + 1);
            path.push_back(str);
            BackTrackingForPartition(s, i + 1); // 寻找i+1为起始位置的⼦串
            path.pop_back();                    // 回溯过程，弹出本次已经添加的⼦串
        }
    }
    void BackTrackingForMoslemsPartition(const std::string &s, int startIndex)
    {
        // 如果起始位置已经⼤于s的⼤⼩，说明已经找到了⼀组分割⽅案了
        if (startIndex >= s.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++)
        {
            if (isPalindrome(s, startIndex, i))
            { // 是回⽂⼦串
                // 获取[startIndex,i]在s中的⼦串
                std::string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            }
            else
            { // 不是回⽂，就直接剪枝跳过
                continue;
            }
            BackTrackingForMoslemsPartition(s, i + 1); // 寻找i+1为起始位置的⼦串
            path.pop_back();                           // 回溯过程，弹出本次已经添加的⼦串
        }
    }
    void BackTrackingForIPPartition(std::string &s, int startIndex, int pointNum)
    {
        if (pointNum == 3)
        { // 逗点数量为3时，分隔结束
            // 判断第四段⼦字符串是否合法，如果合法就放进result中
            if (isValid(s, startIndex, s.size() - 1))
            {
                std::string str = s.substr(startIndex, s.size() - startIndex + 1);
                path.push_back(str);
                result.push_back(path);
                path.pop_back();
            }
            return;
        }
        for (int i = startIndex; i < s.size(); i++)
        {
            if (isValid(s, startIndex, i)) // 判断 [startIndex,i] 这个区间的⼦串是否合法
            {
                std::string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
                pointNum++;
                BackTrackingForIPPartition(s, i + 1, pointNum);
                path.pop_back();
                pointNum--; // 回溯
            }
            else
                break; // 不合法，直接结束本层循环
        }
    }
    // 判断是否为回文串
    bool isPalindrome(const std::string &s, int start, int end)
    {
        for (int i = start, j = end; i < j; i++, j--)
        {
            if (s[i] != s[j])
            {
                return false;
            }
        }
        return true;
    }
    // 判断字符串s在左闭右闭区间[start, end]所组成的IP是否合法
    bool isValid(const std::string &s, int start, int end)
    {
        if (start > end)
        {
            return false;
        }
        if (s[start] == '0' && start != end)
        { // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++)
        {
            if (s[i] > '9' || s[i] < '0')
            { // 遇到⾮数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255)
            { // 如果⼤于255了不合法
                return false;
            }
        }
        return true;
    }
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> path;
};

// 关键概念：不仅在叶子结点取值而是在每个节点都取值，即之前在终止条件下才获取结果，而此时则是在每层递归中都要获取结果
class SubsetsSolution
{
public:
    std::vector<std::vector<int>> Subsets(std::vector<int> &nums)
    {
        result.clear();
        path.clear();
        BackTrackingForSubsets(nums, 0);
        return result;
    }
    std::vector<std::vector<int>> SubsetsWithDuplication(std::vector<int> &nums)
    {
        result.clear();
        path.clear();
        std::vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end()); // 去重需要排序
        BackTrackingForSubsetsWithDuplication(nums, 0, used);
        return result;
    }
    std::vector<std::vector<int>> IncreasingSubsetsWithDuplication(std::vector<int> &nums)
    {
        result.clear();
        path.clear();
        BackTrackingForIncreasingSubsetsWithDuplication(nums, 0);
        return result;
    }

private:
    // 集合中没有重复元素
    void BackTrackingForSubsets(std::vector<int> &nums, int startIndex)
    {
        result.push_back(path); // 在每一次递归都收集一次⼦集，要放在终⽌添加的上⾯，否则会漏掉⾃⼰
        if (startIndex >= nums.size())
        { // 终⽌条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            BackTrackingForSubsets(nums, i + 1);
            path.pop_back();
        }
    }
    void BackTrackingForSubsetsWithDuplication(std::vector<int> &nums, int startIndex, std::vector<bool> &used)
    {
        result.push_back(path);
        if (startIndex >= nums.size())
        { // 终⽌条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++)
        {
            // used[i - 1] == true，说明同⼀树枝candidates[i - 1]使⽤过
            // used[i - 1] == false，说明同⼀树层candidates[i - 1]使⽤过
            // ⽽我们要对同⼀树层使⽤过的元素进⾏跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
            {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            BackTrackingForSubsetsWithDuplication(nums, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }
    void BackTrackingForIncreasingSubsetsWithDuplication(std::vector<int> &nums, int startIndex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
            // 注意这⾥不要加return，要取树上的节点
        }
        std::unordered_set<int> uset; // 使⽤set对本层元素进⾏去重
        // int used[201] = {0}; 使用哈希表也可以
        for (int i = startIndex; i < nums.size(); i++)
        {
            // 保证递增子序列需要当前元素nums[i]>path.back()最后一个元素
            if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()) // || used[nums[i] + 100] == 1
            {
                continue;
            }
            uset.insert(nums[i]); // 记录这个元素在本层⽤过了，本层后⾯不能再⽤了，used[nums[i] + 100] = 1;
                                  // 为什么这个时候不用回溯？因为uset定义在每一层，而在新的一层都会刷新，故不需要在回到上一层时回溯
            path.push_back(nums[i]);
            BackTrackingForIncreasingSubsetsWithDuplication(nums, i + 1);
            path.pop_back();
        }
    }
    std::vector<std::vector<int>> result;
    std::vector<int> path;
};

class ArraySolution
{
public:
    std::vector<std::vector<int>> ArrayNum(std::vector<int> &nums)
    {
        result.clear();
        path.clear();
        std::vector<bool> used(nums.size(), false);
        BackTrackingForArrayNum(nums, used);
        return result;
    }
    std::vector<std::vector<int>> ArrayNumWithDuplication(std::vector<int> &nums)
    {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end()); // 排序
        std::vector<bool> used(nums.size(), false);
        BackTrackingForArrayNumWithDuplication(nums, used);
        return result;
    }

private:
    void BackTrackingForArrayNum(std::vector<int> &nums, std::vector<bool> &used)
    {
        // 此时说明找到了⼀组
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }
        // 全排列，就无所谓startIndex了
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i] == true)
                continue; // path⾥已经收录的元素，直接跳过
            used[i] = true;
            path.push_back(nums[i]);
            BackTrackingForArrayNum(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    void BackTrackingForArrayNumWithDuplication(std::vector<int> &nums, std::vector<bool> &used)
    {
        // 此时说明找到了⼀组
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            // used[i - 1] == true，说明同⼀树枝nums[i - 1]使⽤过
            // used[i - 1] == false，说明同⼀树层nums[i - 1]使⽤过
            // 如果同⼀树层nums[i - 1]使⽤过则直接跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
            {
                continue;
            }
            if (used[i] == false)
            {
                used[i] = true;
                path.push_back(nums[i]);
                BackTrackingForArrayNumWithDuplication(nums, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }
    std::vector<std::vector<int>> result;
    std::vector<int> path;
};

// for循环表示确定行中的某一列，回溯表示进入下一行
class NQueensSolution
{
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        result.clear();
        std::vector<std::string> chessboard(n, std::string(n, '.'));
        BackTrackingForNQueens(n, 0, chessboard);
        return result;
    }

private:
    std::vector<std::vector<std::string>> result;
    // n 为输⼊的棋盘⼤⼩
    // row 是当前递归到棋盘的第⼏⾏了
    void BackTrackingForNQueens(int n, int row, std::vector<std::string> &chessboard)
    {
        if (row == n)
        {
            result.push_back(chessboard);
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (isValid(row, col, chessboard, n))
            {                               // 验证合法就可以放
                chessboard[row][col] = 'Q'; // 放置皇后
                BackTrackingForNQueens(n, row + 1, chessboard);
                chessboard[row][col] = '.'; // 回溯，撤销皇后
            }
        }
    }
    bool isValid(int row, int col, std::vector<std::string> &chessboard, int n)
    {
        // 不用检查行，因为算法就是沿着行进行的，所以行条件一定满足
        // 检查列
        for (int i = 0; i < row; i++)
        { // 这是⼀个剪枝
            if (chessboard[i][col] == 'Q')
            {
                return false;
            }
        }
        // 检查 45度⻆是否有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (chessboard[i][j] == 'Q')
            {
                return false;
            }
        }
        // 检查 135度⻆是否有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        {
            if (chessboard[i][j] == 'Q')
            {
                return false;
            }
        }
        return true;
    }
};

// 两层for循环+一层回溯
class SudokuSolution
{
public:
    void solveSudoku(std::vector<std::vector<char>> &board)
    {
        BackTrackingForSudoku(board);
    }

private:
    // 这里使用bool而非void是因为并不遍历完成所有可能而只找出一种可能就返回
    bool BackTrackingForSudoku(std::vector<std::vector<char>> &board)
    {
        for (int i = 0; i <= 8; i++)
        {
            for (int j = 0; j <= 8; j++)
            {
                if (board[i][j] != '.')
                    continue; //.表示空
                for (char k = '1'; k <= '9'; k++)
                {
                    if (isValid(i, j, k, board))
                    {
                        board[i][j] = k;
                        if (BackTrackingForSudoku(board))
                            return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    bool isValid(int row, int col, char val, std::vector<std::vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        { // 判断⾏⾥是否重复
            if (board[row][i] == val)
            {
                return false;
            }
        }
        for (int j = 0; j < 9; j++)
        { // 判断列⾥是否重复
            if (board[j][col] == val)
            {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++)
        { // 判断9⽅格⾥是否重复
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (board[i][j] == val)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

static const std::string letterMap[10] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz", // 9
};

class TelephoneNumberSolution
{
public:
    std::vector<std::string> result;
    std::string s;
    void backtracking(std::string &digits, int index)
    {
        if (index == digits.size())
        {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';        // 将index指向的数字转为int
        std::string letters = letterMap[digit]; // 取数字对应的字符集
        for (int i = 0; i < letters.size(); i++)
        {
            s.push_back(letters[i]);         // 处理
            backtracking(digits, index + 1); // 递归，注意index+1，⼀下层要处理下⼀个数字了
            s.erase(s.length() - 1, 1);
        }
    }
    std::vector<std::string> LetterCombinations(std::string digits)
    {
        s.clear();
        result.clear();
        if (digits.size() == 0)
            return result;
        backtracking(digits, 0);
        return result;
    }
};

#define RedRegion 1
#define PurpleRegion -1
class SqStack // 顺序栈，先进先出
{
public:
    SqStack()
    {
        this->data = new int[12]; // 为data申请容量为MaxSize的空间
        this->top = -1;           // 初始化栈顶指针
    }
    ~SqStack() { delete[] data; }      // 释放data所在的空间
    bool Empty() { return top == -1; } // 栈空判断
    bool Full() { return top == 11; }  // 栈满判断
    bool Push(int e)
    {
        if (this->Full())
            return false;
        top++;
        data[top] = e;
        return true;
    }
    bool Pop(int &e)
    {
        if (this->Empty())
            return false;
        e = data[top];
        top--;
        return true;
    }
    bool JustPop()
    {
        if (this->Empty())
            return false;
        top--;
        return true;
    }
    int GetTopElement()
    {
        if (this->Empty())
            return 11;
        int e = data[top];
        return e;
    }
    int GetTop()
    {
        return this->top;
    }
    void ChangeTop(int t)
    {
        this->top = t;
    }
    bool Traversal(int target)
    {
        int temptop = this->top;
        while (temptop != -1)
        {
            if (target == data[temptop])
                return true;
            temptop--;
        }
        return false;
    }

private:
    int *data; // 栈元素数组
    int top;   // 栈顶指针，栈空时指向-1，其他时候指向栈顶（序号从零开始）
};

class GetBall
{
public:
    GetBall() : MinDistance(32767), TryTime(0), MaxDistance(0)
    {
    }

    // private:
    int RedRegionList[6], PurpleRegionList[6];
    int AvailableRedRegionList[6], AvailablePurpleRegionList[6];

    void GetAvailableRegion(int *state)
    {
        int j = 0, k = 0;
        for (int i = 0; i <= 11; i++)
        {
            if (state[i] == RedRegion)
            {
                RedRegionList[j] = i;
                j++;
            }
            if (state[i] == PurpleRegion)
            {
                PurpleRegionList[k] = i;
                k++;
            }
        }
    }

    int GetDistance(int Location1, int Location2)
    {
        int row1, row2, col1, col2, Distance;
        row1 = Location1 / 6;
        col1 = Location1 % 6;
        row2 = Location2 / 6;
        col2 = Location2 % 6;
        if (row1 == 0 && row2 == 0)
        {
            int i = 0;
            if (col1 < col2)
            {
                for (i = 6 + col1; i <= 6 + col2; i++)
                {
                    if (!path.Traversal(i))
                    {
                        Distance = 255;
                        break;
                    }
                }
                if (i == 7 + col2)
                    Distance = abs(col1 - col2);
            }
            else
            {
                for (i = 6 + col2; i <= 6 + col1; i++)
                {
                    if (!path.Traversal(i))
                    {
                        Distance = 255;
                        break;
                    }
                }
                if (i == 7 + col1)
                    Distance = abs(col2 - col1);
            }
        }
        else if (row1 == 0 && row2 == 1)
        {
            if (path.Traversal(6 + col1))
                Distance = abs(col1 - col2) + 1;
            else
                Distance = 255;
        }
        else if (row1 == 1 && row2 == 0)
        {
            if (path.Traversal(6 + col2))
                Distance = abs(col1 - col2) + 1;
            else
                Distance = 255;
        }
        else if (row1 == 1 && row2 == 1)
        {
            Distance = abs(col1 - col2);
        }

        if (Distance > this->MaxDistance)
        {
            this->MaxDistance = Distance;
            this->MaxLocation1 = Location1;
            this->MaxLocation2 = Location2;
        }
        return Distance;
    }

    void BackTracking(int SumDistance, int player)
    {
        if (SumDistance > MinDistance) // 剪枝
            return;
        if (path.GetTop() == 11)
        {
            if (SumDistance < MinDistance)
            {
                MinDistance = SumDistance;
                for (int i = 11; i >= 0; i--)
                {
                    path.Pop(DistanceDirectory[i]);
                }
                path.ChangeTop(11);
            }
            return;
        }
        if (player == RedRegion)
        {
            for (int i = 0; i <= 5; i++)
            {
                if (AvailableRedRegionList[i] == true)
                    continue;
                AvailableRedRegionList[i] = true;
                SumDistance += GetDistance(path.GetTopElement(), RedRegionList[i]);
                path.Push(RedRegionList[i]);
                BackTracking(SumDistance, -player);
                AvailableRedRegionList[i] = false;
                path.JustPop();
                SumDistance -= GetDistance(path.GetTopElement(), RedRegionList[i]);
            }
        }
        else if (player == PurpleRegion)
        {
            for (int i = 0; i <= 5; i++)
            {
                if (AvailablePurpleRegionList[i] == true)
                    continue;
                AvailablePurpleRegionList[i] = true;
                SumDistance += GetDistance(path.GetTopElement(), PurpleRegionList[i]);
                path.Push(PurpleRegionList[i]);
                BackTracking(SumDistance, -player);
                AvailablePurpleRegionList[i] = false;
                path.JustPop();
                SumDistance -= GetDistance(path.GetTopElement(), PurpleRegionList[i]);
            }
        }
    }

    int GetMinDistance()
    {
        return this->MinDistance;
    }

    void PrintDistanceDirectory()
    {
        for (int i = 0; i <= 11; i++)
            std::cout << DistanceDirectory[i] << ",";
    }

    void PrintAvailableRegion()
    {
        for (int i = 0; i <= 5; i++)
        {
            std::cout << RedRegionList[i] << ",";
        }
        std::cout << std::endl;
        for (int i = 0; i <= 5; i++)
        {
            std::cout << PurpleRegionList[i] << ",";
        }
        std::cout << std::endl;
    }

    void GetMaxDistance()
    {
        std::cout << this->MaxDistance << "," << this->MaxLocation1 << "," << this->MaxLocation2 << std::endl;
    }

    long int GetTryTime()
    {
        return TryTime;
    }
    SqStack path; // ⽤来存放符合条件结果
    int MinDistance;
    int DistanceDirectory[12];
    long int TryTime;
    int MaxDistance, MaxLocation1, MaxLocation2;
};