/**
 ******************************************************************************
 * @file     HD44780_LCD.c
 * @author   Aditya Agarwal (aditya.agarwal@dumblebots.com)
 * @version  V1.0
 * @date     13/04/2023 13:44:50
 * @brief    Contains definitions for the functions defined in HD447780_LCD.h to use 16x2 Character Liquid Crystal Displays along with the HD44780 Controller
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"
#include "HD44780_LCD.h"

// Alias to refer to the GPIO Port used to connect to the Data pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   DATA_PORT          	dataPort[0]
// Alias to refer to the GPIO Port used to connect to the Clock pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   CLOCK_PORT          	dataPort[1]
// Alias to refer to the GPIO Port used to connect to the Latch pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   LATCH_PORT          	dataPort[2]

// Alias to refer to the GPIO Pin used to connect to the Data pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   DATA_PIN          	dataPin[0]
// Alias to refer to the GPIO Pin used to connect to the Clock pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   CLOCK_PIN          	dataPin[1]
// Alias to refer to the GPIO Pin used to connect to the Latch pin of the Shift Register (this is used when the LCD is operated by the shift register)
#define   LATCH_PIN          	dataPin[2]

/** Functions ----------------------------------------------------------------*/

/**
 * @brief							Initializes an LCD structure to operate the HD44780 controller in 4-bit mode
 *
 * @param		lcd					Pointer to LCD structure
 * @param		port0				GPIO Port on which pin D4 of the LCD is connected
 * @param		pin0				GPIO Pin number within the port to which pin D4 of the LCD is connected
 * @param		port1				GPIO Port on which pin D5 of the LCD is connected
 * @param		pin1				GPIO Pin number within the port to which pin D5 of the LCD is connected
 * @param		port2				GPIO Port on which pin D6 of the LCD is connected
 * @param		pin2				GPIO Pin number within the port to which pin D6 of the LCD is connected
 * @param		port3				GPIO Port on which pin D7 of the LCD is connected
 * @param		pin3				GPIO Pin number within the port to which pin D7 of the LCD is connected
 * @param		enPort				GPIO Port on which the Enable (En) pin of the LCD is connected
 * @param		enPin				GPIO Pin number within the port to which the Enable (En) pin of the LCD is connected
 * @param		rsPort				GPIO Port on which the Register Select (RS) pin of the LCD is connected
 * @param		rsPin				GPIO Pin number within the port to which the Register Select (RS) pin of the LCD is connected
 */
void LCD_createHalfBus(HD44780_LCD_t *lcd, GPIO_TypeDef *port0, uint16_t pin0,
		GPIO_TypeDef *port1, uint16_t pin1, GPIO_TypeDef *port2, uint16_t pin2,
		GPIO_TypeDef *port3, uint16_t pin3, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin) {
	lcd->busMode = halfBus;

	lcd->dataPort[0] = port0;
	lcd->dataPort[1] = port1;
	lcd->dataPort[2] = port2;
	lcd->dataPort[3] = port3;

	lcd->dataPin[0] = pin0;
	lcd->dataPin[1] = pin1;
	lcd->dataPin[2] = pin2;
	lcd->dataPin[3] = pin3;

	lcd->enPort = enPort;
	lcd->rsPort = rsPort;

	lcd->enPin = enPin;
	lcd->rsPin = rsPin;
}

/**
 * @brief							Initializes an LCD structure to operate the HD44780 controller in 4-bit mode
 *
 * @param		lcd					Pointer to LCD structure
 * @param		port0				GPIO Port on which pin D0 of the LCD is connected
 * @param		pin0				GPIO Pin number within the port to which pin D0 of the LCD is connected
 * @param		port1				GPIO Port on which pin D1 of the LCD is connected
 * @param		pin1				GPIO Pin number within the port to which pin D1 of the LCD is connected
 * @param		port2				GPIO Port on which pin D2 of the LCD is connected
 * @param		pin2				GPIO Pin number within the port to which pin D2 of the LCD is connected
 * @param		port3				GPIO Port on which pin D3 of the LCD is connected
 * @param		pin3				GPIO Pin number within the port to which pin D3 of the LCD is connected\
 * @param		port4				GPIO Port on which pin D4 of the LCD is connected
 * @param		pin4				GPIO Pin number within the port to which pin D4 of the LCD is connected
 * @param		port5				GPIO Port on which pin D5 of the LCD is connected
 * @param		pin5				GPIO Pin number within the port to which pin D5 of the LCD is connected
 * @param		port6				GPIO Port on which pin D6 of the LCD is connected
 * @param		pin6				GPIO Pin number within the port to which pin D6 of the LCD is connected
 * @param		port7				GPIO Port on which pin D7 of the LCD is connected
 * @param		pin7				GPIO Pin number within the port to which pin D7 of the LCD is connected
 * @param		enPort				GPIO Port on which the Enable (En) pin of the LCD is connected
 * @param		enPin				GPIO Pin number within the port to which the Enable (En) pin of the LCD is connected
 * @param		rsPort				GPIO Port on which the Register Select (RS) pin of the LCD is connected
 * @param		rsPin				GPIO Pin number within the port to which the Register Select (RS) pin of the LCD is connected
 */
