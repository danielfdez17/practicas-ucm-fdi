#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
using matrix = vector<vector<int>>;

matrix dp;
string a, b, sol;

bool ok(int i, int j) {
    return 1 <= i && i <= a.size() && 1 <= j && j <= b.size();
}

int lcs() {
    // if (!ok(i, j)) return 0;
    // if (a[i - 1] == b[j - 1])
    //     return dp[i][j] = dp[i - 1][j - 1] + 1;
    // return dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    for (int i = 1; i < dp.size(); ++i) {
        for(int j = 1; j < dp[0].size(); ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[a.size()][b.size()];
}

void build(int i, int j) {
    if (!ok(i, j)) return;
    if (a[i - 1] == b[j - 1]) {
        sol.push_back(a[i - 1]);
        build(i - 1, j - 1);
        return;
    }
    if (dp[i][j] == dp[i - 1][j]) {
        build(i - 1, j);
        return;
    }
    if (dp[i][j] == dp[i][j - 1]) {
        build(i, j - 1);
        return;
    }
}

int main() {
    // int finish;
    // while (cin >> finish && finish != 0) {
    //     cin.ignore(1, '\n');
    //     getline(cin, a);
    //     getline(cin, b);
    //     sol = "";
    //     dp = vector<vector<int>>(a.size() + 1, vector<int>(b.size() + 1, 0));
    //     cout << "LCS size: " << lcs() << "\n";
    //     build(a.size(), b.size()); 
    //     reverse(sol.begin(), sol.end());
    //     cout << "LCS: " << sol << "\n";

    // }
    a = "abcdaf"; b = "acbcf"; sol = "";
    dp = vector<vector<int>>(a.size() + 1, vector<int>(b.size() + 1, 0));
    cout << "LCS size: " << lcs() << "\n";
    build(a.size(), b.size()); 
    reverse(sol.begin(), sol.end());
    cout << "LCS: " << sol << "\n";

    return 0;
}