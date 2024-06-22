#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// 定义最大的车站数
#define MAX_STATIONS 100

// 定义邻接矩阵的大小
int adjacency_matrix[MAX_STATIONS][MAX_STATIONS];

// 广度优先搜索函数，用于计算最少换乘次数
int bfs(int n, int start, int end) {
    int queue[MAX_STATIONS];
    bool visited[MAX_STATIONS] = {false};
    int front = 0, rear = 0;
    int level[MAX_STATIONS];
    
    // 初始化
    visited[start] = true;
    queue[rear++] = start;
    level[start] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < n; ++i) {
            if (adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
                level[i] = level[current] + 1;
                
                if (i == end) {
                    return level[i];
                }
            }
        }
    }
    
    // 如果无法到达end，返回-1表示不可达
    return -1;
}

// 打印邻接矩阵函数
void printAdjacencyMatrix(int n) {
    printf("邻接矩阵表示的有向图：\n");
    printf("   ");
    for (int i = 0; i < n; ++i) {
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%3d", i);
        for (int j = 0; j < n; ++j) {
            printf("%3d", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n; // 公交线路数和车站个数
    int i, j;
    
    printf("请输入公交线路数和车站个数：\n");
    scanf("%d %d", &m, &n);
    
    // 初始化邻接矩阵
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            adjacency_matrix[i][j] = 0;
        }
    }
    
    printf("请输入各公交线路上的各站编号：\n");
    for (i = 0; i < m; ++i) {
        int num_stations;
        printf("请输入第%d条公交线路的站点数量：\n", i+1);
        scanf("%d", &num_stations);
        
        printf("请输入第%d条公交线路经过的站点编号：\n", i+1);
        int prev_station, current_station;
        scanf("%d", &prev_station);
        for (j = 1; j < num_stations; ++j) {
            scanf("%d", &current_station);
            adjacency_matrix[prev_station][current_station] = 1;
            prev_station = current_station;
        }
    }
    
    // 打印邻接矩阵
    printAdjacencyMatrix(n);
    
    // 求最少换乘次数
    int min_transfers = bfs(n, 0, n-1);
    
    if (min_transfers == -1) {
        printf("从站0到站%d不可达。\n", n-1);
    } else {
        printf("从站0到站%d的最少换乘次数为：%d\n", n-1, min_transfers);
    }
    
    return 0;
}
