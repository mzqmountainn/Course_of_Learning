
#include <iostream>
#include <algorithm>
using namespace std;

/*
m个柜台提供服务，每个柜台给一个用户提供服务的时间是t(用数组表示每一个柜台提供服务的时间)，
问怎么排列，使得柜台给所有用户提供服务的时间最少？
*/
struct Counter {  // 描述柜台
	bool operator<(const Counter &counter) const {
		return time < counter.time;
	}
	int id; // 柜台id
	int time; // 柜台提供服务所花费的时间
};
int main()
{
	int arr[] = { 3,2,4 }; // 每一个柜台提供服务的时间
	const int m = sizeof(arr) / sizeof(arr[0]); // 柜台的数量
	int n = 15; // 办理业务的人数

	// 定义柜台信息数组，初始化柜台id和time
	Counter cons[m];
	for (int i = 0; i < m; ++i) {
		cons[i].id = i;
		cons[i].time = arr[i];
	}

	// 按照柜台提供服务的时间升序排列
	sort(cons, cons + m);

	int mintime = 0; // 记录给所有用户提供服务的最少时间
	int x[m] = { 0 }; // 记录每一个柜台安排的用户数量

	for (int i = 0; i < n; ++i) {
		// 先计算把i用户放在0号柜台的时间
		int time = cons[0].time * (x[0] + 1);   //   1 5      5 1
		// 再遍历其它的柜台，看是否可以得到更少的花费时间
		int j = 1;
		for (; j < m; ++j) {
			int t = cons[j].time * (x[j] + 1);
			if (t <= time) {  // 放在其它柜台处理时间总体更快，直接放入j柜台
				x[j]++;
				// 新添加了一个人，整体花费的时间有可能变得更长了，更新mintime
				if (t > mintime) {
					mintime = t;
				}
				break;
			}
		}
		// 最终还是放在0号柜台花费时间最少
		if (j == m) {
			x[0]++;
			// 新添加了一个人，整体花费的时间有可能变得更长了，更新mintime
			mintime = cons[0].time * x[0];
		}
	}

	cout << mintime << endl;
	for (int i = 0; i < m; ++i) {
		cout << arr[cons[i].id] << " : " << x[i] << endl;
	}

	return 0;
}