void LCD_createFullBus(HD44780_LCD_t *lcd, GPIO_TypeDef *port0, uint16_t pin0,
		GPIO_TypeDef *port1, uint16_t pin1, GPIO_TypeDef *port2, uint16_t pin2,
		GPIO_TypeDef *port3, uint16_t pin3, GPIO_TypeDef *port4, uint16_t pin4,
		GPIO_TypeDef *port5, uint16_t pin5, GPIO_TypeDef *port6, uint16_t pin6,
		GPIO_TypeDef *port7, uint16_t pin7, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin) {
	lcd->busMode = fullBus;

	lcd->dataPort[0] = port0;
	lcd->dataPort[1] = port1;
	lcd->dataPort[2] = port2;
	lcd->dataPort[3] = port3;
	lcd->dataPort[4] = port4;
	lcd->dataPort[5] = port5;
	lcd->dataPort[6] = port6;
	lcd->dataPort[7] = port7;

	lcd->dataPin[0] = pin0;
	lcd->dataPin[1] = pin1;
	lcd->dataPin[2] = pin2;
	lcd->dataPin[3] = pin3;
	lcd->dataPin[4] = pin4;
	lcd->dataPin[5] = pin5;
	lcd->dataPin[6] = pin6;
	lcd->dataPin[7] = pin7;

	lcd->enPort = enPort;
	lcd->rsPort = rsPort;

	lcd->enPin = enPin;
	lcd->rsPin = rsPin;
}

/**
 * @brief							Initializes the LCD to be used along with a 74HC595 Shift Register
 *
 * The Shift Register is used to operate the LCD in 8-bit mode, and the wiring should be done in reverse order, i.e.
 * Shift Register O0 is wired to LCD D7, O1 to D6 etc.
 * he RS and En pins are not operated by the Shift Register and must be directly wired to the microcontroller
 *
 * @param		lcd					Pointer to LCD structure
 * @param		dataPort			GPIO Port on which the Data-In pin of the Shift Register is connected
 * @param		dataPin				GPIO Pin within the Port to which the Data-In pin of the Shift Register is connected
 * @param		clockPort			GPIO Port on which the Clock-In pin of the Shift Register is connected
 * @param		clockPin			GPIO Pin within the Port to which the Clock-In pin of the Shift Register is connected
 * @param		latchPort			GPIO Port on which the Output-Latch pin of the Shift Register is connected
 * @param		latchPin			GPIO Pin within the Port to which the Output-Latch pin of the Shift Register is connected
 * @param		enPort				GPIO Port on which the Enable (En) pin of the LCD is connected
 * @param		enPin				GPIO Pin number within the port to which the Enable (En) pin of the LCD is connected
 * @param		rsPort				GPIO Port on which the Register Select (RS) pin of the LCD is connected
 * @param		rsPin				GPIO Pin number within the port to which the Register Select (RS) pin of the LCD is connected
 */
void LCD_createShiftRegister(HD44780_LCD_t *lcd, GPIO_TypeDef *dataPort,
		uint16_t dataPin, GPIO_TypeDef *clockPort, uint16_t clockPin,
		GPIO_TypeDef *latchPort, uint16_t latchPin, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin) {
	lcd->busMode = shiftReg;

	lcd->DATA_PORT= dataPort;
	lcd->CLOCK_PORT= clockPort;
	lcd->LATCH_PORT= latchPort;

	lcd->DATA_PIN= dataPin;
	lcd->CLOCK_PIN= clockPin;
	lcd->LATCH_PIN= latchPin;

	lcd->enPort = enPort;
	lcd->rsPort = rsPort;

	lcd->enPin = enPin;
	lcd->rsPin = rsPin;
}

