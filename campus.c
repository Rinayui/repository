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
#define HASH_INITESIZE 80   //哈希表长
#define HASHINCREASESIZE 40 //单次增加的哈希表长
#define NUM 10  //前NUM名
//哈希表

//读取输入
//建立哈希表
//从哈希表读取数据
//排行榜排序

//学生数据结构
typedef struct student{     
    char name[NAME_SIZE];   //名字
    int number;     //票数
    char class[10];  //班级
    char ID[20];     //学号
    char grade[10];  //年级
    char major[50]; //专业
    char honour[100];   //突出事迹
    // int address;      //在哈希表中的位置
}Student;
//哈希表
typedef struct hash{
    Student* data;      //储存数据的数组
    int HashLength;     //哈希表长
}Hash;
//函数部分
int IniteHashTable(Hash* table);                //初始化哈希表
int SearchHashTable(Hash table,char* ,int ,int* );    //通过学号查找结点
int AddHashData(Hash table,Student data);       //向哈希表中增添数据
int Vote(Hash table);                           //投票
int ShowRank(Hash table);                       //展示当前排行榜

int main(void){
    int choice;      //用户的选择
    Student data;    //储存数据
    Hash table;      //哈希表
    char ID[20];
    int a;
    // Student array[HASH_INITESIZE];
    IniteHashTable(&table);

    do
    {
        printf("1.选手信息\n");
        printf("2.选手得票数\n");
        printf("3.投票\n");
        printf("4.排行榜\n");
        printf("5.退出系统\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            for (int i = 0; i < table.HashLength; i++)      //输出
                if (table.data[i].number)
                    printf("姓名:%-15s 学号:%s  %d票  年级:%s  专业:%s  班级:%s  %s\n",table.data[i].name,table.data[i].ID,
                    table.data[i].number,table.data[i].grade,table.data[i].major,table.data[i].class,table.data[i].honour);
            
            break;
        case 2:
            printf("请输入选手学号:\n");
            scanf("%s",ID);

            if (SearchHashTable(table,ID,strlen(ID),&a))
                printf("选手姓名:%s 票数:%d\n",table.data[a].name,table.data[a].number);
            else
                printf("查无此人.\n");
                        
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
            printf("输入错误\n");
            break;
        }
    } while (choice != 5);
    
    return 0;
}
//初始化哈希表  默认票数(number)为0
int IniteHashTable(Hash* table){
    table->data = (Student *)malloc(HASH_INITESIZE * sizeof(Student));      //申请空间
    if (!table->data)
        return ERROR;

    for (int i = 0; i < HASH_INITESIZE; i++)        //初始化表
        table->data[i].number = 0;                  //以票数为0记未占用
    
    table->HashLength = HASH_INITESIZE;
    return OK;
}
//输入学号  在哈希表中查找有无对应节点  返回 ture or false  如果有 返回节点在哈希表中的下标
int SearchHashTable(Hash table,char* ID,int n,int* x){         //参数依次为  哈希表  学生学号  学号长度  学生在哈希表中的下标
    unsigned long long a = 0;

    for (int i = 0; i < n; i++)     //转换字符为数字
        a += a*10 + (ID[i] - '0');
    
    a = a % table.HashLength;       //求地址

    while (table.data[a].number)        //查找自a起的结点有无与输入相等的结点  解决冲突
    {
        int count = 0;
        for (int i = 0; i < n; i++)     //比较
        {
            if(table.data[a].ID[i] != ID[i])        //每有一个不同的字符计数一次
                count++;
        }

        if (!count){     //count==0 该两个字符完全相同
            *x = a;
            return OK;
        }

        a++;
    }

    *x = -1;             //无此结点则返回-1
    return ERROR;       //没有找到学号与输入学号完全相等的结点
}
//向哈希表中增添新的结点
int AddHashData(Hash table,Student data){           //参数依次为  哈希表  学生结点
    unsigned long long a = 0;

    for (int i = 0; i < strlen(data.ID); i++)     //转换字符为数字
        a += a*10 + (data.ID[i] - '0');
    
    a = a % table.HashLength;

    while (table.data[a].number)        //查找自a之后的第一个零结点  解决冲突问题
        a++;
    
    table.data[a] = data;
    
    return OK;
}
//给学生投票  学生已被录入则number++ 否则录入该学生信息到哈希表再number++
int Vote(Hash table){           //参数为  哈希表
    Student data;
    int a;
    int choice;

    printf("请输入选手姓名\n");
    scanf("%s",data.name);
    printf("请输入选手学号\n");
    scanf("%s",data.ID);

    if (SearchHashTable(table,data.ID,strlen(data.ID),&a)){     //元素存在
        table.data[a].number++;
        printf("投票成功!\n");
    }
    else {
        printf("无此记录!\n");
        printf("\t1.提名该学生\n");
        printf("\t2.返回\n");
        printf("请选择操作\n");
        scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                printf("提名学生信息格式如下:\n");
                printf("\t班级:20190654\n");
                printf("\t专业:计算机科学与技术\n");
                printf("\t年级:2019\n");
                printf("\t突出事迹:优秀团员\n");
                printf("班级:\t");
                scanf("%s",data.class);
                printf("专业:\t");
                scanf("%s",data.major);
                printf("年级:\t");
                scanf("%s",data.grade);
                printf("突出事迹:\t");
                scanf("%s",data.honour);
                data.number = 1;

                AddHashData(table,data);

                break;
            case 2:
                break;
            default:
                printf("输入错误,已退出\n");
                break;
            }
    }//else
    
    return OK;
}
//展示当前排行榜 使用插入排序
int ShowRank(Hash table){
	int a[NUM+1];                              //定义一个数组存放前十名在哈希表中的下标

	for(int i = 0; i < NUM; i++)     //初始化 
        a[i] = -1;
    
    for(int i = 0; i < table.HashLength; i++)        //遍历哈希表
	{
		if(table.data[i].number)        //如果节点存在
		{
            int k;
			for(k = NUM-1; k >= 0; k--)               //插入排序
			{
				if(a[k] > -1){         //a[k]存在且 对应值小于目前值 则向后挪
                    if (table.data[a[k]].number < table.data[i].number)
                        a[k+1] = a[k];
                    else           //已经到达最前端
                        break;
                }
			}
		   a[k+1] = i;
		}
	}

	for(int i = 0; i < NUM && a[i] > -1; i++)      //对前十名输出
	    printf("选手姓名:%-15s  %d票\n",table.data[a[i]].name,table.data[a[i]].number);
    return OK;
}