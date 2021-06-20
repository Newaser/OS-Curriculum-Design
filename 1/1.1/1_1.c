#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/sem.h>  
#include <fcntl.h>  
#include <unistd.h>
#include <wait.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <time.h>  
#define MAXSEM 5  
/*本程序序采用Linux中的信号量实现了操作系统中的生产者、消费者问题，共有一个生产者进程，有两
个消费者进程，其中生产者产生 1～20 的 20 个数，两个消费者从共享内存中取数，并求和，以实现
生产者与消费者进程之间同步和协同机制的模拟*/


void main()
{     
	int fullid,emptyid,mutxid;
	//声明P,V变量  
	struct sembuf P, V;
	//声明semun型的联合体变量arg  
	union semun
	{
		int val;
		struct semid_ds* buf;
		ushort* array;
	} arg;

	//声明四个指针变量，array表示产品的空位数组，sum表示产品代号和，set用于生产者放置产品，get用于消费者获取产品  
	int* array;
	int* sum;
	int* set;
	int* get;
	//创建3个所有用户都可以读写的信号量  
	fullid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
	emptyid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
	mutxid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
	//将这些变量指向 int 整数倍长度的内存映射区，且内容可被读写，用于进程间共享。但为临界资源，需要受保护访问  
	array = (int*)mmap(NULL, sizeof(int) * 5, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sum = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	get = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	set = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//初始化各共享变量  
	*sum = 0;
	*get = 0;
	*set = 0;

	
	//初始化各信号量  
	arg.val = 0;
	if (semctl(fullid, 0, SETVAL, arg) == -1)
	perror("semctl semval error");
	arg.val = MAXSEM;
	if (semctl(emptyid, 0, SETVAL, arg) == -1)
	perror("semctl semval error");
	arg.val = 1;
	if (semctl(mutxid, 0, SETVAL, arg) == -1)
	perror("semctl semval error");

	//初始化P,V操作(信号量数为1，单次P/V将减/增1，SEM_UNDO会让系统跟进信号量的修改情况，以防止死锁)  
	V.sem_num = 0;
	V.sem_op = 1;
	V.sem_flg = SEM_UNDO;
	P.sem_num = 0;
	P.sem_op = -1;
	P.sem_flg = SEM_UNDO;


	if (fork() == 0)
	{ // 生产者,生产20个产品  
		
		
		do{
			semop(emptyid, &P, 1);//产品的空位-1  
			semop(mutxid, &P, 1);//拿到写信号量  

			//循环数组array用于记录产品编号，set是放置产品的位置，其值累加  
			array[(*set) % MAXSEM] = *set + 1;
			printf("生产者进程产出数字 %d\n", array[(*set) % MAXSEM]);
			semop(mutxid, &V, 1); //释放写信号量  
			semop(fullid, &V, 1); //产品的满位+1  
			(*set)++;
		}while (*set < 20);
		sleep(1);
		printf("Producer is over\n");
		exit(0);
	}
	else
	{
		if (fork() == 0)
		{ //消费者A，最多消费20个产品  
			//消费者的主循环  
			
			while (1){
				semop(fullid, &P, 1); //产品的满位-1  
				semop(mutxid, &P, 1); //拿到写信号量  

				//get是获取产品的位置，循环数组生产&消费的算法以至于不会get到空值位或重复位  
				if (*get < 20) {
					*sum += array[(*get) % MAXSEM];
					printf("消费者进程A取得数字 %d\n", array[(*get) % MAXSEM]);
					(*get)++;
					if (*get == 20) {
						printf("1～20 的 20 个数的和为： %d\n", *sum);
					}
				}
				semop(mutxid, &V, 1);  //释放写信号量  
				semop(emptyid, &V, 1); //产品的空位+1  
				if (*get == 20)
				{
					break;
				}
			}
			printf("消费者进程A结束\n");
			exit(0);
		}
		else
		{
			if (fork() == 0)
			{ //消费者B，同消费者A  
				
				while (1){
					semop(fullid, &P, 1);
					semop(mutxid, &P, 1);
					if (*get < 20) {
						*sum += array[(*get) % MAXSEM];
						printf("消费者进程B取得数字 %d\n", array[(*get) % MAXSEM]);
						(*get)++;
						if (*get == 20) {
							printf("1～20 的 20 个数的和为：%d\n", *sum);
						}
					}
					semop(mutxid, &V, 1);
					semop(emptyid, &V, 1);
					if (*get == 20) {
						break;
					}
				}
				printf("消费者进程B结束\n");
				exit(0);
			}
			else {//主进程  
				wait(0);
				wait(0);
				wait(0);
				sleep(1);
				exit(0);
			}
		}
	}
}
