#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

int main () {
    int N, n;
    string buffer;
    char c;
    vector <char> parenthese;

    cin >> N;
    getchar();
    n = N;
    while (n--) {
        bool match = true;
        getline(cin, buffer);

        for (int i = 0 ; buffer[i]!='\0' ; i++) {
            if (buffer[i] == '{' || buffer[i] == '[' || buffer[i] == '(' || buffer[i] == '<')
                parenthese.push_back(buffer[i]);
            else if (!parenthese.empty()) {
                if (buffer[i] == '}' && parenthese.back() == '{')
                    parenthese.pop_back();
                else if (buffer[i] == ']' && parenthese.back() == '[')
                    parenthese.pop_back();
                else if (buffer[i] == ')' && parenthese.back() == '(')
                    parenthese.pop_back();
                else if (buffer[i] == '>' && parenthese.back() == '<')
                    parenthese.pop_back();
                else {
                    match = false;
                    break;
                }
            }
            else if (parenthese.empty()) {
                match = false;
                break;
            }
        }

        if (match && parenthese.empty()) cout << "Case " << N-n << ": Yes" << endl;
        else cout << "Case " << N-n << ": No" << endl;

        parenthese.clear();
    }
}

/*
I:
2
{[()]}()
[(<})]

O:
Case 1: Yes
Case 2: No
*/
