#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int len){
	for(int i=0; i<len ; i++){
		for(int j=0; j<len-i-1 ; j++){
			if (arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
		}
	}
}

void parallelBubble(int arr)

int main(){
	int ves[] = {5,4,2,8,9,7};
	bubbleSort(ves, 6);
	for(int i=0; i<sizeof(ves)/sizeof(ves[0]); i++)
		cout<<ves[i]<<" ";
	return 0;
	
}