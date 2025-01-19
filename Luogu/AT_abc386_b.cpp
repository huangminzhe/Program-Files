#include <bits/stdc++.h>
using namespace std;
string s;
int cnt;
int main(int argc, char **argv){
    cin >> s;
    int n = s.size();
    for (int i = 0;i < n;i++){
        if (s[i] == '0'){
            int cnt0 = 1;
            while(s[i + 1] == '0')  i++,cnt0++;
            cnt += ceil(cnt0 / 2.0);
        }else cnt++;
    }
    cout << cnt;
    return 0;
}