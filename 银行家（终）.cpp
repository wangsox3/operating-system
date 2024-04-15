#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#define true 1
#define false 0

char NAME[100]= {0}; //��Դ������
int Max[100][100]= {0}; //����������
int Allocation[100][100]= {0}; //ϵͳ�ѷ������
int Need[100][100]= {0}; //����Ҫ��Դ����
int Available[100]= {0}; //������Դ����
int Request[100]= {0}; //������Դ����
int Work[100]= {0}; //���ϵͳ���ṩ��Դ��
int Finish[100]= {0}; //���ϵͳ�Ƿ����㹻����Դ�������������

int M=100;//���̵������
int N=100;//��Դ�������

///*�ж�������ĸ�����Դ�Ƿ���������Ҫ����Դ������������������Դ����*/
void requestComToNeed(int i) {
	int j;
	for(j=0; j<N; j++) { //�ӵ�һ����Դ��ʼ�ж�
		if(Request[j]<=Need[i][j])
			continue;//�������Ҫ�󣬾ͼ���
		else {
			printf("����Ҫ����Դ���Ѿ��������������ĵ����ֵ!!\n"); //������������
			exit(0);//�˳�����
		}
	}
}

/*�ж�������ĸ�����Դ�Ƿ�����С��ϵͳ���еĸ�����Դ����Ŀ*/
void requestComToAvail() {
	int j;
	for(j=0; j<N; j++) { //�ӵ�һ����Դ��ʼ�ж�
		if(Request[j]<=Available[j])
			continue;	//�������Ҫ��ͼ���
		else {
			printf("�����㹻��Դ���䣡\n");//�����������
			exit(0);
		}
	}
}

/*ϵͳ�����������Դ���������i֮�󣬽����̵ĸ�����Դ���и��£��ı���Դ��*/
void updateResource(int i) {
	int j;
	for(j=0; j<N; j++) { //�ӵ�һ����Դ��ʼ����
		Available[j]-=Request[j];
		Allocation[i][j]+=Request[j];
		Need[i][j]-=Request[j];
//		-------------	printf("%d  %d  %d\n",Available[j],Allocation[i][j],Need[i][j]);
	}
}

int safetyTest() {
	int j,i;
	int pre_count=1,post_count=0;

	for(j=0; j<M; j++)	//��ʼʱFinish�ĸ�ֵ����ֵfalse
		Finish[j]=false;
	for(j=0; j<N; j++) //��ʼʱWork=Available
		Work[j]=Available[j];
	while(pre_count!=post_count) {
		post_count=pre_count;
		for(i=0; i<M; i++) {
			if(Finish[i]==false) { //�������iδ���и�����Դ����
				for(j=0; j<N; j++) {
					//=====================printf("%d  %d!!\n",Need[i][j],Work[j]);
					if(Need[i][j]<=Work[j])
						continue;
					else
						break;
				}

				if(j==N) { //�������i����Ҫ�ĸ�����Դ��������ϵͳ������Դ
					for(j=0; j<N; j++) {
						Work[j]=Work[j]+Allocation[i][j];
						Finish[i]=true;
						pre_count++;
					}
				}
			}
		}
	}
	//�ж�Finish[i]�Ƿ�Ϊtrue��Ҳ�������н����Ƿ��ѷ�����Դ
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
	/* mΪ���̸�����������������nΪ��Դ���࣬������������*/
	int i,j,m,n;
	int number,flag;
	char name;//������Դ����
	int temp[100]= {0}; //ͳ���Ѿ��������Դ
	//����ϵͳ��Դ��Ŀ������Դ���Ը���
	printf("ϵͳ������Դ����Ϊ:");
	scanf("%d",&n);
	N=n;
	for(i=0; i<n; i++) {
		printf("��Դ%d������:",i);
		fflush(stdin);  //������������������ַ���ע���������#include<stdlib.h>ͷ�ļ�
		scanf("%c",&name);
		NAME[i]=name;
		printf("��Դ%c�ĳ�ʼ����Ϊ:",name);
		scanf("%d",&number);
		Available[i]=number;
	}

	//����������������̵�����������
	printf("\n��������̵�����:");
	scanf("%d",&m);
	M=m;
	printf("����������̵������������ֵ[Max]:\n");
	do {
		flag = false;
		for(i=0; i<M; i++)
			for(j=0; j<N; j++) {
				scanf("%d",&Max[i][j]);
				if(Max[i][j]>Available[j])
					flag = true;
			}
		if(flag)
			printf("��Դ�������������ϵͳ����Դ�����������������!\n");
	} while(flag);


	//����������Ѿ��������Դ��������û���Ҫ����Դ��
	do {
		flag=false;
		printf("������������Ѿ��������Դ��[Allocation]:\n");
		for(i=0; i<M; i++) {
			for(j=0; j<N; j++) {
				scanf("%d",&Allocation[i][j]);
				if(Allocation[i][j]>Max[i][j])
					flag=true;
				Need[i][j]=Max[i][j]-Allocation[i][j];
				temp[j]+=Allocation[i][j];//ͳ���Ѿ���������̵���Դ��Ŀ
			}
		}
		if(flag)
			printf("�������Դ���������������������!\n");
	} while(flag);

	//���ϵͳ�п����õ���Դ��
	for(j=0; j<N; j++)
		Available[j]=Available[j]-temp[j];
}

void showdata() {
	int i,j;
	printf("*************************************************************\n");
	printf("ϵͳĿǰ���õ���Դ[Available]:\n");
	for(i=0; i<N; i++)
		printf("%c  ",NAME[i]);
	printf("\n");
	for(j=0; j<N; j++)
		printf("%d  ",Available[j]);
	printf("\n");
	printf("ϵͳ��ǰ����Դ����������£�\n");
	printf("            Max   	 Allocation    Need\n");
	printf("������      ");
	//����������ͬ�е���Դ����Max��Allocation��Need�·ֱ��Ӧ
	for(j=0; j<3; j++) {
		for(i=0; i<N; i++)
			printf("%c  ",NAME[i]);
		printf("     ");
	}
	printf("\n");
	//���ÿ�����̵�Max��Allocation��Need
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
	/*�����i������������ĸ�����Դ����Ŀ��*/
	printf("�������ĸ���������������Դ(1-%d):\n",M);
	fflush(stdin);
	scanf("%d",&i);
	printf("�����%d������������ĸ�����Դ����Ŀ:\n",i);
	i-=1;
	for(int x=0; x<N; x++) {
		scanf("%d",&Request[x]);
	}
	requestComToNeed(i);
	requestComToAvail();
	updateResource(i);
	stat=safetyTest();
	if(stat==true)//��ȫ����ȫ����˵��ϵͳ���ڰ�ȫ״̬
		printf("ϵͳ���ڰ�ȫ״̬���ɽ���Դ���������%d\n",i);
	else
		printf("ϵͳ���ڲ���ȫ״̬��������Դ��������!!\n");
	exit(0);
}

