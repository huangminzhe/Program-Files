#include <bits/stdc++.h>
using namespace std;
map<int,int> m;
int main(int argc, char **argv){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    m[a]++,m[b]++,m[c]++,m[d]++;
    if (((*m.begin()).second == 1 && (*m.rbegin()).second == 3) || 
        ((*m.begin()).second == 2 && (*m.rbegin()).second == 2) || 
        ((*m.begin()).second == 3 && (*m.rbegin()).second == 1)){
        printf("Yes");
    }else   printf("No");
    return 0;
}
