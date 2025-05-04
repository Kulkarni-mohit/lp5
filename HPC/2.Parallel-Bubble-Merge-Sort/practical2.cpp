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

void pBubble(int array[], int n){
    //Sort odd indexed numbers
    for(int i = 0; i < n; ++i){
        #pragma omp for
        for (int j = 1; j < n; j += 2){
        if (array[j] < array[j-1])
        {
          swap(array[j], array[j - 1]);
        }
    }

    // Synchronize
    #pragma omp barrier

    #pragma omp for
    for (int j = 2; j < n; j += 2){
      if (array[j] < array[j-1])
      {
        swap(array[j], array[j - 1]);
      }
    }
  }
}

void merge(int arr[], int low, int mid, int high){
	int n1 = mid - low +1;
	int n2 = high- mid;
	
	int left[n1];
	int right[n2];
	
	for(int i = 0; i<n1; i++) left[i] = arr[low+i];
	for(int i = 0; i<n2; i++) right[i] = arr[mid+i+1];
	
	int i=0, j=0, k=low;
	while(i<n1 && j<n2){
		if (left[i]>right[j]){
			arr[k] = right[j];
			j++;
		}
		else{
			arr[k] = left[i];
			i++;
		}
		k++;
	}
	
	while(i<n1){
		arr[k] = left[i];
		i++;
		k++;
	}
	while(j<n2){
		arr[k] = right[j];
		j++;
		k++;
	}
}

void mergesort(int arr[], int low, int high){
	if (low<high){
		int mid = (low+high)/2;
		mergesort(arr,low, mid);
		mergesort(arr, mid+1, high);
		merge(arr, low, mid, high);
	}
}

void pMergeSort(int arr[], int low, int high){
	if (low<high){
		int mid = (low+high)/2;
	    #pragma omp parallel sections
		{
			#pragma omp section
			{
				pMergeSort(arr, low, mid);
			}
			#pragma omp section
			{
				pMergeSort(arr, mid+1, high);
			}
		}
		merge(arr,low,mid,high);
	}
	
}

int main(){
	int ves[1000];
	for (int i = 0; i < 1000; ++i) {
        ves[i] = rand() % 1000;
    }
	double start_time = omp_get_wtime();
	mergesort(ves,0, 1000-1);
	double end_time = omp_get_wtime();
	// for(int i=0; i<10000; i++)
	// 	cout<<ves[i]<<" ";
	cout<<"\nTotal Time taken for sequential mergeSort"<< end_time-start_time;
	return 0;	
}