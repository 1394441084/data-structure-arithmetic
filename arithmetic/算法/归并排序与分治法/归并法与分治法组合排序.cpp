#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void mergeAdd_demo(int arr[], int left, int mid, int right){ 
	int temp[64]={0}; 
	int i = left; //指向左边数组最小的元素位置
	int j = mid; //指向右边数组最小的元素位置
	int k = 0; //临时数组的下标 
	
	while( i<mid && j<=right){ 
		if(arr[i]<arr[j]){ 
			temp[k++] = arr[i++];
		}else { 
			temp[k++] = arr[j++];
		} 
	}
	
	while(i< mid){
		temp[k++] = arr[i++];
	}
	
	while(j<= right){
		temp[k++] = arr[j++];
	}

	//把 temp 中的内容拷贝到 arr 数组中 
	memcpy(arr+left, temp, sizeof(int) * (right - left + 1)); 
}

//归并法(需排序数组,数组起始位置,分组定界点,数组终点位置,存放排序结果的临时数组)
void mergeAdd(int arr[], int left, int mid, int right, int *temp){
	//int temp[64]={0};
	int i = left; //指向左边数组最小的元素位置 
	int j = mid; //指向右边数组最小的元素位置 
	int k = left; //临时数组的下标 

	while( i<mid && j<=right){ //起始<定界点 && 定界点<=终点
		if(arr[i]<arr[j]){ //左边组的第i个元素 < 右边组的第j个元素 
			temp[k++] = arr[i++];//右边大就将左边组的那个元素放进临时数组里,然后左下一位,临时数组下个位置等待
		}else {
			temp[k++] = arr[j++];//右元素放进临时数组,跳出循环继续当前左元素比对下个右元素,如果下个右元素胜利,那此左元素进到临时数组
		} 
	}
	
	//上面执行行完了,可能会遇到左组是2个元素,右组是5个元素,那么5-2=3,还剩3个元素没有进到临时数组
	while(i< mid){//将剩余元素放进临时数组里
		temp[k++] = arr[i++]; 
	}
	
	while(j<= right){ 
		temp[k++] = arr[j++];
	}
	
	//将临时数组的内容拷贝到需排序数组里,归并法实现完结
	//由于分治需要做了处理(左值+起点,右值+起点,拷贝多少字节) //这样就不会将其它数据覆盖掉
	memcpy(arr+left, temp+left, sizeof(int) * (right - left + 1));//把 temp 中的内容拷贝到 arr 数组中 
}

//分治归并(需排序数组,数组起始位置,数组终点位置,存放排序结果的临时数组)
void mergeSort(int arr[], int left, int right, int *temp){//归并排序结合分治理念
	int mid = 0;
	if(left < right){
		mid = left +(right - left)/2;//分组定界 //0+(7-0)/2=3 //

		//经过定界分成了两组
		mergeSort(arr, left, mid, temp);//0-3  左边组 //里面又会分为两组0-1和2-3然后再里面分为左0右1和左2右3的两个空间组
		mergeSort(arr, mid + 1, right, temp);//4-7 右边组

		//经过前面的分治归并后两组都为有序的了,接下来就归并了
		mergeAdd(arr, left, mid + 1, right, temp);//单归并
	} 
}

int main(void){ 
	int beauties[]={10, 11, 12, 13, 2, 4, 5, 8}; 
	int len = sizeof(beauties)/sizeof(beauties[0]);//数组元素个数
	int *temp = new int[len];//临时数组暂存归并好的数组
	//int mid = len/2; 
	mergeSort(beauties, 0, len - 1, temp);
	//mergeAdd(beauties, 0, mid, len-1, temp); 
	printf("执行归并大法后:\n"); 
	for(int i=0; i<len; i++){
		printf("%d ", beauties[i]);
	}

	system("pause"); 
	return 0; 
}

//总结:利用归并的分组排序规律进行递归细分,那么分治法大展身手.栈空间不足,可以尝试用循环或者是跳转进行优化.
/*
*在处理大文件比对如100G的文件数据,可电脑内存不能存放如此多,那么就需分化如50G,50G,
*如此细分下去,直到能在电脑上进行比对.

*细节:
**先利用分治法使文件细分下去,成为了一颗树,然后文件就可以使用归并了.
**因为归并的原理,所以自下往上归并而去.
***归并细节:
***如:比对的是手机号码,13245678954,13548796541,那么先清空父文件,左子文件和右子文件,
***各取一串手机号码进行电脑内比较,根据需求如从小排到大,就13245678954先写入父文件,
***然后左子文件中再取一串手机号跟右子节点的13548796541比较.

***为保障电脑突然死机从而造成数据丢失,对文件操作时使用先写入父文件再删除已进入父文件的数据.
*/