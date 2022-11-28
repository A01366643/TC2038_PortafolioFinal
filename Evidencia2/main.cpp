/*
Integrantes:
- Fernando López Gómez (A01639715)
- Fausto Alejandro Palma Cervantes (A01639224)
- Luisa Fernanda Castaños Arias (A01366643)
Compilar:
  g++ A011366643_ActInt2/main.cpp -o main
Ejecutar
  ./main < in.txt
Referencias:
  https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
  https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
  https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
*/

#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <queue>
#include <string.h>
#include <vector>

// Define infinity
#define INF 0x3f3f3f3f

// Complejidad computacional: O(n)
void printMat(int *matrix, int n) {
  std::cout << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[(i * n) + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Complejidad computacional: O(n)
void printAlfa(std::string &coords) {
  std::string strNum;
  int intNum;
  for (char i : coords) {
    if (isdigit(i)) {
      strNum += i;
    } else {
      if (i == ',' || i == ')') {
        intNum = stoi(strNum);
        // intNum = 701; // LIMIT: 701
        if(intNum >= 26) {std::cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[((intNum-26)/26)%26];}
        std::cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[intNum%26];
        strNum.clear();
      }
      std::cout << i;
    }
  }
  std::cout << std::endl;
}

// Complejidad computacional: O(n)
void printVec(std::vector<std::pair<int, int>> &v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << "(" << v[i].first << "," << v[i].second << ")";
  }
  std::cout << std::endl;
}

// Complejidad computacional: O(n log n)
void quicksort(int *arr, int *mat, int start, int end) {
  if (start < end) {
    int i = start + 1;
    for (int j = i; j < end; j++) {
      if (mat[arr[j]] <= mat[arr[start]]) {
        std::swap(arr[i], arr[j]);
        i++;
      }
    }
    std::swap(arr[start], arr[i - 1]);
    quicksort(arr, mat, start, i - 1);
    quicksort(arr, mat, i, end);
  }
}

// Complejidad computacional: O(ElogE) || O(ElogV)
void kruskal(int *matrix, int n) {
  int indexArray[n * (n - 1)], rInt, cInt;
  std::string rStr, cStr;
  for (int i = 0; i < n * n; i++) {
    if (i % (n + 1) != 0) {
      indexArray[((n * (i / (n + 1))) + (i % (n + 1))) - 1] = i;
    }
  }
  quicksort(indexArray, matrix, 0, n * (n - 1));
  // for(auto i: indexArray) {std::cout << i << " ";}
  // std::cout << std::endl;
  std::vector<std::string> disjointSet;
  disjointSet.push_back("(" + std::to_string(indexArray[0] / n) + "," + std::to_string(indexArray[0] % n) + ")");
  int seq = 1;
  for (int i = 1; i < sizeof(indexArray) / sizeof(int); i++) {
    rStr = std::to_string(indexArray[i] / n);
    cStr = std::to_string(indexArray[i] % n);
    rInt = -1, cInt = -1;
    for (int j = 0; j < disjointSet.size(); j++) {
      if (disjointSet[j].find(rStr) != std::string::npos) {
        rInt = j;
      }
      if (disjointSet[j].find(cStr) != std::string::npos) {
        cInt = j;
      }
    }
    if (rInt < 0 && cInt < 0) {
      disjointSet.push_back("(" + rStr + "," + cStr + ")");
    } else if (rInt != cInt && rInt < 0) {
      disjointSet[cInt] += "(" + rStr + "," + cStr + ")";
    } else if (rInt != cInt && cInt < 0) {
      disjointSet[rInt] += "(" + rStr + "," + cStr + ")";
    } else if (rInt != cInt) {
      disjointSet[rInt] += disjointSet[cInt] + "(" + rStr + "," + cStr + ")";
      disjointSet.erase(disjointSet.begin() + cInt);
    }
    if ((rInt < 0 && cInt < 0) || (rInt != cInt)) {
      seq++;
    }
    // std::cout << "R: " << rInt << " C: " << cInt << " Seq: " << seq <<
    // std::endl;
    if (seq == (n - 1)) {
      break;
    }
  }
  // PRINT
  printAlfa(disjointSet[0]);
}

//Complejidad computacional: O(n^2)
void TSP(int *matrizAdj, int size) {
  int secuencia[size] = {}, k = 0;
  std::string set;
  bool visitados[size] = {};
  for (int i = 0; i < size; i++) {
    set += "(" + std::to_string(k) + ",";
    visitados[k] = 1;
    for (int j = 0; j < size; j++) {
      if (visitados[j] == 0) {
        if (secuencia[k] == 0 ||
            matrizAdj[(k * size) + j] < matrizAdj[(k * size) + secuencia[k]]) {
          secuencia[k] = j;
        }
      }
    }
    k = secuencia[k];
    set += std::to_string(k) + ")";
  }
  printAlfa(set);
}

//Complejidad Computacional: O(V^2)
int bfs(int n, std::vector<std::vector<int>> &dataTransmissionMatrix, int source, int target, std::vector<int> &parent) {
  fill(parent.begin(), parent.end(), -1);
  parent[source] = -2;
  std::queue<std::pair<int, int>> q;
  q.push({source, 1e9});
  while (!q.empty()) {
    int u = q.front().first;
    int cap = q.front().second;
    q.pop();
    for (int i = 0; i < n; i++) {
      if (u != i && dataTransmissionMatrix[u][i] != 0 && parent[i] == -1) {
        parent[i] = u;
        int min_cap = std::min(cap, dataTransmissionMatrix[u][i]);
        if (i == target) {
          return min_cap;
        }
        q.push({i, min_cap});
      }
    }
  }
  return 0;
}

// Complejidad computacional: O (max_flow * E)
int ford_Fulkerson(int n, int source, int target, std::vector<std::vector<int>> &dataTransmissionMatrix) {
  std::vector<int> parent(n, -1);
  int max_flow = 0;
  int min_cap = 0;
  while (min_cap = bfs(n, dataTransmissionMatrix, source, target, parent)) {
    max_flow += min_cap;
    int v = target;
    while (v != source) {
      int u = parent[v];
      dataTransmissionMatrix[u][v] -= min_cap;
      dataTransmissionMatrix[v][u] += min_cap;
      v = u;
    }
  }
  return max_flow;
}

void addEdge(std::vector<std::vector<int>> &dataTransmissionMatrix, int i,
             int j, int val) {
  dataTransmissionMatrix[i][j] = val;
}

// Complejidad computacional: O(n)
void bottomLeftPoint(std::vector<std::pair<int, int>> &v) {
  int indexBLP = 0;
  for (int i = 1; i < v.size(); i++) {
    if ((v[i].second < v[indexBLP].second) ||
        (v[i].second == v[indexBLP].second && v[i].first < v[indexBLP].first)) {
      indexBLP = i;
    }
  }
  std::swap(v[indexBLP], v[0]);
  // printVec(v);
}

// Complejidad computacional: O(1)
int orientation(std::pair<int, int> a, std::pair<int, int> b,
                std::pair<int, int> c) {
  int ori = (b.second - a.second) * (c.first - b.first) -
            (c.second - b.second) * (b.first - a.first);
  if (ori == 0)
    return 0; // Collinear
  if (ori > 0)
    return 1; // Clockwise
  return 2;   // Counterclockwise
}

// Complejidad computacional: O(n log n)
void polarAngleQuicksort(std::vector<std::pair<int, int>> &v, int start,
                         int end) {
  if (start < end) {
    int i = start + 1, ori, dx, dy, distI, distJ;
    for (int j = i; j < end; j++) {
      ori = orientation(v[0], v[start], v[j]);
      // std::cout << "orientation(v[0], v[" << start << "], v[" << j << "]): "
      // << ori << std::endl; printVec(v);
      if (ori == 1) {
        std::swap(v[i], v[j]);
        i++;
      }
    }
    swap(v[start], v[i - 1]);
    // printVec(v);
    polarAngleQuicksort(v, start, i - 1);
    polarAngleQuicksort(v, i, end);
  }
}

// Complejidad computacional: O(n)
void pointSelection(std::vector<std::pair<int, int>> &v) {
  int ori, distI, distIMU;
  for (int i = 1; i < v.size() - 1; i++) {
    ori = orientation(v[0], v[i], v[i + 1]);
    // std::cout << "ori: " << ori << std::endl;
    if (ori == 0) {
      distI = (v[i].first - v[0].first) * (v[i].first - v[0].first) +
              (v[i].second - v[0].second) * (v[i].second - v[0].second);
      distIMU =
          (v[i + 1].first - v[0].first) * (v[i + 1].first - v[0].first) +
          (v[i + 1].second - v[0].second) * (v[i + 1].second - v[0].second);
      // std::cout << "i: " << i << " distI: " << distI << " distIMU: " <<
      // distIMU << std::endl;
      if (distI < distIMU) {
        v.erase(v.begin() + i);
      } else {
        v.erase(v.begin() + i + 1);
      }
      i--;
    }
    // printVec(v);
  }
}

// Complejidad computacional: O(n)
void convexHull(std::vector<std::pair<int, int>> &v) {
  if (v.size() < 3) {
    std::cout
        << "ERROR: No es posible crear un polígono convexo con esos puntos"
        << std::endl;
    return;
  }
  int next = 2, curr = 1, prev = 0, ori;
  while (next < v.size()) {
    ori = orientation(v[prev], v[curr], v[next]);
    // std::cout << "prev: " << prev << " curr: " << curr << " next: " << next
    // << " | ori: " << ori << std::endl;
    if (ori == 2) {
      next++, curr++, prev++;
    } else {
      v.erase(v.begin() + curr);
      next--, curr--, prev--;
    }
  }
  // PROPER PRINT
  printVec(v);
}

// Complejidad computacional: O(n log n)
void grahamScan(std::vector<std::pair<int, int>> &v) {
  bottomLeftPoint(v);                  // STEP 1
  polarAngleQuicksort(v, 1, v.size()); // STEPS 2-3
  pointSelection(v);                   // STEPS 4-5
  convexHull(v);                       // STEP 6
}

int main(int argc, char *argv[]) {
  int n, val, coma;
  std::string line;
  // N
  std::cin >> n;
  // Create distance matrix
  int distanceMatrix[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> val;
      distanceMatrix[i][j] = val;
    }
  }
  // PRINT
  // printMat(*distanceMatrix, n);
  // PUNTO 1
  kruskal(*distanceMatrix, n);
  // PUNTO 2
  TSP(*distanceMatrix, n);
  // Create data flow matrix
  std::vector<std::vector<int>> dataTransmissionMatrix(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> val;
      addEdge(dataTransmissionMatrix, i, j, val);
    }
  }
  // PUNTO 3
  std::cout << ford_Fulkerson(n, 0, n-1, dataTransmissionMatrix) << std::endl;
  // Create "centrals" array
  std::pair<int, int> coord;
  std::vector<std::pair<int, int>> centrals;
  while (std::cin >> line) {
    line = line.substr(1, line.size() - 2);
    coma = line.find(',');
    coord.first = stoi(line.substr(0, coma));
    coord.second = stoi(line.substr(coma + 1, line.size() - 1));
    centrals.push_back(coord);
  }
  // PRINT
  // printVec(centrals);
  // PUNTO 4
  grahamScan(centrals);
  return 0;
}