/**
 * @brief							Initializes the LCD to be used along with a PC8574 Driver controlled via I2C at address 0x27
 *
 * @param		lcd					Pointer to LCD structure
 * @param		I2CHandle			Pointer to structure to the I2C interface that the LCD module is connected to
 */
void LCD_createI2C(HD44780_LCD_t *lcd, I2C_HandleTypeDef *I2CHandle) {
	LCD_createI2C_addr(lcd, I2CHandle, DEFAULT_I2C_ADDR);
}

/**
 * @brief							Initializes the LCD to be used along with a PC8574 Driver controlled via I2C
 *
 * @param		lcd					Pointer to LCD structure
 * @param		I2CHandle			Pointer to structure to the I2C interface that the LCD module is connected to
 * @param		lcdAddr				Address of the module on the I2C bus
 *
 */
void LCD_createI2C_addr(HD44780_LCD_t *lcd, I2C_HandleTypeDef *I2CHandle, uint8_t lcdAddr) {

	lcd->busMode = I2C;
	lcd->I2CHandle = I2CHandle;
	lcd->I2CAddr = lcdAddr;

	lcd->backlightMask = 1 << 3;
}

/**
 * @brief							Enables the backlight of the LCD (the function does not operate if the LCD is not being driven via I2C)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_enableBacklight(HD44780_LCD_t *lcd) {
	if (lcd->busMode == I2C) {
		lcd->backlightMask	= (1 << BACKLIGHT_ID);
		HAL_I2C_Master_Transmit(lcd->I2CHandle, lcd->I2CAddr, (uint8_t *)&(lcd->backlightMask), 1, HAL_MAX_DELAY);
	}
}

/**
 * @brief							Disables the backlight of the LCD (the function does not operate if the LCD is not being driven via I2C)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_disableBacklight(HD44780_LCD_t *lcd) {
	if (lcd->busMode == I2C) {
		lcd->backlightMask	= 0;
		HAL_I2C_Master_Transmit(lcd->I2CHandle, lcd->I2CAddr, (uint8_t *)&(lcd->backlightMask), 1, HAL_MAX_DELAY);
	}
}

/**
 * @brief							Toggles the backlight of the LCD (the function does not operate if the LCD is not being driven via I2C)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_toggleBacklight(HD44780_LCD_t *lcd) {
	if (lcd->busMode == I2C) {
		lcd->backlightMask ^= (1 << BACKLIGHT_ID);
		HAL_I2C_Master_Transmit(lcd->I2CHandle, lcd->I2CAddr, (uint8_t *)&(lcd->backlightMask), 1, HAL_MAX_DELAY);
	}
}

/**
 * @brief							Sends a nibble (4-bits) of information to the LCD when it is used in 4-bit mode (the information can be data or instructions, which must be determined by the caller)
 *
 * @param		lcd					Pointer to LCD structure
 * @param		nibble				Nibble of data to transmit (only the lower 4 bits of this are considered)
 */
