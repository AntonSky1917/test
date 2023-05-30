#include <iostream>

#define SIZE 6
#define INF 999999

class Graph {
private:
    int matrix[SIZE][SIZE]; // матрица смежности
    int vertexes[SIZE];     // хранилище вершин
    int vertexCount;        // количество добавленных вершин
    int shortestDistances[SIZE]; // массив кратчайших расстояний

public:
    Graph() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = 0;
        vertexCount = 0;
    }

    // добавление вершины
    void addVertex(int vnumber) {
        vertexes[vertexCount] = vnumber;
        vertexCount++;
    }

    // добавление ребра
    void addEdge(int v1, int v2, int weight) {
        matrix[v1][v2] = weight;
        matrix[v2][v1] = weight;
    }

    // проверка существования ребра
    bool edgeExists(int v1, int v2) {
        return matrix[v1][v2] > 0;
    }

    // проверка существования вершины
    bool vertexExists(int v) {
        for (int i = 0; i < vertexCount; i++)
            if (vertexes[i] == v)
                return true;
        return false;
    }

    // поиск индекса вершины с минимальным расстоянием
    int findMinDistanceIndex(int dist[], bool visited[]) {
        int minDist = INF;
        int minIndex = -1;
        for (int i = 0; i < SIZE; i++) {
            if (!visited[i] && dist[i] <= minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    // поиск кратчайшего расстояния от указанной вершины до всех остальных
    void findMinDistanceDijkstra(int startVertex) {
        int dist[SIZE];        // массив кратчайших расстояний
        bool visited[SIZE];    // массив посещенных вершин

        // Инициализация массивов dist[] и visited[]
        for (int i = 0; i < SIZE; i++) {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[startVertex] = 0; // Расстояние от начальной вершины до себя равно 0

        for (int count = 0; count < SIZE - 1; count++) {
            int u = findMinDistanceIndex(dist, visited);
            visited[u] = true;
            for (int v = 0; v < SIZE; v++) {
                if (!visited[v] && edgeExists(u, v) && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }

        // Сохранение кратчайших расстояний
        for (int i = 0; i < SIZE; i++) {
            shortestDistances[i] = dist[i];
        }
    }

    // вывод кратчайших расстояний
    void printShortestDistances() {
        for (int i = 0; i < SIZE; i++) {
            std::cout << shortestDistances[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Graph g;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    g.addEdge(0, 2, 13);
    g.addEdge(0, 4, 21);
    g.addEdge(0, 5, 27);
    g.addEdge(2, 3, 82);
    g.addEdge(2, 4, 77);
    g.addEdge(4, 1, 43);
    g.addEdge(4, 5, 11);
    g.addEdge(5, 1, 38);

    g.findMinDistanceDijkstra(4);
    g.printShortestDistances();

    return 0;
}
