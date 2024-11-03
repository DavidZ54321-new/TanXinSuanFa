#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Good{
private:
    double weight;
    double value;
    double xingJiaBi = value / weight;
public:
    Good(double value,double weight):value(value),weight(weight){}

    [[nodiscard]] double getXJB() const{
        return xingJiaBi;
    }
    [[nodiscard]] double getWeight() const{
        return weight;
    }
    [[nodiscard]] double getValue() const{
        return value;
    }
};

bool compareWoodXJB(Good a, Good b){
    return a.getXJB() > b.getXJB();
}

int main(){
    // 定义货物数量，船最大载重
    long long good_number;
    double boat_max_weight;
    cin >> good_number >> boat_max_weight;

    // 定义每个货物的重量
    double good_weight;
    double good_value;
    vector<Good> good_list;
    for (long long i = 0; i < good_number; i++){
        cin >> good_value >> good_weight;
        good_list.emplace_back(good_value,good_weight);
    }

    // 按照性价比排序
    sort(good_list.begin(),good_list.end(), compareWoodXJB);

    // 按照性价比装货物，定义一个当前载重变量
    double sum = 0;
    double out = 0;
    for (long long i = 0; i < good_number; i++){
        if (sum > boat_max_weight){
            sum -= good_list[i-1].getWeight();
            out -= good_list[i-1].getValue();
            double last_weight = boat_max_weight - sum;
            out += last_weight*good_list[i-1].getXJB();
            break;
        }else if (sum == boat_max_weight){
            break;
        }
        sum += good_list[i].getWeight();
        out += good_list[i].getValue();
    }
    cout << "load value:" << out << endl;

    return 0;
}