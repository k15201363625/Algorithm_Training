#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//两种思路：【1】枚举应该讲当前物品填方到什么位置
//         【2】枚举当前位置应该放置什么物品
//【1】可能性太多 即便从大的开始搜索
//【2】只有少量物品 可以
//dfs加回溯 只需要存储当前填充状况暴力判断即可