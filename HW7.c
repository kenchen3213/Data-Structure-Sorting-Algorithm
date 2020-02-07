#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int *Random_data(int n){
	int i, size, *a;
	srand(time(NULL));
	size=n+1;
	a=malloc(sizeof(int)*size);
	for (i=1; i<=n; i++){
		a[i]=rand()%9999+1;
	}
	return a;
}
void Show_data(int *a, int n){
	int i;
	for (i=1; i<=n; i++){
		printf("%d\t",a[i]);
	}
	printf("\n");
}
void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void SelectionSort(int *a, int n){
	//O(n^2)
	int i, j, k, temp;
	for (i=1; i<=n; i++){
    	j=i;
        for (k=i+1; k<=n; k++){        	
		    if(a[j]>a[k]) j=k;
		}
        swap(&a[i],&a[j]);
	}
}
void InsertionSort(int *a, int n){
	//Average:O(n^2)
	//Best:O(n)
	int i, j;
	for (i=2; i<=n; i++){
		a[0]=a[i];
		j=i-1;
		while (a[0]<a[j]){
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=a[0];
	}
}
void QuickSort(int *a, const int left, const int right){
	//Average:O(nlogn)
	//Worst:O(n^2)
	int i, j, pivot;
	if (left<right){
		i=left;
		j=right+1;
		pivot=a[left];
		while (i<j){
			i++;
			while (a[i]<pivot) i++;
			j--;
			while (a[j]>pivot) j--;
			if (i<j) swap(&a[i],&a[j]);
		}
		swap(&a[left],&a[j]);
		QuickSort(a,left,j-1);
		QuickSort(a,j+1,right);
	}
}
void Merge(int *a, const int left, const int mid, const int right){
	const int Max=100000;
	int i, idxleft=0, idxright=0;
	int leftsub[mid-left+2];
	int rightsub[right-mid+1];
	for (i=0; i<mid-left+2; i++) {   
	    if (i==(mid-left+1)) leftsub[i]=Max;
	    else leftsub[i]=a[i+left];
	    
    }
	for (i=0; i<right-mid+1; i++){    
	    if (i==(right-mid)) rightsub[i]=Max;
	    else rightsub[i]=a[i+mid+1];
    }
    for (i=left; i<=right; i++){
    	if (leftsub[idxleft]<=rightsub[idxright]){
    		a[i]=leftsub[idxleft++];
		}
		else {
			a[i]=rightsub[idxright++];
		}
	}
}
void MergeSort(int *a, const int left, const int right){
	//O(nlogn)
	if (left<right){
		int mid=(left+right)/2;
		MergeSort(a, left, mid);
		MergeSort(a, mid+1, right);
		Merge(a, left, mid, right);
	}
}
void MaxHeapify(int *a, const int idxroot, const int heapsize){
	int root=a[idxroot], j;
	for (j=2*idxroot; j<=heapsize; j*=2){
		if (j<heapsize && a[j]<a[j+1]) j++;
		if (root>=a[j]) break;
		a[j/2]=a[j]; 
	}
	a[j/2]=root;
}
void HeapSort(int *a, const int n){
	//O(nlogn)
	int i;
	for (i=n/2; i>=1; i--){
		MaxHeapify(a, i, n);
	}
	for (i=n-1; i>=1; i--){
		swap(&a[1],&a[i+1]);
		MaxHeapify(a, 1, i);
	}
}
void RadixSort(int *a, const int n, const int r){
	//O((n+r)log(r)k)
	int bucket[10][n], order[10];
	int i, j, k, lsd;
	for (i=0; i<10; i++){
		order[i]=0;
	}
	for (i=0; i<10; i++){
		for (j=0; j<n; j++){
			bucket[i][j]=0;
		}
	}
	i=1; 
	while (i<=pow(10,r-1)){
		for (j=1; j<=n; j++){
			lsd=((a[j]/i)%10);
			bucket[lsd][order[lsd]]=a[j];
			order[lsd]++;
		}
		int idxdata=1;
		for (j=0; j<10; j++){
			if (order[j] != 0){
				for (k=0; k<order[j]; k++){
					a[idxdata++]=bucket[j][k];
					bucket[j][k]=0;
				}
			}	
			order[j]=0;
		}
		i*=10;
	}
}
int main(void)
{
	int i, *data, N=100000;
    data=Random_data(N);
    QuickSort(data,1,N);
	Show_data(data,N);
	free(data);
	return 0;
 } 
