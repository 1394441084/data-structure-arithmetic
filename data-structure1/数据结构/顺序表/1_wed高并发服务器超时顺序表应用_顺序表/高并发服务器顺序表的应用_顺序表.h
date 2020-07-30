#pragma once
#include "顺序表类.h"
#include <time.h>

#define MAX_DIMENSION  MAX_SIZE_1 //最大维度(顺序表总空间)

typedef struct {//时间结构体 //进行超时管理
	int fd;	//web窗口服务句柄
	time_t timestamp;//超时-时间戳
}timeDimension;//时间维度