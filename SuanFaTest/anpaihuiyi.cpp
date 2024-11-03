#include <iostream>
#include <algorithm>

using namespace std;

class Meeting {
public:
    long long meetingIndex;
    long long startTime; // 如果结束时间相等，以开始时间从大到小（选择最迟的开始）
    long long endTime; // 以结束时间为准，从小到大（选择最早的结束）
};

bool compareMeetingTime(Meeting meet1, Meeting meet2){
    if (meet1.endTime == meet2.endTime){
        return meet1.startTime > meet2.startTime;
    }
    return meet1.endTime < meet2.endTime;
}

int main(){
    // 初始化“三属性”
    long long sT,eT;
    // 定义多少个会议
    long long meetNum;
    cin >> meetNum;
    // 创建会议列表
    Meeting meetList[meetNum+10];
    // 循环填入会议信息
    for (long long i = 0; i < meetNum; i++){
        cin >> sT >> eT;
        meetList[i].meetingIndex = i+1;
        meetList[i].startTime = sT;
        meetList[i].endTime = eT;
    }
    //填完了，开始整理
    sort(meetList,meetList+meetNum, compareMeetingTime);
    //开始挑
    long long last = meetList[0].endTime;
    long long choose = 1;
    cout << meetList[0].meetingIndex << endl;

    for(long long i = 0; i < meetNum; i++){
        if (meetList[i].startTime >= last){ //满足“开始大于结束”就选它
            last = meetList[i].endTime;
            cout << meetList[i].meetingIndex << endl;
            choose++;
        }
    }
    cout << choose;
    return 0;
}