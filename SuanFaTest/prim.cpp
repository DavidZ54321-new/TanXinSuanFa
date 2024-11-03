/*
画圈法，确定最小生成树
1.设置起点s，找到离s最近的点t
2.找到连接t的所有点，除s外。判断t和其他点的距离是否小于s到其他点的距离
3.如果是，更新距离和最近的点；反之，不理他
4.做完了，把s-t圈起来，判断t和哪个相邻的点最近（除s之外），设最近的那个点为u
5.以u代t，重复2-4步，直到把所有点全部探测完。
6.计算最小生成树的距离和，输出。
 */

#include <iostream>
#include <algorithm>
using namespace std;

const long long INF = INT_MAX;

int main(){
    // 初始化邻接矩阵，距离最近点，距离数组
    long long pointNum;
    cin >> pointNum;
    // 输入两点之间距离
    long long roadNum;
    cin >> roadNum;
    // 输入你的起点
    long long st;
    cin >> st;
    long long map[pointNum+1][pointNum+1];
    long long minDist[pointNum+1];
    long long closePoint[pointNum+1];
    for(long long x = 1; x <= pointNum; x++){
        for(long long y = 1; y <= pointNum; y++){
            map[x][y] = map[y][x] = INF;
        }
        closePoint[x] = st;
    }
    long long a,b,distance;
    for(long long i = 1; i <= roadNum; i++){
        cin >> a >> b >> distance;
        map[a][b] = map[b][a] = min(distance,INF);
    }

    // 开始运算
    // 1.读取st那一列，作为最短距离
    for(long long y = 1; y <= pointNum; y++){
        minDist[y] = map[st][y];
    }
    bool isDetected[pointNum+1];
    for(long long i = 1; i <= pointNum; i++){
        isDetected[i] = false;
    }
    isDetected[0] = isDetected[st] = true;
    while(true){
        // 2.找到离st(u)最近的那一个点
        long long point = -1;
        long long minDistance = INF; // 初始化为无穷大
        for (long long i = 1; i <= pointNum; ++i) {
            // 如果这个点未被探测并且距离比当前的最小距离小
            if (!isDetected[i] && minDist[i] < minDistance) {
                minDistance = minDist[i];
                point = i; // 更新最近点
            }
        }
        // 如果未找到有效的点，可能是图中未连通
        if (point == -1) {
            break; // 退出循环
        }
        // 3.更新minDist数组
        for (long long y = 1; y <= pointNum; y++) {
            if (!isDetected[y] && map[point][y] < minDist[y]) { // 只要没探测过的点
                minDist[y] = map[point][y];
                closePoint[y] = point;
            }
        }
        isDetected[point] = true; // 标记该点为已探测
    }
    // debug
    minDist[st] = 0;
    long long sum = 0;
    for(long long i = 1; i <= pointNum; i++){
        cout << i << ":" << minDist[i] << ":" << closePoint[i] << endl;
        sum += minDist[i];
    }
    cout << sum;
    // 有趣的是，不管你的起点是什么，最终的结果都一样
    return 0;
}