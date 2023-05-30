#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

class Graph {
private:
    std::vector<std::vector<int>> adjacencyList;
    std::vector<bool> visited;

public:
    Graph(int vertexCount) {
        adjacencyList.resize(vertexCount);
        visited.resize(vertexCount, false);
    }

    void addEdge(int source, int destination) {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source); // Если граф неориентированный, добавьте эту строку
    }

    void breadthFirstSearch(int startVertex) {
        std::queue<int> q;
        q.push(startVertex);
        visited[startVertex] = true;

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            std::cout << currentVertex << " ";

            // Сортировка списка смежных вершин в порядке возрастания номеров
            std::sort(adjacencyList[currentVertex].begin(), adjacencyList[currentVertex].end());

            for (int adjacentVertex : adjacencyList[currentVertex]) {
                if (!visited[adjacentVertex]) {
                    q.push(adjacentVertex);
                    visited[adjacentVertex] = true;
                }
            }
        }
    }

    void breadth(int startVertex) {
        breadthFirstSearch(startVertex);
        std::cout << std::endl;
    }
};

int main() {
    Graph g(9);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 5);
    g.addEdge(1, 4);
    g.addEdge(4, 3);
    g.addEdge(5, 3);
    g.addEdge(4, 7);
    g.addEdge(3, 6);
    g.addEdge(3, 7);
    g.addEdge(3, 8);
    g.addEdge(5, 8);
    g.addEdge(8, 6);
    g.addEdge(7, 6);

    g.breadth(7);

    return 0;
}
