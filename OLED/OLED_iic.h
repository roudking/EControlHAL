#ifndef __OLED_IIC_H__
#define __OLED_IIC_H__

#include "iic.h"

// OLED器件地址
#define OLED_ADDRESS 0x78

// OLED参数
#define OLED_PAGE 8            // OLED页数
#define OLED_ROW 8 * OLED_PAGE // OLED行数
#define OLED_COLUMN 128        // OLED列数

#define OLED_IICPORT hi2c1 // IIC端口

void OLED_Send(uint8_t *data, uint8_t len);


#endif