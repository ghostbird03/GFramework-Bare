/*
#########################################################################################################################
#  ModuleLayer    : DRV-Screen                                                                                          #
#  ModuleName     : DRV_ST7567                                                                                          #
#  FileName       : DRV_ST7567.h                                                                                        #
#  Public         : Y                                                                                                   #
#=======================================================================================================================#
#  Note  :                                                                                                              #
#    The Driver for screens that use ST7567 as controler.                                                               #
#=======================================================================================================================#
#    Version    |    Date    |   Modified By   |                              Change Log                                #
#-----------------------------------------------------------------------------------------------------------------------#
#     V0.1.0    | 2024/xx/xx |  Ghostbird03    | Initial Commit                                                         #
#-----------------------------------------------------------------------------------------------------------------------#
#########################################################################################################################
*/

#ifndef DRV_SCREEN_DRV_ST7567_H_
#define DRV_SCREEN_DRV_ST7567_H_

#define ON      1
#define OFF     0

/*          DriverLayer:ST7567 Communication Status
 *          Start:      Start of a Data/Command series
 *          Cont:       Continuous Communication of a Data/Command series
 *          End:        End of a Data/Command series
 *          Dat2Cmd:    Switch from data to command in a Data/Command series
 *          Cmd2Dat:    Switch from command to data in a Data/Command series
 */
typedef enum
{
    dST7567_ComSta_Start = 0,               dST7567_ComSta_Cont,                    dST7567_Cmd_End,
    dST7567_ComSta_Dat2Cmd,                 dST7567_ComSta_Cmd2Dat
}dST7567_enumComSta;

/*          DriverLayer:ST7567 Commands List
 * Display ON/OFF                           Set start line of display               Set page address to be operate
 * Set column address to be operate         Set scan direction of SEG               Inverse the display content
 * Set all pixel ON                         Set the bias duty                       Enter Read-Modify-Write mode
 * Exit Read-Modify-Write mode              Software RESET                          Set the output direction of COM
 * Power control of built-in circuit        Set the RR ratio(coarse CR)             Set the EV ratio(fine CR)
 * Set booster level(LCD vol)
 */
typedef enum
{
    dST7567_Cmd_DisplaySwitch = 0,          dST7567_Cmd_SetStartLine,               dST7567_Cmd_SetPageAdd,
    dSt7567_Cmd_SetColAdd,                  dST7567_Cmd_SetDirSEG,                  dST7567_Cmd_SetInvDisplay,
    dSt7567_Cmd_AllPxON,                    dST7567_Cmd_SetBias,                    dST7567_Cmd_EntModeRMD,
    dST7567_Cmd_ExitModeRMD,                dST7567_Cmd_RESET,                      dST7567_Cmd_setDirCOM,
    dST7567_Cmd_PowCtrl,                    dST7567_Cmd_SetRatioREG,                dST7567_Cmd_SetRatioEV,
    dST7567_Cmd_SetBooster
}dST7567_enumCmdID;



#endif // DRV_SCREEN_DRV_ST7567_H_
