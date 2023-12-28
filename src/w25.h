#ifndef _W25_H_
#define _W25_H_

typedef void (*SPI_TransmitReceive_Func)(uint8_t*, uint8_t*, uint32_t);
SPI_TransmitReceive_Func w25_spi_transmit_receive;

void w25_read_jedec_id(void);
uint8_t w25_read_status(void);
void w25_write_enable(void);
void w25_read_flash(uint32_t address, uint8_t *data, uint32_t size);
void w25_write_page(uint32_t address, uint8_t *data, uint32_t size);
void w25_erase_page(uint32_t address);
void w25_init(SPI_TransmitReceive_Func function);

#endif