void LCD_sendNibble(HD44780_LCD_t *lcd, uint8_t nibble) {

	for (uint32_t i = 0; i < 4; ++i) {
		HAL_GPIO_WritePin(lcd->dataPort[i], lcd->dataPin[i], (nibble >> i) & 1);
	}

	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

/**
 * @brief							Sends a byte (8-bits) of information to the LCD when it is used in 8-bit mode (the information can be data or instructions, which must be determined by the caller)
 *
 * @param		lcd					Pointer to LCD structure
 * @param		byte				Byte of data to transmit
 */
void LCD_sendByte(HD44780_LCD_t *lcd, uint8_t byte) {

	for (uint32_t i = 0; i < 8; ++i) {
		HAL_GPIO_WritePin(lcd->dataPort[i], lcd->dataPin[i], (byte >> i) & 1);
	}

	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

/**
 * @brief							Shifts out a byte of information to the LCD when it is used with a shift register (the information can be data or instructions, which must be determined by the caller)
 *
 * @param		lcd					Pointer to LCD structure
 * @param		byte				Byte of data to transmit
 */
void LCD_shiftByte(HD44780_LCD_t *lcd, uint8_t byte) {
	for (uint32_t i = 0; i < 8; ++i) {
		HAL_GPIO_WritePin(lcd->DATA_PORT, lcd->DATA_PIN, (byte >> (i)) & 1);
		HAL_GPIO_WritePin(lcd->CLOCK_PORT, lcd->CLOCK_PIN, GPIO_PIN_SET);
		// HAL_Delay(1);
		HAL_GPIO_WritePin(lcd->CLOCK_PORT, lcd->CLOCK_PIN, GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(lcd->LATCH_PORT, lcd->LATCH_PIN, GPIO_PIN_SET);
	// HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->LATCH_PORT, lcd->LATCH_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->enPort, lcd->enPin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

/**
 * @brief							Sends a nibble of information to the LCD when it is used with the I2C driver (the caller must also specify whether the information is data or an instruction)
 *
 * @param		lcd					Pointer to LCD structure
 * @param		nibble				Nibble of data to send (only the lower 4-bits are considered)
 * @param		isData				Whether the Nibble is an instruction (0) or Data (1)
 */
void LCD_sendNibbleI2C(HD44780_LCD_t *lcd, uint8_t nibble, uint8_t isData) {

	uint8_t result	= (nibble << 4) | (isData << RS_ID) | lcd->backlightMask;

	uint8_t buf[3];
	buf[0] = result;
	buf[1] = result | (1 << EN_ID);
	buf[2] = result;

	HAL_I2C_Master_Transmit(lcd->I2CHandle, lcd->I2CAddr, buf, 3, HAL_MAX_DELAY);
}

/**
 * @brief							Sends a single-byte instruction with the parameter bitmask to the LCD's Instruction Register
 *
 * @param		lcd					Pointer to LCD structure
 * @param		instruction			Instruction with parameter bitmask
 */
void LCD_sendInstruction(HD44780_LCD_t *lcd, uint8_t instruction) {

	switch (lcd->busMode) {
	case halfBus:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_RESET);
		LCD_sendNibble(lcd, HI_NIBBLE(instruction));
		LCD_sendNibble(lcd, LO_NIBBLE(instruction));
		break;
	case fullBus:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_RESET);
		LCD_sendByte(lcd, instruction);
		break;
	case shiftReg:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_RESET);
		LCD_shiftByte(lcd, instruction);
		break;
	case I2C:
		LCD_sendNibbleI2C(lcd, HI_NIBBLE(instruction), 0);
		LCD_sendNibbleI2C(lcd, LO_NIBBLE(instruction), 0);
		break;
	};
}

/**
 * @brief							Sends a single-byte of data to the LCD's Data Register
 *
 * @param		lcd					Pointer to LCD structure
 * @param		data				Data to send
 */
void LCD_sendData(HD44780_LCD_t *lcd, const uint8_t data) {
	switch (lcd->busMode) {
	case halfBus:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_SET);
		LCD_sendNibble(lcd, HI_NIBBLE(data));
		LCD_sendNibble(lcd, LO_NIBBLE(data));
		break;
	case fullBus:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_SET);
		LCD_sendByte(lcd, data);
		break;
	case shiftReg:
		HAL_GPIO_WritePin(lcd->rsPort, lcd->rsPin, GPIO_PIN_SET);
		LCD_shiftByte(lcd, data);
		break;
	case I2C:
		LCD_sendNibbleI2C(lcd, HI_NIBBLE(data), 1);
		LCD_sendNibbleI2C(lcd, LO_NIBBLE(data), 1);
		break;
	}
}

/**
 * @brief							Sends a sequence of bytes with fixed length to the LCD's Data Register
 *
 * @param		lcd					Pointer to LCD structure
 * @param		buf					Pointer to Data Buffer
 * @param		len					Length of Data Buffer
 */
void LCD_sendBuffer(HD44780_LCD_t *lcd, const uint8_t *buf, const uint32_t len) {
	for (uint32_t i = 0; i < len; ++i) {
		LCD_sendData(lcd, buf[i]);
	}
}

