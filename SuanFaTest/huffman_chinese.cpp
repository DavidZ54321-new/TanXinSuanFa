// 给定一堆数字集合，进行哈夫曼排序
/*
1. 找出最小的两个数，排序，小在左，大在右
2. 相加，得出的新数放回集合
3. 找出最小的两个数，如果有一个数是有“哈夫曼树”的，把另一个数放在它旁边；否则，另起一棵树。
4. 重复2-3步骤，直到集合只有一个数为止
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <codecvt>

#ifdef _WIN32
#include <cstdlib> // 添加此行以支持system函数
#endif

using namespace std;

struct HNodeType {
    double weight;
    long long parent, l_child, r_child;
    string value;
    long long originalIndex;

    HNodeType(double w, long long p, long long l, long long r, long long index)
            : weight(w), parent(p), l_child(l), r_child(r), value("解放！！！"), originalIndex(index) {}
    HNodeType() = default;

    void outEverything() const {
        cout << value << " " << parent << " " << l_child << " " << r_child << " " << weight << endl;
    }
};

struct HCodeType {
    string bit;
};

struct Compare {
    bool operator()(const HNodeType& a, const HNodeType& b) {
        return a.weight > b.weight; // 权值小的优先级高
    }
};

int main() {
#ifdef _WIN32
    system("chcp 65001"); // 更改控制台编码为 UTF-8
#endif

    // 设置为支持中文的 locale
    setlocale(LC_ALL, "");
    wcout.imbue(locale(""));
    wcin.imbue(locale(""));

    // 初始化数据
    long long n;
    wcout << L"请输入节点数量: ";
    wcin >> n;

    HNodeType HuffNode[2 * n - 1];
    for (long long i = 0; i < 2 * n - 1; i++) {
        HuffNode[i] = HNodeType(INT_MAX, -1, -1, -1, i); // 使用构造函数初始化
    }

    // 使用优先队列
    priority_queue<HNodeType, vector<HNodeType>, Compare> pq;

    // 输入具体值
    wstring v; // 改为使用 wstring 以处理宽字符
    double w;
    for (long long i = 0; i < n; i++) {
        wcout << L"请输入权值和字符串: ";
        wcin >> w >> v; // 使用 wcin 读取宽字符串
        HuffNode[i].weight = w;

        // 将 wstring 转换为 string
        HuffNode[i].value = string(v.begin(), v.end());
    }

    // 哈夫曼算法
    long long i, k;
    HNodeType l_node = HNodeType();
    HNodeType r_node = HNodeType();
    for (i = n; i < 2 * n - 1; i++) {
        // 从优先队列中取出两个权值最小的节点
        l_node.originalIndex = -1;
        r_node.originalIndex = -1;

        // 清空优先队列
        while (!pq.empty()) {
            pq.pop();
        }

        for (k = 0; k <= i - 1; k++) {
            if (HuffNode[k].parent == -1) { // 要没父母的点
                pq.emplace(HuffNode[k]);
            }
        }

        l_node = pq.top(); pq.pop();
        r_node = pq.top(); pq.pop();
        HuffNode[l_node.originalIndex].parent = i;
        HuffNode[r_node.originalIndex].parent = i;
        HuffNode[i].weight = l_node.weight + r_node.weight;
        HuffNode[i].l_child = l_node.originalIndex;
        HuffNode[i].r_child = r_node.originalIndex;
    }

    // 输出哈夫曼树结果
    for (long long zcw = 0; zcw < 2 * n - 1; zcw++) {
        HuffNode[zcw].outEverything();
    }

    // 编码
    HCodeType hct[n];
    long long index;
    for (long long lxy = 0; lxy < n; lxy++) {
        HCodeType hcd;
        HNodeType par = HNodeType(0, 0, 0, 0, 0);
        index = HuffNode[lxy].originalIndex;

        while (par.parent != -1) {
            for (long long jzn = 0; jzn < 2 * n - 1; jzn++) {
                if (HuffNode[jzn].l_child == index) {
                    hcd.bit += '0';
                    index = HuffNode[jzn].originalIndex;
                    par = HuffNode[jzn];
                    break;
                } else if (HuffNode[jzn].r_child == index) {
                    hcd.bit += '1';
                    index = HuffNode[jzn].originalIndex;
                    par = HuffNode[jzn];
                    break;
                }
            }
        }
        // 处理结果
        reverse(hcd.bit.begin(), hcd.bit.end());
        hct[lxy] = hcd;
    }

    // 输出编码结果
    for (i = 0; i < n; i++) {
        cout << HuffNode[i].value << ":" << hct[i].bit << endl;
    }
    return 0;
}
