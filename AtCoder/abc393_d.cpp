#include <bits/stdc++.h>
using namespace std;
vector<int> a;
int main(int argc, char **argv){
    int n;
    string s;
    cin >> n >> s;
    for (int i = 0;i < n;i++){
        if (s[i] == '1') {
            a.push_back(i);
        }
    }
    int len = a.size();
    vector<int> y;
    for (int i = 0;i < len;i++){
        y.push_back(a[i] - i);
    }
    int mid = y[len / 2];
    long long ans = 0;
    for (int i : y){
        ans += abs(i - mid);
    }
    cout << ans;
    return 0;
}