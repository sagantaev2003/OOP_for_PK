#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = 1e9;

// -------------------- Дейкстра --------------------
void printGraph(const vector<vector<int>>& graph) {
    int n = graph.size();
    cout << "Матрица смежности графа:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                cout << "INF\t";
            else
                cout << graph[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void dijkstra(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        if (dist[u] == INF) break;
        visited[u] = true;

        for (int v = 0; v < n; v++)
            if (graph[u][v] != INF)
                dist[v] = min(dist[v], dist[u] + graph[u][v]);
    }

    cout << "Кратчайшие расстояния от вершины " << start << " (Дейкстра):\n";
    for (int i = 0; i < n; i++)
        cout << i << ": " << (dist[i] == INF ? -1 : dist[i]) << "\n";
    cout << "\n";
}

// -------------------- Краскал --------------------
struct Edge {
    int u, v, w;
};

int find_set(int v, vector<int>& parent) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, vector<int>& parent) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) parent[b] = a;
}

void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
    vector<int> parent(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    int total_weight = 0;
    cout << "Рёбра MST (Краскал):\n";
    for (auto e : edges) {
        if (find_set(e.u, parent) != find_set(e.v, parent)) {
            cout << e.u << "-" << e.v << " (вес " << e.w << ")\n";
            total_weight += e.w;
            union_sets(e.u, e.v, parent);
        }
    }
    cout << "Общий вес MST: " << total_weight << "\n\n";
}

// -------------------- Прим --------------------
void prim(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> key(n, INF), parent(n, -1);
    vector<bool> inMST(n, false);
    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u])) u = i;

        inMST[u] = true;
        for (int v = 0; v < n; v++)
            if (graph[u][v] != INF && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
    }

    int total_weight = 0;
    cout << "Рёбра MST (Прим):\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << "-" << i << " (вес " << graph[i][parent[i]] << ")\n";
        total_weight += graph[i][parent[i]];
    }
    cout << "Общий вес MST: " << total_weight << "\n\n";
}

// запуск
int main() {
    setlocale(LC_ALL, "Russian");
    // ----- Дейкстра -----
    vector<vector<int>> graphD = {
        {0, 10, 3, INF, INF},
        {INF, 0, 1, 2, INF},
        {INF, 4, 0, 8, 2},
        {INF, INF, INF, 0, 7},
        {INF, INF, INF, 9, 0}
    };
    cout << "Исходные данные для Дейкстры:\n";
    printGraph(graphD);
    dijkstra(graphD, 0);

    // ----- Краскал -----
    int nK = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,3,8}, {1,2,3}, {2,3,5}, {2,4,7}, {3,4,9}
    };
    cout << "Исходные данные для Краскала (рёбра с весами):\n";
    for (auto e : edges)
        cout << e.u << "-" << e.v << " : " << e.w << "\n";
    cout << "\n";
    kruskal(nK, edges);

    // ----- Прим -----
    vector<vector<int>> graphP = {
        {0, 2, INF, 6, INF},
        {2, 0, 3, 8, INF},
        {INF, 3, 0, 5, 7},
        {6, 8, 5, 0, 9},
        {INF, INF, 7, 9, 0}
    };
    cout << "Исходные данные для Прима:\n";
    printGraph(graphP);
    prim(graphP);

    return 0;
}
