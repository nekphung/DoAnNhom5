﻿#include "FloydWarshall.h"

const int INF = 1000000000;  // Giá trị đại diện cho vô cùng (không có đường đi trực tiếp)

// Constructor: Khởi tạo ma trận kề với trọng số vô hạn, trừ đường chéo là 0
floydWarshall::floydWarshall(int vertex) : V(vertex) {
    adjMatrix.assign(V, vector<int>(V, INF));   // Tạo ma trận V x V toàn INF
    for (int i = 0; i < V; i++) {
        adjMatrix[i][i] = 0;                    // Khoảng cách từ i đến i là 0
    }
}

// Thêm cạnh có hướng từ start → end với trọng số weight
void floydWarshall::addEdge(int start, int end, int weight) {
    adjMatrix[start][end] = weight;
}

// Thuật toán Floyd-Warshall: tìm đường đi ngắn nhất giữa mọi cặp đỉnh
void floydWarshall::FloydWarshall() {
    // Sao chép ma trận kề sang ma trận khoảng cách ban đầu
    vector<vector<int>> dist = adjMatrix;

    // Ba vòng lặp: duyệt qua đỉnh trung gian k, điểm xuất phát i và điểm kết thúc j
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if (dist[i][k] == INF) continue; // Không cần xét nếu không đi từ i đến k
            for (int j = 0; j < V; ++j) {
                if (dist[k][j] == INF) continue; // Không cần xét nếu không đi từ k đến j

                // Kiểm tra xem đường đi qua k có ngắn hơn không
                int viaK = dist[i][k] + dist[k][j];
                if (viaK < dist[i][j]) {
                    dist[i][j] = viaK;
                }
            }
        }
    }

    // In ma trận khoảng cách kết quả
    cout << "\nAll pairs shortest paths (Floyd–Warshall):\n";
    printMatrix(dist);
}

// Hàm hỗ trợ: In ma trận khoảng cách ra màn hình
void floydWarshall::printMatrix(const vector<vector<int>>& dist) {
    // In hàng tiêu đề (các đỉnh đích)
    cout << setw(6) << "";
    for (int j = 0; j < V; ++j)
        cout << setw(6) << j;
    cout << "\n" << string(7 + 6 * V, '-') << "\n";

    // In từng hàng (từng đỉnh xuất phát)
    for (int i = 0; i < V; ++i) {
        cout << setw(6) << i << "|";
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}
