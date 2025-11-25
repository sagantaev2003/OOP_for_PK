#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; 

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 4;
    vector<vector<int>> dist = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    cout << "Исходная матрица расстояний:\n";
    for (auto& row : dist) {
        for (int x : row)
            cout << (x == INF ? 999 : x) << "\t";
        cout << endl;
    }

    // ------- Алгоритм Флойда --------
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "\nМатрица кратчайших путей (результат Флойда):\n";
    for (auto& row : dist) {
        for (int x : row)
            cout << (x == INF ? 999 : x) << "\t";
        cout << endl;
    }

    return 0;
}
