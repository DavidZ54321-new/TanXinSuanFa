// 给定一堆数字集合，进行哈夫曼排序
/*
1.找出最小的两个数，排序，小在左，大在右
2.相加，得出的新数放回集合
3.找出最小的两个数，如果有一个数是有“哈夫曼树”的，把另一个数放在它旁边；否则，另起一棵树。
4.重复2-3步骤，直到集合只有一个数为止
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <cstdlib> // 添加此行以支持system函数
#endif


using namespace std;

struct HNodeType{
    double weight;
    long long parent, l_child, r_child;
    string value;
    long long originalIndex;

    HNodeType(double w, long long p, long long l, long long r, long long index)
            : weight(w), parent(p), l_child(l), r_child(r), value("社会主义好"), originalIndex(index){}
    HNodeType() = default;

    void outEverything() const{
        cout << value << " " << parent << " " << l_child << " " << r_child << " " << weight << endl;
    }
};

struct HCodeType{
    string bit;
};

struct Compare {
    bool operator()(const HNodeType& a, const HNodeType& b) {
        return a.weight > b.weight; // 权值小的优先级高
    }
};


int main(){
    // 初始化数据
    long long n; // 节点数量
    cin >> n;
    HNodeType HuffNode[2*n-1]; // 链条数量
    for (long long i = 0; i < 2*n-1; i++) {
        HuffNode[i] = HNodeType(INT_MAX, -1, -1, -1, i); // 使用构造函数初始化
        // 权值，双亲，左孩子，右孩子
    }
    // 使用优先队列
    priority_queue<HNodeType, vector<HNodeType>, Compare> pq;
    // 输入具体值，权重，文本
    string v;
    double w;
    for (long long i = 0; i < n; i++) {
        cin >> w >> v;
        HuffNode[i].weight = w;
        HuffNode[i].value = v;
    }
#ifdef _WIN32
    system("chcp 65001");
#endif
    // 哈夫曼算法
    long long i, k;
    HNodeType l_node = HNodeType();
    HNodeType r_node = HNodeType();
    for (i = n; i < 2*n-1; i++){
        // 从优先队列中取出两个权值最小的节点
        l_node.originalIndex = -1;
        r_node.originalIndex = -1;
        for (k = 0; k <= i-1; k++){
            if (HuffNode[k].parent == -1){ // 要没父母的点
                pq.emplace(HuffNode[k]); // 优先队列
            }
        }
        l_node = pq.top();pq.pop(); // 提取最前面的，并且删掉
        r_node = pq.top();pq.pop();
        HuffNode[l_node.originalIndex].parent = i;
        HuffNode[r_node.originalIndex].parent = i; // 它们的共同父母
        HuffNode[i].weight = l_node.weight + r_node.weight; // 第i格，为它们的父母安家，设置父母的权重为孩子们的权重和
        HuffNode[i].l_child = l_node.originalIndex; // 父母的小孩
        HuffNode[i].r_child = r_node.originalIndex; // 父母的大孩
        std::priority_queue<HNodeType, std::vector<HNodeType>, Compare>().swap(pq);//清除队列，重新开始
    }
    // 输出哈夫曼树结果
    for (long long zcw = 0; zcw < 2*n-1; zcw++){
        HuffNode[zcw].outEverything();
    }
    // 编码
    HCodeType hct[n];
    long long index;
    for (long long lxy = 0; lxy < n; lxy++){
        HCodeType hcd;//一个单例
        HNodeType par = HNodeType(0,0,0,0,0);//一个单例
        index = HuffNode[lxy].originalIndex;//计算第lxy个的编码
        // 寻根问祖，小孩子找爸妈，追溯到开拓者（没有父母）为止
        while(par.parent != -1){
            // 从第0个一直往后找，找到自己的父母为止
            for (long long jzn = 0; jzn < 2*n-1; jzn++){
                if (HuffNode[jzn].l_child == index){
                    // 发现自己是父母的小孩，在单例+0
                    hcd.bit += '0';
                    index = HuffNode[jzn].originalIndex;
                    par = HuffNode[jzn];
                    break;
                }else if(HuffNode[jzn].r_child == index){
                    // 发现自己是父母的大孩，在单例+1
                    hcd.bit += '1';
                    index = HuffNode[jzn].originalIndex;
                    par = HuffNode[jzn];
                    break;
                }
            }
        }
        // 处理结果
        reverse(hcd.bit.begin(),hcd.bit.end()); // 反转字符串
        hct[lxy] = hcd; // 把单例安置在第lxy个格子里
    }
    // 输出编码结果
    for (i = 0; i < n; i++){
        cout << HuffNode[i].value << ":" << hct[i].bit << endl;
    }
    return 0;
}
