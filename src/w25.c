#include <stdio.h>
#include <stdint.h>
#include <string.h>

// FLASH - START
#define W25_JEDEC_ID_COMMAND 0x9F
#define W25_STATUS_COMMAND   0x05
#define W25_WRITE_ENABLE     0x06
#define W25_READ_DATA_COMMAND 0x03
#define W25_PAGE_PROGRAM_COMMAND  0x02
#define W25_SECTOR_ERASE_COMMAND  0x20

// #define W25_DEBUG 1

typedef void (*SPI_TransmitReceive_Func)(uint8_t*, uint8_t*, uint32_t);
SPI_TransmitReceive_Func w25_spi_transmit_receive;

void w25_read_jedec_id(void)
{
#ifdef W25_DEBUG
    printf("Reading JEDEC ID \n");
#endif

    uint8_t mybuffer[4];
    mybuffer[0] = W25_JEDEC_ID_COMMAND;

    w25_spi_transmit_receive(mybuffer, mybuffer, 4);

#ifdef W25_DEBUG
    printf("JEDEC ID: 0x%X%X%X \n", mybuffer[0 + 1], mybuffer[1 + 1], mybuffer[2 + 1]);
#endif
}

uint8_t w25_read_status(void)
{
    uint8_t mybuffer[2];
    mybuffer[0] = W25_STATUS_COMMAND;

    w25_spi_transmit_receive(mybuffer, mybuffer, 2);

    return mybuffer[0 + 1];
}

void w25_write_enable(void)
{
    uint8_t mybuffer[1];
    mybuffer[0] = W25_WRITE_ENABLE;

    w25_spi_transmit_receive(mybuffer, mybuffer, 1);
}

void w25_read_flash(uint32_t address, uint8_t *data, uint32_t size)
{
#ifdef W25_DEBUG
    printf("Reading Flash start %X\n", address);
#endif

    uint8_t mybuffer[256 + 4];
    mybuffer[0] = W25_READ_DATA_COMMAND;

    mybuffer[1] = (address >> 16) & 0xFF;
    mybuffer[2] = (address >> 8) & 0xFF;
    mybuffer[3] = address & 0xFF;

    w25_spi_transmit_receive(mybuffer, mybuffer, 4 + size);

    memcpy(data, &mybuffer[4], size);

    while (w25_read_status() & 0x01);
}

void w25_write_page(uint32_t address, uint8_t *data, uint32_t size)
{
#ifdef W25_DEBUG
    printf("Write Page start %X\n", address);
#endif

    w25_write_enable();

    uint8_t mybuffer[256 + 4];
    mybuffer[0] = W25_PAGE_PROGRAM_COMMAND;

    mybuffer[1] = (address >> 16) & 0xFF;
    mybuffer[2] = (address >> 8) & 0xFF;
    mybuffer[3] = address & 0xFF;

    memcpy(&mybuffer[4], data, size);

    w25_spi_transmit_receive(mybuffer, mybuffer, 4 + size);

    while (w25_read_status() & 0x01);
}

void w25_erase_page(uint32_t address)
{
#ifdef W25_DEBUG
    printf("Erase Page %X start \n", address);
#endif

    w25_write_enable();

    uint8_t mybuffer[32];
    mybuffer[0] = W25_SECTOR_ERASE_COMMAND;

    mybuffer[1] = (address >> 16) & 0xFF;
    mybuffer[2] = (address >> 8) & 0xFF;
    mybuffer[3] = address & 0xFF;

    w25_spi_transmit_receive(mybuffer, mybuffer, 4);

    while (w25_read_status() & 0x01);
}


void w25_init(SPI_TransmitReceive_Func function) {
    w25_spi_transmit_receive = function;

    w25_read_jedec_id();
}
