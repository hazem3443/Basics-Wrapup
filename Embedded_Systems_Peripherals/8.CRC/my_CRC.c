#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short CRC_calc16(char indata[], int len);
unsigned int CRC_calc32(unsigned char const indata[], int len);

void main()
{
    char Tx_data[] = {0xC1}; //have to have the null character

    printf("CRC-16\n");

    // printf("TX Data\n");
    // for (size_t i = 0; i < sizeof(Tx_data) / sizeof(char); i++)
    //     printf("%X\n", Tx_data[i]);

    unsigned short CRC_val = CRC_calc16(Tx_data, sizeof(Tx_data) / sizeof(char));

    printf("CRC Value at TX = %X\n", CRC_val);

    char Rx_data[] = {Tx_data[0], CRC_val >> 8, (char)CRC_val};

    // printf("RX Data\n");
    // for (size_t i = 0; i < sizeof(Rx_data) / sizeof(char); i++)
    //     printf("%X\n", Rx_data[i]);

    printf("CRC Value at RX = %X\n", CRC_calc16(Rx_data, sizeof(Rx_data) / sizeof(char)));

    // printf("Tx_data = %s ,CRC_val at Tx = %X ,Rx_data  = %s ,CRC_val at RX = %X \n", Tx_data, CRC_val, Rx_data, CRC_calc16(Rx_data, length));

    printf("\nCRC-32\n");

    char input_data[] = {0x00, 0x00, 0x00, 0xC1};

    unsigned int crc_Code = CRC_calc32(input_data, sizeof(input_data) / sizeof(char));
    printf("TX-data = 0x000000C1, CRC-Value at TX = %X\n", crc_Code);

    int Rx_data32[] = {input_data[0], crc_Code};

    // printf("CRC Value at RX = %X\n", CRC_calc32(Rx_data32, sizeof(Rx_data32) / sizeof(int)));
}

unsigned short CRC_calc16(char indata[], int len)
{
    // printf("in func rem = %X size = %i\n", indata[0], len);
    unsigned short rem = 0x0000; //initial CRC
    for (int i = 0; i < len; ++i)
    {
        rem ^= ((unsigned short)indata[i] << 8);
        for (int j = 8; j > 0; --j)
        {
            // printf("new rem = %X comp=%x\n", rem, rem & (1 << 15));
            if (rem & (1 << 15))
                rem = (rem << 1) ^ 0x1021; //fill zero in shifted bits
            else
                rem = (rem << 1);
        }
    }
    return rem;
}

unsigned int CRC_calc32(unsigned char const indata[], int len)
{
    // printf("in func rem = %X size = %i\n", indata[0], len);
    unsigned int rem = 0xFFFFFFFF; //initial CRC
    for (int i = 0; i < len; ++i)
    {
        rem ^= indata[i] << ((8 * sizeof(unsigned int)) - 8);
        for (int j = 8; j > 0; --j)
        {
            printf("new rem = %X comp=%x\n", rem, rem & (1 << 15));
            if (rem & ((1 << ((8 * sizeof(unsigned int)) - 1))))
                rem = (rem << 1) ^ 0x04C11DB7; //fill zero in shifted bits
            else
                rem = (rem << 1);
            // if (rem & (1 << 31))
            //     rem ^= 0x04C11DB7; //fill zero in shifted bits
            // rem = (rem << 1);
        }
    }
    return rem;
}
