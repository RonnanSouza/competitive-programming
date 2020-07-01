    #include <iostream>

    const int MAXN =  2 * 100000;
    const int MAXLOG = 18;

    int n;
    int logs[MAXN];
    int table[MAXLOG][MAXN];


    void computeLogs() {
    logs[1] = 0;
    for (int i = 2; i <= n; i++) {
        logs[i] = logs[i / 2] + 1;
    }
    }

    void buildSparseTable() {
        for (int i = 1; i <= logs[n]; i++) {
            int currentLen = 1 << i;
            for (int j = 0; j + currentLen <= n; j++) {
                table[i][j] = std::min(table[i - 1][j], table[i - 1][j + (currentLen / 2)]);
            }
        }
    }

    int getMin(int l, int r) {
        int p = logs[r - l + 1];
        int pLen = 1 << p;
        return std::min(table[p][l], table[p][r - pLen + 1]);
    }

    int main() {
        std::cin >> n;
        computeLogs();
        for (int i = 0; i < n; i++) {
            std::cin >> table[0][i];
        }
        buildSparseTable();
        int q;
        std::cin >> q;
        for (int i = 0; i < q; i++) {
            int l, r;
            std::cin >> l >> r;
            std::cout << getMin(l, r) << "\n";
        }
        return 0;
    }