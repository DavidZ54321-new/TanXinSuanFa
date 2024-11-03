#include <iostream>
using namespace std;

const long long INF = 1e7;

bool allDetected(const bool flag[],long long n){
    for(long long i = 1; i <= n; i++){
        if(!flag[i]){
            return false;
        }
    }
    return true;
}

void printBestWay(const long long p[], long long targetPoint, long long st){
    // 回溯路径方式
    long long bestWay[121];
    long long i = 1;
    for (long long & zcw : bestWay){
        zcw = INF;
    }
    bestWay[0] = targetPoint;
    while (p[targetPoint] != -1){
        bestWay[i] = p[targetPoint];
        targetPoint = p[targetPoint];
        i++;
    }
    // 输出
    long long j = 120;
    while(bestWay[j] == INF){
        j--;
    }
    cout << st;
    j--;
    for (; j >= 0; j--){
        cout << "-" << bestWay[j];
    }
    cout << "\n";
}

int main(){
    // 城市数量，路线数量
    long long cityNum, roadNum;
    cin >> cityNum >> roadNum;
    // 初始化地图线路图和标记
    long long real_cityNum = cityNum+5;
    long long map[real_cityNum][real_cityNum]; //
    bool isFound[cityNum+1]; //
    long long qianQu[real_cityNum];
    long long dist[real_cityNum];
    for(long long x = 0; x < real_cityNum; x++){
        for(long long y = 0; y < real_cityNum; y++){
            map[x][y] = INF;
        }
        qianQu[x] = -1;
        dist[x] = INF;
    }
    for(long long i = 0; i < (cityNum+1); i++){
        isFound[i] = false;
    }
    // 输入具体的线路图
    long long city_s, city_e, distance;
    for(long long n = 1; n <= roadNum; n++){
        cin >> city_s >> city_e >> distance;
        map[city_s][city_e] = min(map[city_s][city_e],distance);
    }
    // 输入你开始的位置
    long long startP;
    cin >> startP;
    // 开始计算
    // 1.初始化距离，前驱，标点，从startP开始
    for(long long y = 1; y <= cityNum; y++){
        dist[y] = map[startP][y];
        if(dist[y] == INF){
            qianQu[y] = -1;
        }else{
            qianQu[y] = startP;
        }
    }
    dist[startP] = 0;
    isFound[startP] = true;
    isFound[0] = true;
    // 2.找最小，标好点，借东风
    while(!allDetected(isFound,cityNum)){ // 没探测完就别停下来
        // 找dist[]最小
        long long temp = INF;
        long long x = startP;
        for(long long i = 1; i <= cityNum; i++){
            if(!isFound[i] && dist[i] < temp){ // 随便找一个临近的就行了
                x = i; // x是你的当前位置
                temp = dist[i];
            }
            // 标记当前位置x已经探测到
            isFound[x] = true;
            // 借东风
            // 先筛除不临近的（x到y的距离无穷大），再搞出到startP最近的点的距离（startP到y的距离 > startP到当前点x的距离 + x到y的距离，是的话就更新）
            for(long long y = 1; y <= cityNum; y++){ // x为当前位置，从1号一直往上找
                if(!isFound[y] && map[x][y] < INF){ // 没找过的城市，以及是距离不是无限的，考虑一下
                    if(dist[y] > (dist[x] + map[x][y])){ // 如果距离小的，更新dist[]和前驱qianQu[]
                        dist[y] = dist[x] + map[x][y];
                        qianQu[y] = x;
                    }
                }
            }
        }
    }
    // 输出结果
    for(long long i = 1; i <= cityNum; i++){
        if (dist[i] == INF){
            cout << startP << "-" << i << ":No way!" << endl;
        }else{
            cout << startP << "-" << i << ":" << dist[i] << endl;
            printBestWay(qianQu, i, startP);
        }
    }
    // 不要全部复制输入
    return 0;
}