#include "Resberry_Pi.h"

static RESBERRY_TEMP resberry_temp;

void Resberry_init(void)
{
   Resberry_uartinit();
}

void Resberry_greenareadataIN(int indata)
{
   resberry_temp.green_area = indata;
}

void Resberry_numerdataIN(int num)
{
	 resberry_temp.num= num;
}

void Resberry_stateIN(Resberry_STATE state)
{
   resberry_temp.state = state;
}   

void Resberry_getgreen_area(RESBERRY *resberry)
{
  Resberry_uartsend("{\"cmd\":\"color\", \"name\":\"green\"}\n",strlen("{\"cmd\":\"color\", \"name\":\"green\"}\n"));
	while(resberry_temp.state == resberry_wait_echo);
	resberry->green_area = resberry_temp.green_area;	
	resberry_temp.state = resberry_wait_echo;
}

//void Resberry_getnumer(RESBERRY *resberry)
//{
//	Resberry_uartsend("{\"cmd\":\"number\"}\n",strlen("{\"cmd\":\"number\"}\n"));
//	while(resberry_temp.state == resberry_wait_echo){};
//	static int i = 0;
//	if(i == 0)  
//	{
//		resberry->num[0] = resberry_temp.num;
//		i++;
//	}
//  else if(i == 1)
//	{
//		resberry->num[1] = resberry_temp.num;
//	}
//	resberry_temp.state = resberry_wait_echo;
//}

void Resberry_sendgetnumercmd(RESBERRY *resberry)
{
	Resberry_uartsend("{\"cmd\":\"number\"}\n",strlen("{\"cmd\":\"number\"}\n"));
	
}
void Resberry_getstate(RESBERRY *resberry)
{
	resberry->state = resberry_temp.state;
}

// 将 *a1, *a2, a3, a4 这四个值中最大的两个放回 *a1 和 *a2
void keep_top2(int *a1, int *a2, int a3, int a4) {
    int tmp[4] = { *a1, *a2, a3, a4 };
    int best_idx, t;

    // 只进行两轮选择：第一轮找最大，第二轮找第二大
    for (int i = 0; i < 2; i++) {
        best_idx = i;
        for (int j = i + 1; j < 4; j++) {
            if (tmp[j] > tmp[best_idx]) {
                best_idx = j;
            }
        }
        // 交换 tmp[i] 和 tmp[best_idx]
        t = tmp[i];
        tmp[i] = tmp[best_idx];
        tmp[best_idx] = t;
    }

    // 将最大值和第二大值写回
    *a1 = tmp[0];
    *a2 = tmp[1];
}


// 在 temp1–temp4 四个值中找出最大的两个不同的数，存到 *a1, *a2
void keep_two_max_distinct(int *a1, int *a2,
                           int temp1, int temp2, int temp3, int temp4)
{
    int temps[4] = { temp1, temp2, temp3, temp4 };
    // 用第一个元素初始化 max1/max2
    int max1 = temps[0], max2 = temps[0];

    for (int i = 1; i < 4; i++) {
        int v = temps[i];
        if (v > max1) {
            // 新的最大值，旧的最大值降为第二大
            max2 = max1;
            max1 = v;
        }
        else if (v != max1 && (max2 == max1 || v > max2)) {
            // v < max1 且与 max1 不同，同时要么还没找到不同的第二大（max2==max1），
            // 要么 v 比当前第二大更大
            max2 = v;
        }
    }

    *a1 = max1;
    *a2 = max2;
}


void Resberry_getnumber(RESBERRY *resberry)
{

	int temp_num_1 = resberry_temp.num/10;
	int temp_num_2 = resberry_temp.num%10;
	int temp_num_3 = 0;
	int temp_num_4 = 0;	
	
	int max1,max2;
	
  keep_top2(&temp_num_1,&temp_num_2,resberry->num[0],resberry->num[1]);
	keep_top2(&temp_num_3,&temp_num_4,resberry->num[0],resberry->num[1]);
	
	keep_two_max_distinct(&max1, &max2, temp_num_1, temp_num_2, temp_num_3, temp_num_4);
	resberry->num[0] = max1;
	resberry->num[1] = max2;
	
	resberry_temp.state = resberry_wait_echo;
	resberry->state = resberry_wait_echo;
}