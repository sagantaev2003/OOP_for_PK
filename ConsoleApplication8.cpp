#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printGraphChristofides(const vector<vector<int>>& graph) {
    int n = graph.size();
    cout << "Матрица расстояний для Кристофидеса:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << graph[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

// для простоты: реализуем жадный обход (не полный Кристофидес, но приближение)
vector<int> greedyTSP(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> path;
    int u = 0;
    path.push_back(u);
    visited[u] = true;

    for (int i = 1; i < n; i++) {
        int next = -1;
        int minDist = 1e9;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] < minDist) {
                minDist = graph[u][v];
                next = v;
            }
        }
        u = next;
        path.push_back(u);
        visited[u] = true;
    }
    path.push_back(0); // возврат в стартовую вершину
    return path;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> graph = {
        {0,10,15,20,10},
        {10,0,35,25,15},
        {15,35,0,30,20},
        {20,25,30,0,25},
        {10,15,20,25,0}
    };

    cout << "Исходные данные для Кристофидеса:\n";
    printGraphChristofides(graph);

    vector<int> path = greedyTSP(graph);
    int total = 0;
    cout << "Приближённый путь коммивояжёра: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
        if (i > 0) total += graph[path[i - 1]][path[i]];
    }
    cout << "\nОбщая длина пути: " << total << "\n\n";

    return 0;
}
