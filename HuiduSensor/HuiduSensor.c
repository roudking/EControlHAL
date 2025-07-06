#include "HuiduSensor.h"

static void Huidu_getvaluearray(int *huidudata)
{
     Huidu_ReadPin(huidudata);
}



//数据处理函数
static uint8_t valueprocess(int *huidudata) {
     uint8_t result = 0;
     for (int i = 0; i < 8; i++) {
         // 将数组元素转换为0或1，并左移到对应位
         result |= (huidudata[i] ? 1 : 0) << (7 - i);
     }
     return result;
}

static uint8_t valueshield(uint8_t huidudata, int index1, int index2)
{
    // 将1-based高位索引转换为0-based低位索引
    int bit1 = 7 - (index1 - 1);
    int bit2 = 7 - (index2 - 1);

    // 确定有效范围
    int start = (bit1 < bit2) ? bit1 : bit2;
    int end = (bit1 < bit2) ? bit2 : bit1;

    // 边界约束
    start = (start < 0) ? 0 : (start > 7) ? 7 : start;
    end = (end < 0) ? 0 : (end > 7) ? 7 : end;

    // 生成掩码
    if (start > end) return 0;
    uint8_t mask = ((1 << (end - start + 1)) - 1) << start;
    
    return huidudata & mask;
}
	

static float Huidu_getbias(uint8_t huidudata_bin)
{
     switch (huidudata_bin) 
				{
         case 0b00000000: return 0.0;  // 无偏差
				 case 0b00011000: return 0.0;  // 无偏差
         case 0b00010000: return 0.5; // 左偏差
         case 0b00110000: return 1.0; // 左偏差
         case 0b00100000: return 1.5; // 左偏差
         case 0b01100000: return 2.0; // 左偏差
         case 0b01000000: return 2.5; // 左偏差
         case 0b11000000: return 3.0; // 左偏差
         case 0b10000000: return 3.5; // 左偏差					
         case 0b00001000: return -0.5; // 右偏差
         case 0b00001100: return -1.0; // 右偏差
         case 0b00000100: return -1.5; // 右偏差
         case 0b00000110: return -2.0; // 右偏差
			   case 0b00000010: return -2.5; // 右偏差
         case 0b00000011: return -3.0; // 右偏差					
         case 0b00000001: return -3.5; // 右偏差	
					
         default: return 0; // 无偏差
				}
}	

void Huidu_getstate(HUIDU *huidu,int index1, int index2)
{
	       uint8_t mask = valueshield(huidu->huiduvalue_bin, index1, index2);
         switch (mask) 
				{
					 case 0b00111100: huidu->state =  in_the_line;     break;// 到达线上
           case 0b00001111: huidu->state =  in_the_turnright;   break; // 到达右直角
					 case 0b11110000: huidu->state =  in_the_turnleft;   break; // 到达左直角
					 case 0b00000000: huidu->state =  in_the_allwhite;	break;//到达无线处
					 case 0b10000000: huidu->state =  in_the_end;	break;//到达终点线
					 case 0b01000000: huidu->state =  in_the_end;	break;//到达终点线
					 case 0b00100000: huidu->state =  in_the_end;	break;//到达终点线					
					 case 0b00010000: huidu->state =  in_the_end;	break;//到达终点线				
									
					 				
					default: huidu->state =  incomplete; break; // 未到达
				}		
}


void Huidu_getvalue(HUIDU *huidu_data)
{
     Huidu_getvaluearray(huidu_data->huiduvalue);
	   huidu_data->huiduvalue_bin = valueprocess(huidu_data->huiduvalue);
	   huidu_data->huidu_bias = Huidu_getbias(huidu_data->huiduvalue_bin);
}


