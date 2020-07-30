#include "高并发服务器顺序表的应用_顺序表.h"

void Timestamp_example();//时间戳示例

void print_the_timeout_order_table(const ssqlist<timeDimension> &tlist);//打印超时时间顺序表

void detectionTimeout(ssqlist<timeDimension> &tlist, time_t now);//超时检测函数
int main(void) {
	//Timestamp_example();
	time_t now, end;//现在,结束
	time_t timeout_detection;//超时检测
	time(&now);//取得当前时间
	end = now + 60;//60秒后退出循环
	timeout_detection = now;
	ssqlist<timeDimension> tlist;

	//1.模拟频率限制模块通过判断分析,增加恶意连接到顺序表中
	for (unsigned int i = 0; i < 10; i++) {
		timeDimension e;
		e.fd = i;
		e.timestamp = now + 5 + 2 * i;
		tlist.Add_a_tail(e);
	}

	print_the_timeout_order_table(tlist);
	
	do {
		//Sleep(1000);//效率极低,使用此函数,整个计算机在休眠时间是干不了其它事情的
		cout << "now:" << now << endl;
		if (timeout_detection + 0.999 < now) {//1秒后执行代码块
			detectionTimeout(tlist,now);//检查超时的连接
			timeout_detection = now;//重置
		}
		
		Sleep(10);//防止cpu不断工作
		time(&now);
		
	} while (now < end);//处理一分钟
	

	system("pause");
	return 0;
}

void Timestamp_example() {//时间戳示例
	time_t  presentTime;//现在时间
	time(&presentTime);//获取现在时间
	cout << "当前时间戳 - presentTime:" << presentTime << endl;
	Sleep(2000);
	time(&presentTime);//获取时间
	cout << "两秒后的时间戳 - presentTime:" << presentTime << endl;
}

void print_the_timeout_order_table(const ssqlist<timeDimension>& tlist) {//打印超时时间顺序表
	cout << "顺序表的总空间:" << tlist.size << "\t顺序表的元素个数:" << tlist.lenth << endl;
	for (int i = tlist.head; i <= tlist.lenth - 1; i++) {
		cout << "第" << i << "个时间维度的句柄:" << tlist.elems[i].fd << "\t服务时间:" << tlist.elems[i].timestamp << endl;
		cout << "---------------------------------------------\n";
	}
	cout << endl;
}

void detectionTimeout(ssqlist<timeDimension>& tlist, time_t now) {//超时检测函数
	int fd=0, i=0;
	cout << "检查超时fd...........\n";

	for (i = 0; i < tlist.lenth; i++) {
		if (tlist.elems[i].timestamp > now) {
			continue;
		}
		//超时,清理连接
		fd = tlist.elems[i].fd;
		//关闭连接
		cout << "连接[fd:" << fd << " 已经超时,关闭连接!\n";

		//删除顺序表中的元素
		if (tlist.deleteSqlist(i+1)) {
			cout << "删除了第" << i << "个元素:";
			tlist.printff();
			//循环中,元素删除后,i继续++,会把移动到删除位置的元素跳过检测,所以需:
			if (i + 1 != tlist.head) {//因为我在顺序表中有能删除头部的功能,所以
				i--;
			}
		}
	}
}