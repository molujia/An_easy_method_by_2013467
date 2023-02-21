#include<iostream>
#include<string.h>
#include<string>
#include<queue>
using namespace std;

int globalnum = 0;//记录搜索次数
//宫格大小
int n = 3;
bool judge[400000];
int all[400000];

int find(int l, int r, int n) {//二分查找 
    globalnum += 1;
    int mid = l + (r - l) / 2;
    if (all[mid] == n)return mid;
    else if (l<r && all[mid]>n)return find(l, mid - 1, n);
    else if (l < r && all[mid] < n) return find(mid + 1, r, n);
    return -1;
}

char ans[9];
bool isUsed[9];
int len = 0;
void getall(int n, int k)
{
    for (int i = 0; i <= n; i++)
    {
        if (!isUsed[i])
        {
            ans[k] = '0' + i;
            //cout << ans[k];
            isUsed[i] = 1;
            if (k == n)
            {
                //cout << ans;
                all[len++] = atol(ans);
            }
            else
            {
                getall(n, k + 1);
            }
            isUsed[i] = 0;//回溯一步 
        }
    }
}

void show(string a)
{
    for (int i = 0; i < 9; i++)
    {
        cout << a[i] << " ";
        if ((i + 1) % 3 == 0)cout << "\n";
    }
    cout << "\n";
}

string MoveDown(string a, int zero_position)
{
    string b = a;
    b[zero_position] = b[zero_position + 3];
    b[zero_position + 3] = '0';
    return b;
}

string MoveUp(string a, int zero_position)
{
    string b = a;
    b[zero_position] = b[zero_position - 3];
    b[zero_position - 3] = '0';
    return b;
}

string MoveLeft(string a, int zero_position)
{
    string b = a;
    b[zero_position] = b[zero_position - 1];
    b[zero_position - 1] = '0';
    return b;
}

string MoveRight(string a, int zero_position)
{
    string b = a;
    b[zero_position] = b[zero_position + 1];
    b[zero_position + 1] = '0';
    return b;
}

queue<int>q;
queue<string>s;
int endFind = 0;
bool first = 0;

void getAnswer_wide(int a, int b, string t)//宽度优先遍历
{
    if (a == b)
    {
        endFind = 1;
        cout << t << "\n";
        return;
    }

    int place = find(0, 400000, a);

    if (judge[place] == 1)return;
    else { judge[place] = 1; }

    string as = to_string(a);

    //cout << as << endl;

    int zero = -1;
    //cout << as.length()<<endl;
    for (int i = 0; i < as.length(); i++)
    {
        if (as[i] == 48)zero = i;
    }
    //cout << "ZZZ!" << zero << endl;
    if (zero == -1)
    {
        as = '0' + as;
        zero = 0;//没有零说明零在首位
    }


    if (endFind != 1)
    {
        if (zero != 6 && zero != 7 && zero != 8)
        {
            //cout << as << endl;
            string temp1 = t + "D";
            s.push(temp1);
            string x1 = MoveDown(as, zero);
            int xx1 = atol(x1.c_str());
            q.push(xx1);
        }
        if (zero != 0 && zero != 1 && zero != 2)
        {
            string temp1 = t + "U";
            s.push(temp1);
            string x1 = MoveUp(as, zero);
            int xx1 = atol(x1.c_str());
            q.push(xx1);
        }
        if (zero != 0 && zero != 3 && zero != 6)
        {
            string temp1 = t + "L";
            s.push(temp1);
            string x1 = MoveLeft(as, zero);
            int xx1 = atol(x1.c_str());
            q.push(xx1);
        }
        if (zero != 2 && zero != 5 && zero != 8)
        {
            string temp1 = t + "R";
            s.push(temp1);
            string x1 = MoveRight(as, zero);
            int xx1 = atol(x1.c_str());
            q.push(xx1);
        }
    }

    if (first)return;
    first = 1;

    while (!q.empty() && !s.empty())
    {
        int next = q.front();
        string nextstr = s.front();
        q.pop();
        s.pop();
        getAnswer_wide(next, b, nextstr);
    }
}
int main()
{
    memset(judge, 0, sizeof(judge));
    string a = "123456780";
    string b = "012345678";
    getall(8, 0);

    cout << "九宫格a形如:\n";
    show(a);
    cout << "九宫格b形如:\n";
    show(b);
    cout << "从a到b的操作应为:\n";
    getAnswer_wide(123456780, 12345678, "ans:");
    cout << "\n查找次数为：" << globalnum << endl;
}