/**
 * @brief							Initializes the LCD module after the LCD structure has been initialized
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_init(HD44780_LCD_t *lcd) {
	HAL_Delay(50);

	lcd->displayState = LCD_DISPLAY_ENABLE | LCD_CURSOR_DISABLE
			| LCD_BLINK_DISABLE;
	lcd->cursorMovement = LCD_CURSOR_MOVE | LCD_CURSOR_POS_INC;

	switch (lcd->busMode) {
	case halfBus:
		for (uint32_t i = 0; i < 3; ++i) {
			LCD_sendNibble(lcd, HI_NIBBLE(LCD_SET_FUNCTION | LCD_BUS_SIZE_8));
			HAL_Delay(5);
		}
		LCD_sendNibble(lcd, HI_NIBBLE(LCD_SET_FUNCTION | LCD_BUS_SIZE_4));
		HAL_Delay(2);
		LCD_sendInstruction(lcd,
				LCD_SET_FUNCTION | LCD_BUS_SIZE_4 | LCD_DOT_COUNT_8
						| LCD_LINE_COUNT_2);
		break;
	case fullBus:
		for (uint32_t i = 0; i < 3; ++i) {
			LCD_sendByte(lcd, LCD_SET_FUNCTION | LCD_BUS_SIZE_8);
			HAL_Delay(5);
		}
		LCD_sendInstruction(lcd,
		LCD_SET_FUNCTION | LCD_BUS_SIZE_8 | LCD_DOT_COUNT_8 | LCD_LINE_COUNT_2);
		break;
	case shiftReg:
		for (uint32_t i = 0; i < 3; ++i) {
			LCD_shiftByte(lcd, LCD_SET_FUNCTION | LCD_BUS_SIZE_8);
			HAL_Delay(5);
		}
		LCD_sendInstruction(lcd,
		LCD_SET_FUNCTION | LCD_BUS_SIZE_8 | LCD_DOT_COUNT_8 | LCD_LINE_COUNT_2);
		break;
	case I2C:
		for (uint32_t i = 0; i < 3; ++i) {
			LCD_sendNibbleI2C(lcd, HI_NIBBLE(LCD_SET_FUNCTION | LCD_BUS_SIZE_8), 0);
			HAL_Delay(5);
		}
		LCD_sendNibbleI2C(lcd, HI_NIBBLE(LCD_SET_FUNCTION | LCD_BUS_SIZE_4), 0);
		HAL_Delay(2);
		LCD_sendInstruction(lcd,
						LCD_SET_FUNCTION | LCD_BUS_SIZE_4 | LCD_DOT_COUNT_8
								| LCD_LINE_COUNT_2);
		break;
	}
	HAL_Delay(2);

	LCD_sendInstruction(lcd, LCD_CLEAR_DISPLAY);
	HAL_Delay(2);

	LCD_sendInstruction(lcd, LCD_SET_CURSOR_HOME);
	HAL_Delay(2);

	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
	HAL_Delay(2);

	LCD_sendInstruction(lcd, LCD_SET_ENTRY_MODE | lcd->cursorMovement);
	HAL_Delay(2);
}

/**
 * @brief							Sets the cursor to automatically decrement (move left) after printing a character
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_setCursorAutoDec(HD44780_LCD_t *lcd) {
	lcd->cursorMovement = LCD_CURSOR_POS_DEC | LCD_CURSOR_MOVE;
	LCD_sendInstruction(lcd, LCD_SET_ENTRY_MODE | lcd->cursorMovement);
}

/**
 * @brief							Sets the cursor to automatically increment (move right) after printing a character
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_setCursorAutoInc(HD44780_LCD_t *lcd) {
	lcd->cursorMovement = LCD_CURSOR_POS_INC | LCD_CURSOR_MOVE;
	LCD_sendInstruction(lcd, LCD_SET_ENTRY_MODE | lcd->cursorMovement);
}

/**
 * @brief							Sets the display to automatically decrement (scroll left) after printing a character
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_setDisplayAutoDec(HD44780_LCD_t *lcd) {
	lcd->cursorMovement = LCD_CURSOR_POS_INC | LCD_DISPLAY_MOVE;
	LCD_sendInstruction(lcd, LCD_SET_ENTRY_MODE | lcd->cursorMovement);
}

/**
 * @brief							Sets the display to automatically increment (scroll right) after printing a character
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_setDisplayAutoInc(HD44780_LCD_t *lcd) {
	lcd->cursorMovement = LCD_CURSOR_POS_DEC | LCD_DISPLAY_MOVE;
	LCD_sendInstruction(lcd, LCD_SET_ENTRY_MODE | lcd->cursorMovement);
}

/**
 * @brief							Clears the contents displayed by the LCD
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_clearDisplay(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_CLEAR_DISPLAY);
}

/**
 * @brief							Enables the Display, i.e. its contents become visible (the display can be enabled or disabled without changing its contents)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_enableDisplay(HD44780_LCD_t *lcd) {
	lcd->displayState |= LCD_DISPLAY_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Disables the Display, i.e. its contents become invisible (the display can be enabled or disabled without changing its contents)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_disableDisplay(HD44780_LCD_t *lcd) {
	lcd->displayState &= ~LCD_DISPLAY_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Toggles the state Display, (the display can be enabled or disabled without changing its contents)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_toggleDisplay(HD44780_LCD_t *lcd) {
	lcd->displayState ^= LCD_DISPLAY_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Sets the cursor (location to display the next character) to the home position
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_setCursorHome(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_SET_CURSOR_HOME);
}

/**
 * @brief							Sets the position of the cursor (location to display the next character) to a custom location
 *
 * @param		lcd					Pointer to LCD structure
 * @param		row					Row number (0 or 1) of the cursor
 * @param		col					Column number (0 to 15) of the cursor
 */
