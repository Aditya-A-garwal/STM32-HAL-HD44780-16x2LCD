/**
 ******************************************************************************
 * @file     HD44780_LCD.h
 * @author   Aditya Agarwal (aditya.agarwal@dumblebots.com)
 * @version  V1.0
 * @date     13/04/2023 13:43:50
 * @brief    Contains declarations of the functions to drive 16x2 Character Liquid Crystal Displays along with the HD44780 Controller
 ******************************************************************************
 */

#ifndef HD44780_LCD_H_
#define HD44780_LCD_H_

// get the lower nibble (4 least significant bits) of a byte
#define   LO_NIBBLE(x)          (((x) >> 0) & 0x0f)

// get the higher nibble (4 most significant bits) of a byte
#define   HI_NIBBLE(x)          (((x) >> 4) & 0x0f)

// instruction to clear the display
#define   LCD_CLEAR_DISPLAY     0x01

// instruction to set the position of the cursor back to origin
#define   LCD_SET_CURSOR_HOME   0x02

// instruction to set the entry mode of the LCD display (direction of cursor/display movement)
#define   LCD_SET_ENTRY_MODE    0x04
// mask to denote that the cursor should move relative to the display, while the absolute position of the display remains constant
#define   LCD_CURSOR_MOVE       0x00
// mask to denote that the display should move relative to the cursor, while the absolute position of the cursor remains constant
#define   LCD_DISPLAY_MOVE      0x01
// mask to denote that the cursor should move left (DDRAM address decrements) each time a character is written
#define   LCD_CURSOR_POS_DEC    0x00
// mask to denote that the cursor should move right (DDRAM address increments) each time a character is written
#define   LCD_CURSOR_POS_INC    0x02

// instruction to control the LCD display (whether the display/cursor/blink is enabled or not)
#define   LCD_CONTROL_DISPLAY   0x08
// mask to denote that the blinking cursor is disabled
#define   LCD_BLINK_DISABLE     0x00
// mask to denote that the blinking cursor is enabled
#define   LCD_BLINK_ENABLE      0x01
// mask to denote that the underscore cursor is disabled
#define   LCD_CURSOR_DISABLE    0x00
// mask to denote that the underscore cursor is enabled
#define   LCD_CURSOR_ENABLE     0x02
// mask to denote that the LCD Display is disabled
#define   LCD_DISPLAY_DISABLE   0x00
// mask to denote that the LCD Display is enabled
#define   LCD_DISPLAY_ENABLE    0x04

// instruction to move the cursor/display left or right
#define   LCD_SHIFT_CURSOR      0x10
// mask to denote that the cursor should move left
#define   LCD_CURSOR_MOVE_LT    0x00
// mask to denote that the cursor should move right
#define   LCD_CURSOR_MOVE_RT    0x04
// mask to denote that the display should move left
#define   LCD_DISPLAY_MOVE_LT   0x08
// mask to denote that the display should move right
#define   LCD_DISPLAY_MOVE_RT   0x0C

// instruction to set the function of the LCD (4-bit/8-bit bus, 1/2 line mode, 8/11 columns in the cell)
#define   LCD_SET_FUNCTION      0x20
// mask to denote that the count of dots in a column of the display is 8
#define   LCD_DOT_COUNT_8       0x00
// mask to denote that the count of dots in a column of the display is 11
#define   LCD_DOT_COUNT_11      0x04
// mask to denote that the number of lines in the LCD display is 1
#define   LCD_LINE_COUNT_1      0x00
// mask to denote that the number of lines in the LCD display is 2
#define   LCD_LINE_COUNT_2      0x08
// mask to denote that the bus is 4 lines wide
#define   LCD_BUS_SIZE_4        0x00
// mask to denote that the bus is 8 lines wide
#define   LCD_BUS_SIZE_8        0x10

// instruction to set the address in the CGRAM (where the subsequent data will be written to)
#define   LCD_SET_CGRAMADDR     0x40

// instruction to set the address in the DDRAM (where the subsequent data will be written to)
#define   LCD_SET_DDRAMADDR     0x80

// address of the first position in single-line mode
#define   LCD_ORIG_ADDR_SINGLE  0x00
// address of the first position of the first line in two-line mode
#define   LCD_ORIG_ADDR_FIRST   0x00
// address of the first position of the second line in two-line mode
#define   LCD_ORIG_ADDR_SECOND  0x40
// the width of a single line of the LCD
#define   LCD_LINE_SIZE         0x28

// the default address of the I2C Peripheral that controls the LCD
#define	  DEFAULT_I2C_ADDR		(0x27<<1)

// the index of the bit that manages the RS pin of the LCD
#define   RS_ID					0
// the index of the bit that manages the RW pin of the LCD
#define   RW_ID					1
// the index of the bit that manages the EN pin of the LCD
#define   EN_ID					2
// the index of the bit that manages the backlight of the LCD
#define	  BACKLIGHT_ID			3

