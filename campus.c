#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define NAME_SIZE 40
#define HASH_INITESIZE 80   //��ϣ��
#define HASHINCREASESIZE 40 //�������ӵĹ�ϣ��
#define NUM 10  //ǰNUM��
//��ϣ��

//��ȡ����
//������ϣ��
//�ӹ�ϣ���ȡ����
//���а�����

//ѧ�����ݽṹ
typedef struct student{     
    char name[NAME_SIZE];   //����
    int number;     //Ʊ��
    char class[10];  //�༶
    char ID[20];     //ѧ��
    char grade[10];  //�꼶
    char major[50]; //רҵ
    char honour[100];   //ͻ���¼�
    // int address;      //�ڹ�ϣ���е�λ��
}Student;
//��ϣ��
typedef struct hash{
    Student* data;      //�������ݵ�����
    int HashLength;     //��ϣ��
}Hash;
//��������
int IniteHashTable(Hash* table);                //��ʼ����ϣ��
int SearchHashTable(Hash table,char* ,int ,int* );    //ͨ��ѧ�Ų��ҽ��
int AddHashData(Hash table,Student data);       //���ϣ������������
int Vote(Hash table);                           //ͶƱ
int ShowRank(Hash table);                       //չʾ��ǰ���а�

int main(void){
    int choice;      //�û���ѡ��
    Student data;    //��������
    Hash table;      //��ϣ��
    char ID[20];
    int a;
    // Student array[HASH_INITESIZE];
    IniteHashTable(&table);

    do
    {
        printf("1.ѡ����Ϣ\n");
        printf("2.ѡ�ֵ�Ʊ��\n");
        printf("3.ͶƱ\n");
        printf("4.���а�\n");
        printf("5.�˳�ϵͳ\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            for (int i = 0; i < table.HashLength; i++)      //���
                if (table.data[i].number)
                    printf("����:%-15s ѧ��:%s  %dƱ  �꼶:%s  רҵ:%s  �༶:%s  %s\n",table.data[i].name,table.data[i].ID,
                    table.data[i].number,table.data[i].grade,table.data[i].major,table.data[i].class,table.data[i].honour);
            
            break;
        case 2:
            printf("������ѡ��ѧ��:\n");
            scanf("%s",ID);

            if (SearchHashTable(table,ID,strlen(ID),&a))
                printf("ѡ������:%s Ʊ��:%d\n",table.data[a].name,table.data[a].number);
            else
                printf("���޴���.\n");
                        
            break;
        case 3:
            Vote(table);
            break;
        case 4:
            ShowRank(table);
            break;
        case 5:
            break;
        default:
            printf("�������\n");
            break;
        }
    } while (choice != 5);
    
    return 0;
}
//��ʼ����ϣ��  Ĭ��Ʊ��(number)Ϊ0
int IniteHashTable(Hash* table){
    table->data = (Student *)malloc(HASH_INITESIZE * sizeof(Student));      //����ռ�
    if (!table->data)
        return ERROR;

    for (int i = 0; i < HASH_INITESIZE; i++)        //��ʼ����
        table->data[i].number = 0;                  //��Ʊ��Ϊ0��δռ��
    
    table->HashLength = HASH_INITESIZE;
    return OK;
}
//����ѧ��  �ڹ�ϣ���в������޶�Ӧ�ڵ�  ���� ture or false  ����� ���ؽڵ��ڹ�ϣ���е��±�
int SearchHashTable(Hash table,char* ID,int n,int* x){         //��������Ϊ  ��ϣ��  ѧ��ѧ��  ѧ�ų���  ѧ���ڹ�ϣ���е��±�
    unsigned long long a = 0;

    for (int i = 0; i < n; i++)     //ת���ַ�Ϊ����
        a += a*10 + (ID[i] - '0');
    
    a = a % table.HashLength;       //���ַ

    while (table.data[a].number)        //������a��Ľ��������������ȵĽ��  �����ͻ
    {
        int count = 0;
        for (int i = 0; i < n; i++)     //�Ƚ�
        {
            if(table.data[a].ID[i] != ID[i])        //ÿ��һ����ͬ���ַ�����һ��
                count++;
        }

        if (!count){     //count==0 �������ַ���ȫ��ͬ
            *x = a;
            return OK;
        }

        a++;
    }

    *x = -1;             //�޴˽���򷵻�-1
    return ERROR;       //û���ҵ�ѧ��������ѧ����ȫ��ȵĽ��
}
//���ϣ���������µĽ��
int AddHashData(Hash table,Student data){           //��������Ϊ  ��ϣ��  ѧ�����
    unsigned long long a = 0;

    for (int i = 0; i < strlen(data.ID); i++)     //ת���ַ�Ϊ����
        a += a*10 + (data.ID[i] - '0');
    
    a = a % table.HashLength;

    while (table.data[a].number)        //������a֮��ĵ�һ������  �����ͻ����
        a++;
    
    table.data[a] = data;
    
    return OK;
}
//��ѧ��ͶƱ  ѧ���ѱ�¼����number++ ����¼���ѧ����Ϣ����ϣ����number++
int Vote(Hash table){           //����Ϊ  ��ϣ��
    Student data;
    int a;
    int choice;

    printf("������ѡ������\n");
    scanf("%s",data.name);
    printf("������ѡ��ѧ��\n");
    scanf("%s",data.ID);

    if (SearchHashTable(table,data.ID,strlen(data.ID),&a)){     //Ԫ�ش���
        table.data[a].number++;
        printf("ͶƱ�ɹ�!\n");
    }
    else {
        printf("�޴˼�¼!\n");
        printf("\t1.������ѧ��\n");
        printf("\t2.����\n");
        printf("��ѡ�����\n");
        scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                printf("����ѧ����Ϣ��ʽ����:\n");
                printf("\t�༶:20190654\n");
                printf("\tרҵ:�������ѧ�뼼��\n");
                printf("\t�꼶:2019\n");
                printf("\tͻ���¼�:������Ա\n");
                printf("�༶:\t");
                scanf("%s",data.class);
                printf("רҵ:\t");
                scanf("%s",data.major);
                printf("�꼶:\t");
                scanf("%s",data.grade);
                printf("ͻ���¼�:\t");
                scanf("%s",data.honour);
                data.number = 1;

                AddHashData(table,data);

                break;
            case 2:
                break;
            default:
                printf("�������,���˳�\n");
                break;
            }
    }//else
    
    return OK;
}
//չʾ��ǰ���а� ʹ�ò�������
int ShowRank(Hash table){
	int a[NUM+1];                              //����һ��������ǰʮ���ڹ�ϣ���е��±�

	for(int i = 0; i < NUM; i++)     //��ʼ�� 
        a[i] = -1;
    
    for(int i = 0; i < table.HashLength; i++)        //������ϣ��
	{
		if(table.data[i].number)        //����ڵ����
		{
            int k;
			for(k = NUM-1; k >= 0; k--)               //��������
			{
				if(a[k] > -1){         //a[k]������ ��ӦֵС��Ŀǰֵ �����Ų
                    if (table.data[a[k]].number < table.data[i].number)
                        a[k+1] = a[k];
                    else           //�Ѿ�������ǰ��
                        break;
                }
			}
		   a[k+1] = i;
		}
	}

	for(int i = 0; i < NUM && a[i] > -1; i++)      //��ǰʮ�����
	    printf("ѡ������:%-15s  %dƱ\n",table.data[a[i]].name,table.data[a[i]].number);
    return OK;
}