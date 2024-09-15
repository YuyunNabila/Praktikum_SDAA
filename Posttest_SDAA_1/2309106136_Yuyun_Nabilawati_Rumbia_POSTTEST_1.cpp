#include <iostream>
using namespace std;

int kombinasi(int n, int r) {
    if (r == 0 || r == n)
        return 1;
    else
        return kombinasi(n - 1, r - 1) + kombinasi(n - 1, r);
}

void segitiga_pascal(int tingkat) {
    for (int n = 0; n < tingkat; n++) {
        for (int r = 0; r <= n; r++) {
            cout << kombinasi(n, r) << " ";
        }
        cout << endl; 
    }
}

int main() {
    int banyak_tingkat = 3; 
    segitiga_pascal(banyak_tingkat);
    return 0;
}