enum HD44780_LCD_BUS_MODE {
	halfBus, fullBus, shiftReg, I2C
};

/** Structs ------------------------------------------------------------------*/
typedef struct HD44780_LCD_t {

	I2C_HandleTypeDef *I2CHandle;
	uint32_t backlightMask;
	uint32_t I2CAddr;

	GPIO_TypeDef *dataPort[8];

	GPIO_TypeDef *enPort;
	GPIO_TypeDef *rsPort;

	uint16_t dataPin[8];

	uint32_t enPin :16;
	uint32_t rsPin :16;

	uint32_t displayState :16;
	uint32_t cursorMovement :16;

	enum HD44780_LCD_BUS_MODE busMode;
} HD44780_LCD_t;

/** Functions ----------------------------------------------------------------*/
void LCD_createHalfBus(HD44780_LCD_t *lcd, GPIO_TypeDef *port0, uint16_t pin0,
		GPIO_TypeDef *port1, uint16_t pin1, GPIO_TypeDef *port2, uint16_t pin2,
		GPIO_TypeDef *port3, uint16_t pin3, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin);
void LCD_createFullBus(HD44780_LCD_t *lcd, GPIO_TypeDef *port0, uint16_t pin0,
		GPIO_TypeDef *port1, uint16_t pin1, GPIO_TypeDef *port2, uint16_t pin2,
		GPIO_TypeDef *port3, uint16_t pin3, GPIO_TypeDef *port4, uint16_t pin4,
		GPIO_TypeDef *port5, uint16_t pin5, GPIO_TypeDef *port6, uint16_t pin6,
		GPIO_TypeDef *port7, uint16_t pin7, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin);
void LCD_createShiftRegister(HD44780_LCD_t *lcd, GPIO_TypeDef *dataPort,
		uint16_t dataPin, GPIO_TypeDef *clockPort, uint16_t clockPin,
		GPIO_TypeDef *latchPort, uint16_t latchPin, GPIO_TypeDef *enPort,
		uint16_t enPin, GPIO_TypeDef *rsPort, uint16_t rsPin);
void LCD_createI2C(HD44780_LCD_t *lcd, I2C_HandleTypeDef *I2CHandle);
void LCD_createI2C_addr(HD44780_LCD_t *lcd, I2C_HandleTypeDef *I2CHandle, uint8_t lcdAddr);

void LCD_init(HD44780_LCD_t *lcd);

void LCD_sendNibble(HD44780_LCD_t *lcd, uint8_t nibble);
void LCD_sendByte(HD44780_LCD_t *lcd, uint8_t byte);
void LCD_shiftByte(HD44780_LCD_t *lcd, uint8_t byte);
void LCD_sendNibble_I2C(HD44780_LCD_t *lcd, uint8_t nibble);
void LCD_sendInstruction(HD44780_LCD_t *lcd, uint8_t instruction);
void LCD_sendData(HD44780_LCD_t *lcd, const uint8_t data);
void LCD_sendBuffer(HD44780_LCD_t *lcd, const uint8_t *buf, const uint32_t len);

void LCD_enableBacklight(HD44780_LCD_t *lcd);
void LCD_disableBacklight(HD44780_LCD_t *lcd);
void LCD_toggleBacklight(HD44780_LCD_t *lcd);

void LCD_setCursorAutoDec(HD44780_LCD_t *lcd);
void LCD_setCursorAutoInc(HD44780_LCD_t *lcd);
void LCD_setDisplayAutoDec(HD44780_LCD_t *lcd);
void LCD_setDisplayAutoInc(HD44780_LCD_t *lcd);

void LCD_clearDisplay(HD44780_LCD_t *lcd);
void LCD_enableDisplay(HD44780_LCD_t *lcd);
void LCD_disableDisplay(HD44780_LCD_t *lcd);
void LCD_toggleDisplay(HD44780_LCD_t *lcd);

void LCD_setCursorHome(HD44780_LCD_t *lcd);
void LCD_setCursorPos(HD44780_LCD_t *lcd, const uint32_t row, const uint32_t col);
void LCD_enableCursor(HD44780_LCD_t *lcd);
void LCD_disableCursor(HD44780_LCD_t *lcd);
void LCD_toggleCursor(HD44780_LCD_t *lcd);

void LCD_enableBlinkingCursor(HD44780_LCD_t *lcd);
void LCD_disableBlinkingCursor(HD44780_LCD_t *lcd);
void LCD_toggleBlinkingCursor(HD44780_LCD_t *lcd);

void LCD_moveCursorLeft(HD44780_LCD_t *lcd);
void LCD_moveCursorRight(HD44780_LCD_t *lcd);
void LCD_scrollDisplayLeft(HD44780_LCD_t *lcd);
void LCD_scrollDisplayRight(HD44780_LCD_t *lcd);
void LCD_createCustomChar(HD44780_LCD_t *lcd, const uint32_t loc, const uint8_t ar[8]);

#endif /* HD44780_LCD_H_ */
