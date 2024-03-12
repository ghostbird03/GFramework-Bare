/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Ghostbird03
 * Version            : V1.0.0
 * Date               : 2024/02/13
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "../VEN/Peripheral/inc/ch32v00x.h"
#include "../VEN/Debug/debug.h"
#include "../Config/CFG_BSP_IO.h"

void HWL_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    //Enable RCC clock of GPIOC/D and SPI1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_SPI1, ENABLE);

    //Init IO for SPI
    GPIO_InitStructure.GPIO_Pin = PIN_SPI_SCK|PIN_SPI_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_SPI_SCK,&GPIO_InitStructure);

    //Init IO for LCD control
    GPIO_InitStructure.GPIO_Pin = PIN_IO_SCRLED|PIN_IO_SCRCS|PIN_IO_SCRA0|PIN_IO_SCRRST;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(PORT_IO_SCRLED,&GPIO_InitStructure);

    //Init IO for Pos read
    GPIO_InitStructure.GPIO_Pin = PIN_IO_POS1|PIN_IO_POS2|PIN_IO_POS3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(PORT_IO_POS1,&GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    //SPI Speed = 6M
//    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    //Enable the SPI
    SPI_Cmd(SPI1, ENABLE);
}

uint8_t DRV_ST7567_SendCommand(uint8_t Command)
{
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, RESET);              //Pull down the chip-select
    GPIO_WriteBit(PORT_IO_SCRA0, PIN_IO_SCRA0, RESET);              //Address configed to cmd mode
    Delay_Us(1000);

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);    //Make sure SPI is not sending data
    SPI_I2S_SendData(SPI1, Command);                                //Assign data to SPI data buffer
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET);  //Make sure data sending has been completely

    Delay_Us(1000);
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, SET);                //Pull up the chip-select
    GPIO_WriteBit(PORT_IO_SCRA0, PIN_IO_SCRA0, SET);                //Address configed to data mode
    return 0;
}

uint8_t DRV_ST7567_SendData(uint8_t Data)
{
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, RESET);              //Pull down the chip-select
    GPIO_WriteBit(PORT_IO_SCRA0, PIN_IO_SCRA0, SET);                //Address configed to data mode
    Delay_Us(1000);

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);    //Make sure SPI is not sending data
    SPI_I2S_SendData(SPI1, Data);                                //Assign data to SPI data buffer
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET);  //Make sure data sending has been completely

    Delay_Us(1000);
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, SET);                //Pull up the chip-select
    return 0;
}

uint8_t DRV_ST7567_FillPage(uint8_t TarPage,uint8_t FillData)
{
    uint16_t i;
    DRV_ST7567_SendCommand(0xB0 | TarPage);
    DRV_ST7567_SendCommand(0x10);
    DRV_ST7567_SendCommand(0x00);
    for(i=0;i<128;i++)
    {
        DRV_ST7567_SendData(FillData);
    }
    return 0;
}

vu8 val;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t i = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
//#if (SDI_PRINT == SDI_PR_OPEN)
//    SDI_Printf_Enable();
//#else
//    USART_Printf_Init(115200);
//#endif
//    printf("SystemClk:%d\r\n",SystemCoreClock);
//    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

//    USARTx_CFG();

    HWL_GPIO_Init();

    //Reset the pos read io to dafault(H)
    GPIO_WriteBit(PORT_IO_POS1, PIN_IO_POS1, SET);
    GPIO_WriteBit(PORT_IO_POS2, PIN_IO_POS2, SET);
    GPIO_WriteBit(PORT_IO_POS3, PIN_IO_POS3, SET);

    //Reset screen control io(CS,RST,LED=Invalid;A0=Cmd status)
    GPIO_WriteBit(PORT_IO_SCRRST, PIN_IO_SCRRST, SET);
    GPIO_WriteBit(PORT_IO_SCRA0, PIN_IO_SCRA0, RESET);
    GPIO_WriteBit(PORT_IO_SCRLED, PIN_IO_SCRLED, RESET);
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, SET);

    //Trigger the reset of screen
    GPIO_WriteBit(PORT_IO_SCRCS, PIN_IO_SCRCS, RESET);
    GPIO_WriteBit(PORT_IO_SCRRST, PIN_IO_SCRRST, RESET);
    Delay_Ms(50);
    GPIO_WriteBit(PORT_IO_SCRRST, PIN_IO_SCRRST, SET);
    Delay_Ms(50);
    DRV_ST7567_SendCommand(0xE2);                       //Soft reset the screen
    Delay_Ms(100);
    DRV_ST7567_SendCommand(0x2C);
    Delay_Ms(100);
    DRV_ST7567_SendCommand(0x2E);
    Delay_Ms(100);
    DRV_ST7567_SendCommand(0x2F);
    Delay_Ms(100);
    DRV_ST7567_SendCommand(0x25);
    DRV_ST7567_SendCommand(0x81);
    DRV_ST7567_SendCommand(0x13);
    DRV_ST7567_SendCommand(0xA2);
    DRV_ST7567_SendCommand(0xC8);
    DRV_ST7567_SendCommand(0xA0);
    DRV_ST7567_SendCommand(0x40);
    DRV_ST7567_SendCommand(0xAF);

    GPIO_WriteBit(PORT_IO_SCRLED, PIN_IO_SCRLED, SET);
    DRV_ST7567_FillPage(0x01, 0xFF);

    while(1)
    {
        Delay_Ms(1000);
//        if(i == 0)
//        {
//            DRV_ST7567_SendCommand(0xA5);
//            GPIO_WriteBit(PORT_IO_SCRLED, PIN_IO_SCRLED, RESET);
//            i++;
//        }else
//        {
//            DRV_ST7567_SendCommand(0xA4);
//            GPIO_WriteBit(PORT_IO_SCRLED, PIN_IO_SCRLED, SET);
//            i = 0;
//        }
//        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//        {
//            /* waiting for receiving finish */
//        }
//        val = (USART_ReceiveData(USART1));
//        USART_SendData(USART1, ~val);
//        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//        {
//            /* waiting for sending finish */
//        }
    }
}
