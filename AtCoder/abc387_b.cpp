#include <bits/stdc++.h>
using namespace std;
int sum;
int main(int argc, char **argv){
    int x;
    cin >> x;
    for (int i = 1;i <= 9;i++){
        for (int j = 1;j <= 9;j++){
            if (i * j != x)   sum += i * j;
        }
    }
    cout << sum;
    return 0;
}