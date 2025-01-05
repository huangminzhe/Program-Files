#include <bits/stdc++.h>
using namespace std;
string s,t;
int k;
int main(int rgc, char **argv){
    cin >> k >> s >> t;
    if (s == t){
        printf("Yes");
        return 0;
    }
    int lens = s.size(),lent = t.size();
    if (abs(lens - lent) > 1){
        printf("No");
        return 0;
    }
    int i = 0,j = 0,f = 0,idx = 0;
    while (i < lens && j < lent){
        if (s[i] != t[j]){
            f++;
            idx = i;
            if (f > 1){
                printf("No");
                return 0;
            }
            if (lens < lent)    j++;
            else    i++;
        }else   i++,j++;
    }
    if (lens == lent){
        printf("Yes");
    }else if (lens > lent){
        s = s.substr(0,idx) + s.substr(idx + 1);
        if (!f) printf("Yes");
        else if (s == t)    printf("Yes");
        else    printf("No");
    }else{
        t = t.substr(0,idx) + t.substr(idx + 1);
        if (!f) printf("Yes");
        else if (s == t)    printf("Yes");
        else    printf("No");
    }
    return 0;
}
