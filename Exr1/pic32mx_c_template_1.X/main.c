/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */
#include "Tick.h" 
#include "HWP OLIMEX_PIC32-WEB.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
    DDPCONbits.JTAGEN = 0;
#endif

    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.
    
    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:
    
    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
    SYS_CFG_PCACHE (configures the pCache if used)
    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)*/

    /* TODO Add user clock/system configuration code if appropriate.  */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /*Configure Multivector Interrupt Mode.  Using Single Vector Mode
    is expensive from a timing perspective, so most applications
    should probably not use a Single Vector Mode*/
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    LED0_TRIS = 0; // Data direction register LED 1
    LED1_TRIS = 0; // Data direction register LED 2
    LED2_TRIS = 0; // Data direction register LED 3
    LED0_IO = 1; // I/O register LED 1
    LED1_IO = 1; // I/O register LED 2
    LED2_IO = 1; // I/O register LED 3
    BUTTON0_TRIS = 1; // Button 1 data direction register
    BUTTON0_IO   = 0;
    BUTTON1_TRIS = 1; // Button 1 data direction register
    BUTTON1_IO   = 0;
    BUTTON2_TRIS = 1; // Button 1 data direction register
    BUTTON2_IO   = 0;
    static DWORD ticksCount = 0;
    static DWORD t = 0;
    static DWORD tRes = 0;
    int i;
    int but;
    int toggle1;
    int toggle2;
    int toggle3;
    TickInit();
//    DoUARTConfig();
    mPORTDToggleBits(BIT_0);
    mPORTDToggleBits(BIT_1);
    mPORTDToggleBits(BIT_2);
    toggle1 = 0;
    toggle2 = 0;
    toggle3 = 0;
    while(1)
    {
        //for(i=0; i<100000; i++);
        
        
        if((PORTDbits.RD6 == 0) && (toggle1 == 0))
        {
            for(i=0; i<10000; i++);
            mPORTDToggleBits(BIT_0); 
            toggle1 = 1;
            
        }
        if((toggle1 == 1) && (PORTDbits.RD6 == 1))
        {
            for(i=0; i<10000; i++);
            toggle1 = 0;
        }
        
        if((PORTDbits.RD7 == 0) && (toggle2 == 0))
        {
            for(i=0; i<10000; i++);
            mPORTDToggleBits(BIT_1); 
            toggle2 = 1;
        }
        if((toggle2 == 1) && (PORTDbits.RD7 == 1))
        {
            for(i=0; i<10000; i++);
            toggle2 = 0;
        }
        
        if((PORTDbits.RD13 == 0) && (toggle3 == 0))
        {
            for(i=0; i<10000; i++);
            mPORTDToggleBits(BIT_2); 
            toggle3 = 1;
        }
        if((toggle3 == 1) && (PORTDbits.RD13 == 1))
        {
            for(i=0; i<10000; i++);
            toggle3 = 0;
        }
        //mPORTDToggleBits(BIT_1);
        //mPORTDToggleBits(BIT_2);
    }
}