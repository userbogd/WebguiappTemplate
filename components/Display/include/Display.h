/*
 * Display.h
 *
 *  Created on: 28 ���. 2021 �.
 *      Author: bogd
 */

#ifndef COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_
#define COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_

#define DISPLAY_TYPE_SH1106
//#define DISPLAY_TYPE_SSD1306


#define LMIC_DISPLAY_ENABLED 1

    void WriteDisplay(char *str,int strnum);
    void ReadDisplay(char *str,int strnum);
    void UpdateDisplay(void);
    void InitDisplay(void);
    void OutputDisplay(char* str, int strnum);
    void ClearDisplay(void);



#endif /* COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_ */
