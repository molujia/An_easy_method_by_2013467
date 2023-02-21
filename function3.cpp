#include<iostream>
#include<string.h>
#include<queue>
#include<deque>
#include<stdlib.h>
#include<ctime>
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

int distance(int* a, int* b)
{
    int num = 0;
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == b[i])num++;
    }
    return num;
}

deque<int*>q;
deque<string>s;
int endFind = 0;
bool first = 0;
int best;
void getAnswer_deque(int* a, int* b, string t)//宽度优先遍历
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
            s.push_back(temp1);
            int* x1 = MoveDown(a, zero);
            if (distance(x1, b) > best)
            {
                best = distance(x1, b);
                q.push_front(x1);
            }
            else q.push_back(x1);
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            string temp2 = t + "U";
            s.push_back(temp2);
            int* x2 = MoveUp(a, zero);
            if (distance(x2, b) > best)
            {
                best = distance(x2, b);
                q.push_front(x2);
            }
            else q.push_back(x2);
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            string temp3 = t + "L";
            s.push_back(temp3);
            int* x3 = MoveLeft(a, zero);
            if (distance(x3, b) > best)
            {
                best = distance(x3, b);
                q.push_front(x3);
            }
            else q.push_back(x3);
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            string temp4 = t + "R";
            s.push_back(temp4);
            int* x4 = MoveRight(a, zero);
            if (distance(x4, b) > best)
            {
                best = distance(x4, b);
                q.push_front(x4);
            }
            else q.push_back(x4);
        }
    }
    if (first)return;
    first = 1;
    while (!q.empty() && !s.empty())
    {
        int* next = q.front();
        string nextstr = s.front();
        q.pop_front();
        s.pop_front();
        getAnswer_deque(next, b, nextstr);
        delete[] next;
    }
}

void getAnswer_nonsense(int* a, int* b, string t)//宽度优先遍历
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
            s.push_back(temp1);
            int* x1 = MoveDown(a, zero);
            if (distance(x1, b) > best)
            {
                best = distance(x1, b);
                q.push_back(x1);
            }
            else q.push_front(x1);
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            string temp2 = t + "U";
            s.push_back(temp2);
            int* x2 = MoveUp(a, zero);
            if (distance(x2, b) > best)
            {
                best = distance(x2, b);
                q.push_back(x2);
            }
            else q.push_front(x2);
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            string temp3 = t + "L";
            s.push_back(temp3);
            int* x3 = MoveLeft(a, zero);
            if (distance(x3, b) > best)
            {
                best = distance(x3, b);
                q.push_back(x3);
            }
            else q.push_front(x3);
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            string temp4 = t + "R";
            s.push_back(temp4);
            int* x4 = MoveRight(a, zero);
            if (distance(x4, b) > best)
            {
                best = distance(x4, b);
                q.push_back(x4);
            }
            else q.push_front(x4);
        }
    }
    if (first)return;
    first = 1;
    while (!q.empty() && !s.empty())
    {
        int* next = q.front();
        string nextstr = s.front();
        q.pop_front();
        s.pop_front();
        getAnswer_nonsense(next, b, nextstr);
        delete[] next;
    }
}

void getAnswer_rand(int* a, int* b, string t)//宽度优先遍历
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
            s.push_back(temp1);
            int* x1 = MoveDown(a, zero);
            if (rand()%2==0)
            {
                q.push_back(x1);
            }
            else q.push_front(x1);
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            string temp2 = t + "U";
            s.push_back(temp2);
            int* x2 = MoveUp(a, zero);
            if (rand()%2==0)
            {
                q.push_back(x2);
            }
            else q.push_front(x2);
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            string temp3 = t + "L";
            s.push_back(temp3);
            int* x3 = MoveLeft(a, zero);
            if (rand() % 2 == 0)
            {
                q.push_back(x3);
            }
            else q.push_front(x3);
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            string temp4 = t + "R";
            s.push_back(temp4);
            int* x4 = MoveRight(a, zero);
            if (rand() % 2 == 0)
            {
                q.push_back(x4);
            }
            else q.push_front(x4);
        }
    }
    if (first)return;
    first = 1;
    while (!q.empty() && !s.empty())
    {
        int* next = q.front();
        string nextstr = s.front();
        q.pop_front();
        s.pop_front();
        getAnswer_rand(next, b, nextstr);
        delete[] next;
    }
}

int main()
{
    memset(judge, 0, sizeof(judge));
    int a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    int b[9] = { 0,1,2,3,4,5,6,7,8 };
    unsigned int seed = time(0);
    srand(seed);
    best = distance(a, b);
    getAnswer_rand(a, b, "");
    cout << endl << globalnum << endl;
    //334453
    //272544
    //386315
    //261830
    //418688
}