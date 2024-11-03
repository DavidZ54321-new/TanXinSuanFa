#include <queue> // 引入优先队列的头文件
#include <iostream> // 引入输入输出流的头文件
#include <cstring> // 引入字符串处理的头文件
using namespace std; // 使用标准命名空间

// 定义全局常量
const int N = 100; // 定义最大城市数
const int INF = 1e7; // 定义无穷大的值
int map[N][N], dist[N], n, m; // 声明邻接矩阵map、距离数组dist、城市数n和道路数m
int flag[N]; // 声明标记数组，用于标记城市是否被访问过

// 定义“数据类”
class Node{ // 定义一个节点类用于Dijkstra算法
public:
    int u, step; // 定义城市（u）和当前距离（step）

    Node()= default; // 默认构造函数
    Node(int a, int sp){ // 带参数的构造函数
        u = a; // 初始化城市
        step = sp; // 初始化距离
    }

    // 函数重载<
    bool operator < (const Node& a)const{ // 重载小于运算符
        return step > a.step; // 优先队列按距离来比较，距离小的优先
    }
};

// Dijkstra算法
void dijkstra(int st){ // Dijkstra算法函数，参数为起始城市st
    priority_queue<Node> Q; // 声明优先队列Q，用于存储节点
    Q.emplace(st,0); // 将起始城市和距离0加入优先队列
    memset(flag,0,sizeof(flag)); // 初始化标记数组，标记城市是否被访问
    //memset() 是 C 和 C++ 语言中一个非常常用的库函数，其主要作用是将一块内存空间的内容初始化为指定的值。它通常用于初始化数组、结构体等数据结构。
    /*
    ptr: 指向要被设置值的内存块的指针。
    value: 要设置的值。注意，这个值会被转换为 unsigned char 类型，然后填充到指定的内存块中。
    num: 要设置的字节数，即要填充的内存块的大小。
     其实就是初始化一个值了，简单理解就是这样
     */
    for (int i = 1; i <= n; ++i){ // 遍历所有城市
        dist[i] = INF; // 初始化所有距离为无穷大
    }
    dist[st] = 0; // 起始城市到自身的距离为0
    while(!Q.empty()){ // 当优先队列不为空时
        Node it = Q.top(); // 获取队头为最小值的城市
        Q.pop(); // 弹出队头城市
        int t = it.u; // 获取当前城市
        if(flag[t]){ // 如果当前城市已经被访问过
            continue; // 继续下一轮循环
        }
        flag[t] = 1; // 标记当前城市为已访问
        for (int i = 1; i <= n; i++){ // 遍历所有城市
            if(!flag[i] && map[t][i]<INF){ // 如果城市i未被访问且与城市t相连
                if (dist[i] > dist[t] + map[t][i]){ // 如果通过城市t到城市i的距离更短
                    // 求当前两个点最短距离，进行松弛操作
                    dist[i] = dist[t] + map[t][i]; // 更新城市i的距离
                    Q.emplace(i, dist[i]); // 将城市i和新距离加入优先队列
                }
            }
        }
    }
}

int main(){

    // 初始化参数
    int u,v,w,st; // 声明城市u、v、边权重w和起始城市st
    cout << "Input the number of the city:" << endl; // 提示输入城市数量
    cin >> n; // 输入城市数量
    cout << "Input the road:" << endl; // 提示输入道路数量
    cin >> m; // 输入道路数量
    for(int i = 1; i <= n; i++){ // 初始化图的邻接矩阵
        for(int j = 1; j <= n; j++){
            map[i][j] = INF; // 将邻接矩阵所有值初始化为无穷大
        }
    }
    cout << "输入u,v的路线及w" << endl; // 提示输入道路的起点u、终点v和u，v距离
    while(m--){ // 循环输入m条道路
        cin >> u >> v >> w; // 输入起点u、终点v和距离w
        map[u][v] = min(map[u][v],w); // 将邻接矩阵中记录的道路距离取最小值
    }
    cout << "请输入小明所在的位置：" << endl; // 提示输入小明的起始位置
    cin >> st; // 输入小明的起始城市

    // 开始计算
    dijkstra(st); // 调用Dijkstra算法计算最短路径

    // 输出结果
    for(int i = 1; i <= n; i++){
        cout << st << "-----" << "local: " << i; // 输出起始城市到目标城市的路径
        if (dist[i] == INF){ // 如果目标城市不可达
            cout << "XXXXXXXXXX" << endl; // 表示无法到达
        }else{
            cout << "short:" << dist[i] << endl; // 输出从起始城市到目标城市的最短距离
        }
    }
    return 0; // 程序结束
}
