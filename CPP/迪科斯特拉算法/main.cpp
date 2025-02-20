#include <iostream>
#include <vector>
#include <queue>
#include<unordered_map>

using namespace std;

const int INF = 0x3f3f3f3f;  // 定义正无穷

// 定义图的邻接表表示
typedef pair<int, int> P;   // first表示节点编号，second表示边权值
vector<vector<P>> graph;

// 迪杰斯特拉算法函数
/**
 * Dijkstra算法，用于计算从起始节点到图中其他节点的最短路径
 * @param start 起始节点的编号
 * @param dist 用于存储从起始节点到每个节点的最短距离
 * @param prev 用于存储最短路径中每个节点的前驱节点
 */
void dijkstra(int start, vector<int>& dist, vector<int>& prev) {
    // 获取图的节点数量
    int n = graph.size();
    
    // 初始化从起始节点到每个节点的最短距离为无穷大
    dist.resize(n, INF);
    
    // 初始化每个节点的前驱节点为-1，表示尚未确定
    prev.resize(n, -1);

    // 设置起始节点到自身的最短距离为0，前驱节点为其自身
    dist[start] = 0;
    prev[start] = start;

    // 小根堆，存储节点编号和距离
    priority_queue<P, vector<P>, greater<P>> pq;   
    // 将起始节点及其距离（0）加入小根堆
    pq.push(make_pair(start, 0));

    // 当小根堆不为空时，循环处理堆中的节点
    while (!pq.empty()) {
        // 获取并移除堆顶节点
        P p = pq.top();
        pq.pop();

        // u为当前处理的节点编号，d为从起始节点到该节点的距离
        int u = p.first, d = p.second;
        
        // 如果当前节点的最短距离已小于d，则跳过
        if (dist[u] < d) continue;

        // 遍历当前节点的所有邻接节点
        for (int i = 0; i < graph[u].size(); i++) {
            // v为邻接节点编号，w为从当前节点到邻接节点的距离
            int v = graph[u][i].first, w = graph[u][i].second;
            
            // 如果从起始节点经当前节点到邻接节点的路径更短
            if (dist[v] > dist[u] + w) {
                // 更新邻接节点的最短距离
                dist[v] = dist[u] + w;
                // 更新邻接节点的前驱节点为当前节点
                prev[v] = u;
                // 将邻接节点及其新的最短距离加入小根堆
                pq.push(make_pair(v, dist[v]));
            }
        }
    }
}

// 测试代码
int main() {
    // 定义节点数
    int n = 5;
    // 根据节点数初始化图的大小
    graph.resize(n);

    // 初始化图的连接信息
    graph[0].push_back(make_pair(1, 2));
    graph[0].push_back(make_pair(2, 4));
    graph[1].push_back(make_pair(2, 1));
    graph[1].push_back(make_pair(3, 2));
    graph[2].push_back(make_pair(3, 3));
    graph[2].push_back(make_pair(4, 2));
    graph[3].push_back(make_pair(4, 5));

    // 运行Dijkstra算法
    vector<int> dist, prev;
    dijkstra(0, dist, prev);

    // 输出结果
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": ";
        if (dist[i] == INF) {
            cout << "Unreachable" << endl;
        } else {
            cout << "Distance = " << dist[i] << ", Path = ";
            int j = i;
            while (prev[j] != j) {
                cout << j << " <- ";
                j = prev[j];
            }
            cout << j << endl;
        }
    }

    return 0;
}