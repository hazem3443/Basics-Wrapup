/*
 * CRC.h
 *
 *  Created on: Sep 20, 2021
 *      Author: root
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_


void CRC_init(void);

uint32_t CRC_Send_32(uint32_t data);
uint32_t CRC_Send_Stream_32(uint32_t *data, size_t len);

#endif /* INC_CRC_H_ */
