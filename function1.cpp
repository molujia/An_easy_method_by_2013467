#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

int globalnum = 0;//记录搜索次数
//宫格大小
int n = 3;
bool judge[864197532];
void show(int* a)
{
    for (int i = 0; i < 9; i++)
    {
        cout << a[i] << " ";
        if ((i + 1) % 3 == 0)cout << "\n";
    }
    cout << "\n";
}

int getnum(int* a)
{
    globalnum += 1;
    int num = 0;
    for (int i = 0; i < 9; i++)
    {
        num *= 10;
        num += a[i];
    }
    return num;
}

int* MoveDown(int* a, int zero_position)
{
    int* b = new int[9];
    memcpy(b, a, 36);
    b[zero_position] = b[zero_position + 3];
    b[zero_position + 3] = 0;
    return b;
}
int* MoveUp(int* a, int zero_position)
{
    int* b = new int[9];
    memcpy(b, a, 36);
    b[zero_position] = b[zero_position - 3];
    b[zero_position - 3] = 0;
    return b;
}
int* MoveLeft(int* a, int zero_position)
{
    int* b = new int[9];
    memcpy(b, a, 36);
    b[zero_position] = b[zero_position - 1];
    b[zero_position - 1] = 0;
    return b;
}
int* MoveRight(int* a, int zero_position)
{
    int* b = new int[9];
    memcpy(b, a, 36);
    b[zero_position] = b[zero_position + 1];
    b[zero_position + 1] = 0;
    return b;
}
queue<int*>q;
queue<string>s;
int endFind = 0;
bool first = 0;
//因为问题本身的性质，不要使用深度优先遍历，会越栈
void getAnswer_deep(int* a, int* b, string t)//深度优先遍历
{
    if (judge[getnum(a) - 12345678] == 1)return;
    else { judge[getnum(a) - 12345678] = 1; }
    int j = 1;
    int zero;
    for (int i = 0; i < 9; i++)
    {
        if (a[i] != b[i])j = 0;
        if (a[i] == 0)zero = i;
    }
    if (j)
    {
        endFind = 1;
        cout << t << "\n";
        return;
    }
    if (endFind != 1)
    {
        if (zero != 6 && zero != 7 && zero != 8)
        {
            int* next = MoveDown(a, zero);
            getAnswer_deep(next, b, t + "D");
            delete[] next;
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            int* next = MoveUp(a, zero);
            getAnswer_deep(next, b, t + "U");
            delete[] next;
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            int* next = MoveLeft(a, zero);
            getAnswer_deep(next, b, t + "L");
            delete[] next;
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            int* next = MoveRight(a, zero);
            getAnswer_deep(next, b, t + "R");
            delete[] next;
        }
    }
}

void getAnswer_wide(int* a, int* b, string t)//宽度优先遍历
{
    if (judge[getnum(a) - 12345678] == 1)return;
    else { judge[getnum(a) - 12345678] = 1; }
    int j = 1;
    int zero;
    for (int i = 0; i < 9; i++)
    {
        if (a[i] != b[i])j = 0;
        if (a[i] == 0)zero = i;
    }
    if (j)
    {
        endFind = 1;
        cout << t << "\n";
        return;
    }
    if (endFind != 1)
    {
        if (zero != 6 && zero != 7 && zero != 8)
        {
            string temp1 = t + "D";
            s.push(temp1);
            int* x1 = MoveDown(a, zero);
            q.push(x1);
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            string temp2 = t + "U";
            s.push(temp2);
            int* x2 = MoveUp(a, zero);
            q.push(x2);
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            string temp3 = t + "L";
            s.push(temp3);
            int* x3 = MoveLeft(a, zero);
            q.push(x3);
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            string temp4 = t + "R";
            s.push(temp4);
            int* x4 = MoveRight(a, zero);
            q.push(x4);
        }
    }
    if (first)return;
    first = 1;
    while (!q.empty() && !s.empty())
    {
        int* next = q.front();
        string nextstr = s.front();
        q.pop();
        s.pop();
        getAnswer_wide(next, b, nextstr);
        delete[] next;
    }
}
int main()
{
    memset(judge, 0, sizeof(judge));
    int a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    int b[9] = { 0,1,2,3,4,5,6,7,8 };
    cout << "九宫格a形如:\n";
    show(a);
    cout << "九宫格b形如:\n";
    show(b);
    cout << "从a到b的操作应为:\n";
    getAnswer_wide(a, b, "");
    cout << "查找次数为：" << globalnum << endl;
}