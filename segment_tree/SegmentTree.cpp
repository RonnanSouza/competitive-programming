#include <iostream>

using namespace std;

int  n;
int tree[100]; 

void buildSegTree(int array[], int l, int r, int pos) {
    if (l == r) {
        tree[pos] = array[l];
        return;
    }

    int mid = (l + r) / 2;
    int leftChild = 2 * pos + 1;
    int rightChild = 2 * pos + 2;
    buildSegTree(array, l, mid, leftChild);
    buildSegTree(array, mid + 1, r, rightChild);

    // For a sum inteval seg tree

    tree[pos] = tree[leftChild] + tree[rightChild];
}

int queryAux(int ql, int qr, int l, int r, int pos) {
    
    // total overlap
    if (ql <= l && qr >= r) {
        return tree[pos];
    }
    // no overlap
    if (ql > r || qr < l) {
        return 0;
    }
    int mid = (l + r) / 2;
    int left = queryAux(ql, qr, l, mid, pos * 2 + 1);
    int right = queryAux(ql, qr, mid + 1, r, pos * 2 + 2);
    return left + right;
}

int query(int arraySize, int l, int r) {
    return queryAux(l, r, 0, arraySize - 1, 0);
}

void updateAux(int l, int r, int arrayPos, int value, int treePos) {
    if (l == r) {
        tree[treePos] = value;
        return;
    }
    int leftChild = treePos * 2 + 1;
    int rightChild = treePos * 2 + 2; 
    int mid = (l + r) / 2;
    if (arrayPos <= mid) {
        updateAux(l, mid, arrayPos, value, leftChild);
    } else {
        updateAux(mid + 1, r, arrayPos, value, rightChild);
    }
    tree[treePos] = tree[leftChild] + tree[rightChild];

}

void update(int arraySize, int pos, int value) {
    updateAux(0, arraySize - 1, pos, value, 0);
}

int main() {
    cin >> n;

    int array[n];

    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    buildSegTree(array, 0, n - 1, 0);
    
    update(n, 0, 5);
    int ql, qr;
    cin >> ql >> qr;
    while (ql > -1) {
        cout << query(n, ql, qr) << endl;
        cin >> ql >> qr;
    }
    return 0;
}