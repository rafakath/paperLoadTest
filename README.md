# paperLoadTest

Project Objective : To check strength of paper

Microcontroller 	: 	16F877A (Microchip)
Language 		:	Embedded C
Compiler		: 	MPLAB 8.33
Simulation Software	:	Proteus 7.1

Hardware Description:

LCD : 2*16 Alphanumeric LCD in 4-bit mode for display purpose.

tensile load sensor : ADC in interrupt mode to read value form load sensor.

Internal EEROM : To stored the calibrated set value by user.

Restart switch : It restart system and check for home position. If lower limit switch is in ON State then only user can start checking the strength of paper.

Start/Stop Switch: User can start checking the strength of paper. In between if user want to stop machine then with the help of same switch it can be done.

Enter/Calibration Switch : With this switch calibration can be done, with left and right switch user can decrease and increase value for calibration. Once calibration value is set then it will get stored in EEPROM and user can exit from calibration mode using same switch (calibration switch)

Description:
Paper is fixed from one side and from other side it is pulled until unless paper tear off. At certain load/stress paper get tear off and value at which paper tears is displayed on LCD. Switch are available through which user can calibrate load value for displaying and other switches are available for controlling other operation.
