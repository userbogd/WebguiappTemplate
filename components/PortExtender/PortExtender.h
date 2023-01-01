/*
 * PortExtender.h
 *
 *  Created on: 22 окт. 2021 г.
 *      Author: bogd
 */

#ifndef COMPONENTS_PORTEXTENDER_PORTEXTENDER_H_
#define COMPONENTS_PORTEXTENDER_PORTEXTENDER_H_

#define  ON     (1)
#define  OFF    (0)

void InitVGPO(void);
void UpdateVGPO(void);

void SetADCInput(uint8_t N);
void SetRS485_RE(uint8_t level);
void SetCTRL_BAT(uint8_t level);
void SetCHECK_BAT(uint8_t level);
void SetPGM1(uint8_t level);
void SetPGM2(uint8_t level);
void SetLORA_RST(uint8_t level);
void SetGSM_PWR(uint8_t level);
void SetETH_RST(uint8_t level);
void SetLEDSRegister(uint8_t addr, uint8_t data);

#endif /* COMPONENTS_PORTEXTENDER_PORTEXTENDER_H_ */
