/*
#########################################################################################################################
#  ModuleLayer    : Config                                                                                              #
#  ModuleName     : ConfigBSPIO                                                                                         #
#  FileName       : CFG_BSP_IO.h                                                                                        #
#  Public         : Y                                                                                                   #
#=======================================================================================================================#
#  Note  :                                                                                                              #
#    The BSP configure of used GPIO.                                                                                    #
#=======================================================================================================================#
#    Version    |    Date    |   Modified By   |                              Change Log                                #
#-----------------------------------------------------------------------------------------------------------------------#
#     V0.1.0    | 2024/02/14 |  Ghostbird03    | Initial Commit                                                         #
#-----------------------------------------------------------------------------------------------------------------------#
#########################################################################################################################
*/


#ifndef CONFIG_CFG_BSP_IO_H_
#define CONFIG_CFG_BSP_IO_H_

//GPIO BSP Config of SPI Bus
#define PORT_SPI_SCK        GPIOC
#define PIN_SPI_SCK         GPIO_Pin_5
#define PORT_SPI_MOSI       GPIOC
#define PIN_SPI_MOSI        GPIO_Pin_6

//GPIO BSP Configure of Normal Control
#define PORT_IO_SCRLED      GPIOC
#define PIN_IO_SCRLED       GPIO_Pin_1
#define PORT_IO_SCRCS       GPIOC
#define PIN_IO_SCRCS        GPIO_Pin_2
#define PORT_IO_SCRA0       GPIOC
#define PIN_IO_SCRA0        GPIO_Pin_3
#define PORT_IO_SCRRST      GPIOC
#define PIN_IO_SCRRST       GPIO_Pin_4
#define PORT_IO_POS1        GPIOD
#define PIN_IO_POS1         GPIO_Pin_4
#define PORT_IO_POS2        GPIOD
#define PIN_IO_POS2         GPIO_Pin_5
#define PORT_IO_POS3        GPIOD
#define PIN_IO_POS3         GPIO_Pin_6



#endif // CONFIG_CFG_BSP_IO_H_
