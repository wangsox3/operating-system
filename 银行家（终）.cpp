#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#define true 1
#define false 0

char NAME[100]= {0}; //资源的名称
int Max[100][100]= {0}; //最大需求矩阵
int Allocation[100][100]= {0}; //系统已分配矩阵
int Need[100][100]= {0}; //还需要资源矩阵
int Available[100]= {0}; //可用资源矩阵
int Request[100]= {0}; //请求资源向量
int Work[100]= {0}; //存放系统可提供资源量
int Finish[100]= {0}; //标记系统是否有足够的资源分配给各个进程

int M=100;//进程的最大数
int N=100;//资源的最大数

///*判断所请求的各类资源是否满足所需要的资源数不超过所宣布的资源数：*/
void requestComToNeed(int i) {
	int j;
	for(j=0; j<N; j++) { //从第一个资源开始判断
		if(Request[j]<=Need[i][j])
			continue;//如果符合要求，就继续
		else {
			printf("所需要的资源数已经超过它所宣布的的最大值!!\n"); //否则就输出错误
			exit(0);//退出程序
		}
	}
}

/*判断所请求的各类资源是否满足小于系统现有的各类资源的数目*/
void requestComToAvail() {
	int j;
	for(j=0; j<N; j++) { //从第一个资源开始判断
		if(Request[j]<=Available[j])
			continue;	//如果符合要求就继续
		else {
			printf("尚无足够资源分配！\n");//否则输出错误
			exit(0);
		}
	}
}

/*系统把所请求的资源分配给进程i之后，将进程的各个资源进行更新，改变资源数*/
void updateResource(int i) {
	int j;
	for(j=0; j<N; j++) { //从第一个资源开始更新
		Available[j]-=Request[j];
		Allocation[i][j]+=Request[j];
		Need[i][j]-=Request[j];
//		-------------	printf("%d  %d  %d\n",Available[j],Allocation[i][j],Need[i][j]);
	}
}

int safetyTest() {
	int j,i;
	int pre_count=1,post_count=0;

	for(j=0; j<M; j++)	//开始时Finish的各值都赋值false
		Finish[j]=false;
	for(j=0; j<N; j++) //开始时Work=Available
		Work[j]=Available[j];
	while(pre_count!=post_count) {
		post_count=pre_count;
		for(i=0; i<M; i++) {
			if(Finish[i]==false) { //如果进程i未进行各类资源分配
				for(j=0; j<N; j++) {
					//=====================printf("%d  %d!!\n",Need[i][j],Work[j]);
					if(Need[i][j]<=Work[j])
						continue;
					else
						break;
				}

				if(j==N) { //如果进程i所需要的各类资源都不大于系统可用资源
					for(j=0; j<N; j++) {
						Work[j]=Work[j]+Allocation[i][j];
						Finish[i]=true;
						pre_count++;
					}
				}
			}
		}
	}
	//判断Finish[i]是否都为true，也就是所有进程是否都已分配资源
	for(i=0; i<M; i++) {
		if(Finish[i]!=true)
			break;
	}

	if(i==M)
		return true;
	else
		return false;

}

void init() {
	/* m为进程个数，即矩阵行数，n为资源种类，即矩阵列数。*/
	int i,j,m,n;
	int number,flag;
	char name;//输入资源名称
	int temp[100]= {0}; //统计已经分配的资源
	//输入系统资源数目及各资源初试个数
	printf("系统可用资源种类为:");
	scanf("%d",&n);
	N=n;
	for(i=0; i<n; i++) {
		printf("资源%d的名称:",i);
		fflush(stdin);  //清空输入流缓冲区的字符，注意必须引入#include<stdlib.h>头文件
		scanf("%c",&name);
		NAME[i]=name;
		printf("资源%c的初始个数为:",name);
		scanf("%d",&number);
		Available[i]=number;
	}

	//输入进程数及各进程的最大需求矩阵
	printf("\n请输入进程的数量:");
	scanf("%d",&m);
	M=m;
	printf("请输入各进程的最大需求矩阵的值[Max]:\n");
	do {
		flag = false;
		for(i=0; i<M; i++)
			for(j=0; j<N; j++) {
				scanf("%d",&Max[i][j]);
				if(Max[i][j]>Available[j])
					flag = true;
			}
		if(flag)
			printf("资源最大需求量大于系统中资源最大量，请重新输入!\n");
	} while(flag);


	//输入各进程已经分配的资源量，并求得还需要的资源量
	do {
		flag=false;
		printf("请输入各进程已经分配的资源量[Allocation]:\n");
		for(i=0; i<M; i++) {
			for(j=0; j<N; j++) {
				scanf("%d",&Allocation[i][j]);
				if(Allocation[i][j]>Max[i][j])
					flag=true;
				Need[i][j]=Max[i][j]-Allocation[i][j];
				temp[j]+=Allocation[i][j];//统计已经分配给进程的资源数目
			}
		}
		if(flag)
			printf("分配的资源大于最大量，请重新输入!\n");
	} while(flag);

	//求得系统中可利用的资源量
	for(j=0; j<N; j++)
		Available[j]=Available[j]-temp[j];
}

void showdata() {
	int i,j;
	printf("*************************************************************\n");
	printf("系统目前可用的资源[Available]:\n");
	for(i=0; i<N; i++)
		printf("%c  ",NAME[i]);
	printf("\n");
	for(j=0; j<N; j++)
		printf("%d  ",Available[j]);
	printf("\n");
	printf("系统当前的资源分配情况如下：\n");
	printf("            Max   	 Allocation    Need\n");
	printf("进程名      ");
	//输出与进程名同行的资源名，Max、Allocation、Need下分别对应
	for(j=0; j<3; j++) {
		for(i=0; i<N; i++)
			printf("%c  ",NAME[i]);
		printf("     ");
	}
	printf("\n");
	//输出每个进程的Max、Allocation、Need
	for(i=0; i<M; i++) {
		printf(" P%d        ",i+1);
		for(j=0; j<N; j++)
			printf("%d  ",Max[i][j]);
		printf("     ");
		for(j=0; j<N; j++)
			printf("%d  ",Allocation[i][j]);
		printf("     ");
		for(j=0; j<N; j++)
			printf("%d  ",Need[i][j]);
		printf("\n");
	}
}



int main() {
	int i,stat;
	init();
	showdata();
	/*输入第i个进程所请求的各类资源的数目：*/
	printf("请输入哪个进程请求申请资源(1-%d):\n",M);
	fflush(stdin);
	scanf("%d",&i);
	printf("输入第%d个进程所请求的各类资源的数目:\n",i);
	i-=1;
	for(int x=0; x<N; x++) {
		scanf("%d",&Request[x]);
	}
	requestComToNeed(i);
	requestComToAvail();
	updateResource(i);
	stat=safetyTest();
	if(stat==true)//若全部安全，就说明系统出于安全状态
		printf("系统处于安全状态，可将资源分配给进程%d\n",i);
	else
		printf("系统处于不安全状态，本次资源分配作废!!\n");
	exit(0);
}

