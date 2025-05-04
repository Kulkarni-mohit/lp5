#include <iostream>
#include <omp.h>

using namespace std;

int min_val(int arr[], int n){
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0; i<n;i++){
        if(arr[i]<min_val){
            min_val = arr[i];
        }
    }
    return min_val;
}

int max_val(int arr[], int n){
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0; i<n;i++){
        if(arr[i]>max_val){
            max_val = arr[i];
        }
    }
    return max_val;
}

int sum(int arr[], int n){
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n;i++){
        sum += arr[i];
    }
    return sum;
}

int average(int arr[], int n){
    return (double)sum(arr, n) / n;
}

int main(){
    int n = 5;
    int arr[] = {1,2,3,4,5};
    cout << "The minimum value is: " << min_val(arr, n) << '\n';
    cout << "The maximum value is: " << max_val(arr, n) << '\n';
    cout << "The summation is: " << sum(arr, n) << '\n';
    cout << "The average is: " << average(arr, n) << '\n';
    return 0;
  }