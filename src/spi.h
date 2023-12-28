#ifndef _SPI_H_
#define _SPI_H_

void SPI1_Init(void);
uint8_t SPI1_ReadWriteByte(uint8_t TxData);
void SPI1_ReadWriteData(uint8_t *pTxData, uint8_t *pRxData, uint32_t Size);

#endif