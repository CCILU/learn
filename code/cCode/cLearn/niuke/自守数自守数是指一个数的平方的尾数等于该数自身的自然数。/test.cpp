#include<iostream>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int count = 0;
        for (int j = 0; j <= n; j++) {
            int i = j;
            int temp = i*i;
            while (i) {
                if (i % 10 == temp % 10) {
                    i /= 10;
                    temp /= 10;
                }
                else {
                    break;
                }
            }
            if (i == 0) {
                count++;
            }
        }
        cout << count << endl;
    }
    system("pause");
    return 0;
}