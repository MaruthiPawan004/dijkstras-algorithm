#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAX_VALUE = numeric_limits<int>::max();

int findClosestVertex(const vector<int>& distances, const vector<bool>& visitedVertices, int numVertices) {
    int closestVertex = -1, minDist = MAX_VALUE;
    for (int v = 0; v < numVertices; v++) {
        if (!visitedVertices[v] && distances[v] < minDist) {
            minDist = distances[v];
            closestVertex = v;
        }
    }
    return closestVertex;
}

int computeShortestPath(const vector<vector<int>>& adjacencyMatrix, int startVertex, int endVertex) {
    int numVertices = adjacencyMatrix.size();
    vector<int> distances(numVertices, MAX_VALUE);
    vector<bool> visitedVertices(numVertices, false);

    distances[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int currentVertex = findClosestVertex(distances, visitedVertices, numVertices);
        if (currentVertex == -1) break;

        visitedVertices[currentVertex] = true;

        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
            if (!visitedVertices[neighbor] && adjacencyMatrix[currentVertex][neighbor] != MAX_VALUE && 
                distances[currentVertex] != MAX_VALUE && 
                distances[currentVertex] + adjacencyMatrix[currentVertex][neighbor] < distances[neighbor]) {
                distances[neighbor] = distances[currentVertex] + adjacencyMatrix[currentVertex][neighbor];
            }
        }
    }

    return distances[endVertex];
}

int main() {
    vector<vector<int>> adjacencyMatrix = {
        {  0,   10, MAX_VALUE, MAX_VALUE,  3 },  
        { MAX_VALUE,   0,   2,   MAX_VALUE,  4 },  
        { MAX_VALUE, MAX_VALUE,   0,   9, MAX_VALUE },  
        { MAX_VALUE, MAX_VALUE, 7,   0, MAX_VALUE },  
        { MAX_VALUE, 1,   8,   2,   0 }   
    };

    int startVertex, endVertex;
    cout << "Enter the starting vertex (0-indexed): ";
    cin >> startVertex;
    cout << "Enter the destination vertex (0-indexed): ";
    cin >> endVertex;

    int shortestPath = computeShortestPath(adjacencyMatrix, startVertex, endVertex);

    if (shortestPath == MAX_VALUE)
        cout << "\nThere is no path from vertex " << startVertex << " to vertex " << endVertex << ".\n";
    else
        cout << "\nThe shortest distance from vertex " << startVertex << " to vertex " << endVertex << " is: " << shortestPath << endl;

    return 0;
}