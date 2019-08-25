#include <bits/stdc++.h>
using namespace std;

bool isOperator(const char &c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    }
    return false;
}

int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string s)
{
    std::stack<char> st;
    st.push('N');
    int l = s.length();
    string ns;
    for (int i = 0; i < l; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            ns += s[i];

        else if (s[i] == '(')

            st.push('(');

        else if (s[i] == ')')
        {
            while (st.top() != 'N' && st.top() != '(')
            {
                char c = st.top();
                st.pop();
                ns += c;
            }
            if (st.top() == '(')
            {
                char c = st.top();
                st.pop();
            }
        }

        else
        {
            while (st.top() != 'N' && prec(s[i]) <= prec(st.top()))
            {
                char c = st.top();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }
    }

    while (st.top() != 'N')
    {
        char c = st.top();
        st.pop();
        ns += c;
    }

    return ns;
}

int evaluate(const string &s)
{
    int result = 0;
    map<char, int> m;
    char c = 'a';
    string symS = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            int x = 0;
            do
            {
                x = x * 10 + (s[i++] - '0');
            } while (isdigit(s[i]));
            i--;
            m[c] = x;
            symS.append(string(1, c++));
        }
        else if (isOperator(s[i]) || s[i] == '(' || s[i] == ')')
        {
            symS.append(string(1, s[i]));
        }
    }
    symS = infixToPostfix(symS);
    stack<int> ev;
    for (auto i : symS)
    {
        if (isOperator(i))
        {
            int a = ev.top();
            ev.pop();
            int b = ev.top();
            ev.pop();
            int ans = 0;
            switch (i)
            {
            case '^':
                ans = int(pow(b, a) + 0.5);
                break;

            case '*':
                ans = b * a;
                break;

            case '/':
                ans = b / a;
                break;

            case '+':
                ans = b + a;
                break;

            case '-':
                ans = b - a;
                break;

            default:
                break;
            }
            ev.push(ans);
        }
        else
        {
            ev.push(m[i]);
        }
    }
    result = ev.top();
    ev.pop();
    return result;
}

int main()
{
    string inp = "";
    cin >> inp;
    cout << evaluate(inp);

    return 0;
}