void LCD_setCursorPos(HD44780_LCD_t *lcd, const uint32_t row, const uint32_t col) {
	LCD_sendInstruction(lcd,
			LCD_SET_DDRAMADDR
					| (((row) ? (LCD_ORIG_ADDR_SECOND) : (LCD_ORIG_ADDR_FIRST))
							+ col));
}

/**
 * @brief							Makes the underscore-style cursor visible
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_enableCursor(HD44780_LCD_t *lcd) {
	lcd->displayState |= LCD_CURSOR_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Makes the underscore-style cursor invisible
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_disableCursor(HD44780_LCD_t *lcd) {
	lcd->displayState &= ~LCD_CURSOR_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Toggles the visibility of the underscore-style cursor
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_toggleCursor(HD44780_LCD_t *lcd) {
	lcd->displayState ^= LCD_CURSOR_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Makes the blinking cursor visible
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_enableBlinkingCursor(HD44780_LCD_t *lcd) {
	lcd->displayState |= LCD_BLINK_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Makes the blinking cursor invisible
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_disableBlinkingCursor(HD44780_LCD_t *lcd) {
	lcd->displayState &= ~LCD_BLINK_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Toggles the visibility of the blinking cursor
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_toggleBlinkingCursor(HD44780_LCD_t *lcd) {
	lcd->displayState ^= LCD_BLINK_ENABLE;
	LCD_sendInstruction(lcd, LCD_CONTROL_DISPLAY | lcd->displayState);
}

/**
 * @brief							Moves the cursor one-position to the left (the cursor wraps around to the right if it is already at the left-most position)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_moveCursorLeft(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_SHIFT_CURSOR | LCD_CURSOR_MOVE_LT);
}

/**
 * @brief							Moves the cursor one-position to the right (the cursor wraps around to the left if it is already at the left-most position)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_moveCursorRight(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_SHIFT_CURSOR | LCD_CURSOR_MOVE_RT);
}

/**
 * @brief							Moves the contents of the display one-position to the left (characters at the left-most position get wrapped around to the right)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_scrollDisplayLeft(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_SHIFT_CURSOR | LCD_DISPLAY_MOVE_LT);
}

/**
 * @brief							Moves the contents of the display one-position to the right (characters at the right-most position get wrapped around to the left)
 *
 * @param		lcd					Pointer to LCD structure
 */
void LCD_scrollDisplayRight(HD44780_LCD_t *lcd) {
	LCD_sendInstruction(lcd, LCD_SHIFT_CURSOR | LCD_DISPLAY_MOVE_RT);
}

/**
 * @brief							Creates a custom glyph in the LCD's Character Memory
 *
 * @param		lcd					Pointer to the LCD structure
 * @param		loc					Location in CGRAM (0-7) where the glyph must be stored
 * @param		ar					Glyph of the character represented as an array of bytes
 */
void LCD_createCustomChar(HD44780_LCD_t *lcd, const uint32_t loc, const uint8_t glyph[8]) {
	LCD_sendInstruction(lcd, LCD_SET_CGRAMADDR | (loc << 3));

	for (uint32_t i = 0; i < 8; ++i) {
		LCD_sendData(lcd, glyph[i]);
	}
}
