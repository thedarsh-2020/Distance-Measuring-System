 /******************************************************************************
 *
 * Module: Ultrasonic Driver
 *
 * Description: Header file for Ultrasonic Driver
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Ultrasonic Driver
 */
void Ultrasonic_init(void);

/*
 * Description :
 * Function to out trigger pulse
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * Function to measure the distance after get timer value from ICU
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 * Function to control capture edge by ICU
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
