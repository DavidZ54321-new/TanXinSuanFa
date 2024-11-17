#include <iostream>

const long long N = 800;

long long lianXian[N][N];
long long qianQu[N][N];
long long zuiXiaoW[N][N];

void printYouJie(long long i, long long j){
    // 自己碰自己，也就是一条边时
    if (qianQu[i][j] == 0) { return; } // 如果没有路径，也结束
    // qianQu-0 > 1 中间有点，要写
    if (qianQu[i][j]-i > 1){
        std::cout << "v[" << i << "]v[" << qianQu[i][j] << "]\n";
    }
    // n-(qianQu) = 1 故中间没点
    if (j-(qianQu[i][j]) > 1){
        std::cout << "v[" << qianQu[i][j] << "]v[" << j << "]\n";
    }
    printYouJie(i, qianQu[i][j]);
    printYouJie(qianQu[i][j], j);
}

int main(){
    long long n;
    std:: cin >> n;
    // 防止temp无法被存入，要赋值为21亿
    for (long long i = 1; i <= n; i++){
        for (long long j = 1; j <= n; j++){
            zuiXiaoW[i][j] = INT_MAX;
        }
    }
    // 初始化两点间距
    long long length;
    for (long long i = 1; i <= n; i++){
        for (long long j = i+1; j <= n; j++){
            std::cin >> length;
            lianXian[i][j] = lianXian[j][i] = length;
            zuiXiaoW[j][i] = 0;
        }
    }
    for (long long i = 1; i <= n; i++){
        for (long long j = 1; j <= n; j++){
            std::cout << lianXian[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    // 把两个数组(i,i)以及(i,i+1)变0
    for (long long i = 1; i <= n; i++){
        zuiXiaoW[i][i] = qianQu[i][i] = 0;
        zuiXiaoW[i][i+1] = qianQu[i][i+1] = 0;
    }
    // 又是李娟，罗惜元，陈智明（全算法最麻烦的傻逼）和张超为
    long long lj, lxy, zcw;
    long long temp;
    zcw = 3;
    while (zcw <= n){
        lj = 1;
        lxy = zcw;
        while (lxy <= n){
            for (long long cjm = 2; cjm <= lxy-1; cjm++){
                temp = zuiXiaoW[lj][cjm] + zuiXiaoW[cjm][lxy] + (lianXian[lj][cjm] + lianXian[lj][lxy] + lianXian[cjm][lxy]);
                if (temp < zuiXiaoW[lj][lxy]){
                    zuiXiaoW[lj][lxy] = temp;
                    qianQu[lj][lxy] = cjm;
                }
            }
            lj++;
            lxy++;
        }
        zcw++;
    }
    for (long long i = 1; i <= n; i++){
        for (long long j = 1; j <= n; j++){
            std::cout << zuiXiaoW[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (long long i = 1; i <= n; i++){
        for (long long j = 1; j <= n; j++){
            std::cout << qianQu[i][j] << " ";
        }
        std::cout << "\n";
    }
    printYouJie(1, n);
    return 0;
}