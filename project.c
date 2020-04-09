#include<stdio.h>
#define true 1
#define false 0
#define processNum 5
#define resourceNum 3
#define MAXINT 9999
typedef int bool;

int available[resourceNum] = { 3,3,2 };
int maxRequest[processNum][resourceNum] = { 7,5,3,3,2,2,9,0,2,2,2,2,4,3,3 };
int allocation[processNum][resourceNum] = { 0,1,0,2,0,0,3,0,2,2,1,1,0,0,2 };
int need[processNum][resourceNum] = { 7,4,3,1,2,2,6,0,0,0,1,1,4,3,1 };
bool Finish[processNum];
int safeSeries[processNum] = { MAXINT, MAXINT , MAXINT , MAXINT , MAXINT };
int request[resourceNum];

void Init()
{
	int i, j;
	printf("Enter the number of process and resource\n");
	//scanf("%d %d",&processNum,&resourceNum);
	printf("Enter the number of current uasble resource\n");
	for (i = 0; i < resourceNum; i++) {
		scanf("%d", &available[i]);
	}
	printf("Enter max require matrix\n");
	for (i = 0; i < processNum; i++) {
		for (j = 0; j < resourceNum; j++) {
			scanf("%d", &maxRequest[i][j]);
		}
	}
	printf("Enter allocate matrix\n");
	for (i = 0; i < processNum; i++) {
		for (j = 0; j < resourceNum; j++) {
			scanf("%d", &allocation[i][j]);
		}
	}
	printf("Enter current matrix\n");
	for (i = 0; i < processNum; i++) {
		for (j = 0; j < resourceNum; j++) {
			scanf("%d", &need[i][j]);
		}
	}
}

void showInfo()
{
	int i, j;
	printf("Current resource remaining: ");
	for (j = 0; j < resourceNum; j++) {
		printf("%d ", available[j]);
	}
	printf("\n");
	printf(" PID\t Max\t\tAllocation\tNeed\n");
	for (i = 0; i < processNum; i++) {
		printf(" P%d\t", i);
		for (j = 0; j < resourceNum; j++) {
			printf("%d ", maxRequest[i][j]);
		}
		printf("\t\t");
		for (j = 0; j < resourceNum; j++) {
			printf("%d ", allocation[i][j]);
		}
		printf("\t\t");
		for (j = 0; j < resourceNum; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
}

void SafeInfo(int *work, int i)
{
	int j;
	printf(" P%d\t", i);
	for (j = 0; j < resourceNum; j++) {
		printf("%d ", work[j]);
	}
	printf("\t\t");
	for (j = 0; j < resourceNum; j++) {
		printf("%d ", need[i][j]);
	}
	printf("\t ");
	for (j = 0; j < resourceNum; j++) {
		printf("%d ", allocation[i][j]);
	}
	printf("\t\t");
	for (j = 0; j < resourceNum; j++) {
		printf("%d ", allocation[i][j] + work[j]);
	}
	printf("\n");
}

bool isSafe()
{
	int i, j, k, flag, temp0;
	int trueFinished = 0;
	int work[resourceNum];
	for (i = 0; i < resourceNum; i++) {
		work[i] = available[i];
	}

	for (i = 0; i < processNum; i++) {
		Finish[i] = false;
	}
	i = 0;
	int temp = 0;
	while (trueFinished != processNum) {
		int j = 0;
		if (Finish[i] != true) {
			for (j = 0; j < resourceNum; j++) {
				if (need[i][j] > work[j]) { break; }
			}
		}
		if (j == resourceNum) {
			Finish[i] = true;
			SafeInfo(work, i);
			for (k = 0; k < resourceNum; k++) {
				work[k] += allocation[i][k];
			}
			int k2;
			safeSeries[trueFinished++] = i;
		}
		i++;
		if (i >= processNum)
		{
			if (flag == 0)
			{
				temp = trueFinished;
				temp0 = trueFinished;
			}
			i = i % processNum;
			if (flag == 1) {
				temp = trueFinished;
				if (temp == temp0)
					break;
				else
					temp0 = temp;
			}
			flag = 1;
		}
		temp = trueFinished;
	}

	if (trueFinished == processNum) {
		printf("\nsystem safe! \n\nThe security sequence is! ");
		for (i = 0; i < processNum; i++) {
			printf("%d ", safeSeries[i]);
		}
		return true;
	}
	printf("******system unsafe! ******\n");
	return false;
}


int main()
{
	int i, j, curProcess;
	int wheInit = 0;
	printf("Use built-in data? 0 Yes, 1 No: ");
	scanf("%d", &wheInit);
	if (wheInit)
		Init(); 
	printf("---------------------------------------------------------\n");
	showInfo();
	printf("\nSystem security analysis\n");
	printf(" PID\t Work\t\tNeed\tAllocation\tWork+Allocation\n");
	isSafe();
	while (true) 
	{ 
		printf("\n---------------------------------------------------------\n");
		printf("\nEnter the process to assign (999 to exit): ");
		scanf("%d", &curProcess);
		printf("\nEnter resources to assign to process P%d: ", curProcess);
		if (curProcess == 999)
			break;
		for (j = 0; j < resourceNum; j++) 
		{
			scanf("%d", &request[j]);
		}
		for (j = 0; j < resourceNum; j++) {
			if (request[j] <= need[curProcess][j])continue;
			else { printf("ERROR! \n"); break; }
		}
		if (j == resourceNum) {
			for (j = 0; j < resourceNum; j++) {
				if (request[j] <= need[curProcess][j])continue;
				else { printf("Insufficient resources, waiting! \n"); break; }
			}
			if (j == resourceNum) {
				for (j = 0; j < resourceNum; j++) {
					available[j] -= request[j];
					allocation[curProcess][j] += request[j];
					need[curProcess][j] -= request[j];
				}
				printf("\nSystem security analysis\n");
				printf(" PID\t Work\t\tNeed\tAllocation\tWork+Allocation\n");
				if (isSafe()) {
					printf("allocation success! \n");
					showInfo();
				}
				else {
					for (j = 0; j < resourceNum; j++) {
						available[j] += request[j];
						allocation[curProcess][j] -= request[j];
						need[curProcess][j] += request[j];
					}
					printf("allocation failed! \n");
					showInfo();
				}
			}
		}
	}
}
