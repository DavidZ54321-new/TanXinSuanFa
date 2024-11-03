#include <iostream>
#include <algorithm>
using namespace std;

long long findIndex(double element, double array[], long long array_len){
    for (int i = 0; i < array_len; i++){
        if (element == array[i]){
            return i+1;
        }
    }
    return -1;
}

int main() {
    // 定义货物数量，船的最高载重
    long long huoWuN;
    double zaiZhong;
    cin >> huoWuN >> zaiZhong;

    // 定义货物清单，两份，第一份是排序的，第二份是原始的
    double huoWuWeight[huoWuN];
    double huoWuWeight_raw[huoWuN];
    double sum = 0; // 船上载重
    long long out; // 最多携带多少货物

    // 定义每个货物的重量
    for (int i = 0; i < huoWuN; i++){
        cin >> huoWuWeight[i];
        huoWuWeight_raw[i] = huoWuWeight[i];
    }

    // 货物重量从小到大排列
    sort(huoWuWeight, huoWuWeight+huoWuN);

    // 筛选，从最小的开始，一直往后面“装”，直到装不下为止
    for (long long i = 0; ; i++){
        if (sum >= zaiZhong){
            if(sum == zaiZhong){ // 刚刚好
                out = i;
                break;
            }else{ // 多一个就不行了
                out = i-1;
                break;
            }
        }
        sum += huoWuWeight[i];
    }

    cout << "load:" << out << endl; // 计算结果

    for (long long i = 0 ; i < out ; i++){
        cout << findIndex(huoWuWeight[i],huoWuWeight_raw,huoWuN) << endl;
    }
    return 0;
}
