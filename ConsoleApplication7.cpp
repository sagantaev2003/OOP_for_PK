#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printGraphEuler(const vector<vector<int>>& graph) {
    int n = graph.size();
    cout << "Матрица смежности графа:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << graph[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

void findEulerPath(vector<vector<int>>& graph, int u, vector<int>& path) {
    int n = graph.size();
    for (int v = 0; v < n; v++) {
        while (graph[u][v] > 0) {
            graph[u][v]--;
            graph[v][u]--;
            findEulerPath(graph, v, path);
        }
    }
    path.push_back(u);
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> graph = {
        {0,1,1,0},
        {1,0,1,1},
        {1,1,0,1},
        {0,1,1,0}
    };

    cout << "Исходные данные для Эйлера:\n";
    printGraphEuler(graph);

    // ----- Эйлеров путь -----
    vector<int> path;
    findEulerPath(graph, 0, path);

    reverse(path.begin(), path.end());
    cout << "Эйлеров путь/цикл: ";
    for (int v : path)
        cout << v << " ";
    cout << "\n\n";

    return 0;
}
