#include "OLED_iic.h"

// ========================== 底层通信函数 ==========================

/**
 * @brief 向OLED发送数据的函数
 * @param data 要发送的数据
 * @param len 要发送的数据长度
 * @return None
 * @note 此函数是移植本驱动时的重要函数 将本驱动库移植到其他平台时应根据实际情况修改此函数
 */
void OLED_Send(uint8_t *data, uint8_t len) {
  iic_send(&OLED_IICPORT, OLED_ADDRESS, data, len, HAL_MAX_DELAY);
}