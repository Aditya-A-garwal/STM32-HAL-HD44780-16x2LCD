# STM32-G071RB-Nucleo

## Overview

This README covers how to use the examples for the [STM32G071RB-NUCLEO](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) board, which contains the STM32G071RB microcontroller based on the ARM Cortex M0+ design. Each section is divided into 4 parts based on the mode in which the LCD is driven (4-bit mode, 8-bit mode, via Shift Register, via I2C). For detailed instructions on importing and building the projects, refer to the README within the ```Examples/``` directory.

## Connecting the LCD to the Microcontroller

The LCD with its pins labelled is shown below -

### 4-bit Mode

|LCD Pin|Nucleo Connector|GPIO Port|GPIO Pin|
|-|-|-|-|
|GND|GND/0v|-|-|
|VCC|5v|-|-|
|V0|variable voltage between GND and VCC (used to vary contrast)|-|-|
|RW|GND/0v|-|-|
|RS|A0|Port A|Pin 0|
|EN|A1|Port A|Pin 1|
|D0|GND|-|-|
|D1|GND|-|-|
|D2|GND|-|-|
|D3|GND|-|-|
|D4|A2|Port A|Pin 4|
|D5|D13|Port A|Pin 5|
|D6|D12|Port A|Pin 6|
|D7|D11|Port A|Pin 7|
|LED (Anode)|5v via a 220 Ohm current-limiting resistor (power for backlight)|-|-|
|LED (Cathode)|0v (ground for backlight)|-|-|

### 8-bit Mode

|LCD Pin|Nucleo Connector|GPIO Port|GPIO Pin|
|-|-|-|-|
|GND|GND/0v|-|-|
|VCC|5v|-|-|
|V0|variable voltage between GND and VCC (used to vary contrast)|-|-|
|RW|GND/0v|-|-|
|RS|A0|Port A|Pin 0|
|EN|A1|Port A|Pin 1|
|D0|D7|Port A|Pin 8|
|D1|D8|Port A|Pin 9|
|D2|D2|Port A|Pin 10|
|D3|D6|Port B|Pin 14|
|D4|A2|Port A|Pin 4|
|D5|D13|Port A|Pin 5|
|D6|D12|Port A|Pin 6|
|D7|D11|Port A|Pin 7|
|LED (Anode)|5v via a 220 Ohm current-limiting resistor (power for backlight)|-|-|
|LED (Cathode)|0v (ground for backlight)|-|-|

### Via HC74595 Shift Register

|LCD Pin|Nucleo Connector|GPIO Port|GPIO Pin|
|-|-|-|-|
|GND|GND/0v|-|-|
|VCC|5v|-|-|
|V0|variable voltage between GND and VCC (used to vary contrast)|-|-|
|RW|GND/0v|-|-|
|RS|A0|Port A|Pin 0|
|EN|A1|Port A|Pin 1|
|LED (Anode)|5v via a 220 Ohm current-limiting resistor (power for backlight)|-|-|
|LED (Cathode)|0v (ground for backlight)|-|-|

|LCD Pin|Shift Register Pin|
|-|-|
|D0|O7|
|D1|O6|
|D2|O5|
|D3|O4|
|D4|O3|
|D5|O2|
|D6|O1|
|D7|O0|

|Shift Register Pin|Nucleo Connector|GPIO Port|GPIO Pin|
|-|-|-|-|
|VCC|5v|-|-|
|In|D7|Port A|Pin 8|
|Enable|GND|-|-|
|Latch|D2|Port A|Pin 10|
|Clock|D8|Port A|Pin 9|
|Reset|5V|-|-|
|Out|-|-|-|
|GND|GND|-|-|

### Via PC8574 I2C Expander

|PC8754 Pin|Nucleo Connector|Microcontroller Pin|
|-|-|-|
|VCC|5v|-|
|GND|GND/0v|-|
|SDA|D15|I2C1 SDA (PB9)|
|SCL|D14|I2C1 SCL (PB8)|

## Selecting how the LCD is driven

Each of the examples include the following code snippet within the ```main``` function in the ```Src/main.c``` file -
```c
    // The LCD can be used in one of 4 modes, and the initialization of the structure depends upon which one is used
    // snippets are shown below for all 4 modes; un-comment the one to use
    // for more information, including wiring diagrams, refer to the README.md files

    // This initializes the structure to use the LCD in 4-bit mode (utilize half of the 8-bit bus)
    // LCD_createHalfBus(&lcd, LCD_D4_GPIO_Port, LCD_D4_Pin, LCD_D5_GPIO_Port, LCD_D5_Pin, LCD_D6_GPIO_Port, LCD_D6_Pin, LCD_D7_GPIO_Port, LCD_D7_Pin, LCD_EN_GPIO_Port, LCD_EN_Pin, LCD_RS_GPIO_Port, LCD_RS_Pin);

    // This initializes the structure to use the LCD in 8-bit mode (utilize the complete 8-bit bus)
    // LCD_createFullBus(&lcd, LCD_D0_GPIO_Port, LCD_D0_Pin, LCD_D1_GPIO_Port, LCD_D1_Pin, LCD_D2_GPIO_Port, LCD_D2_Pin, LCD_D3_GPIO_Port, LCD_D3_Pin, LCD_D4_GPIO_Port, LCD_D4_Pin, LCD_D5_GPIO_Port, LCD_D5_Pin, LCD_D6_GPIO_Port, LCD_D6_Pin, LCD_D7_GPIO_Port, LCD_D7_Pin, LCD_EN_GPIO_Port, LCD_EN_Pin, LCD_RS_GPIO_Port, LCD_RS_Pin);

    // This initializes the structure to use the LCD in 8-bit mode along with a shift register
    // The D0 Pin is used as a Data Pin for the shift register
    // The D1 Pin is used as a Clock Pin for the shift register
    // The D2 Pin is used as a Latch Pin for the shift register
    // LCD_createShiftRegister(&lcd, LCD_D0_GPIO_Port, LCD_D0_Pin, LCD_D1_GPIO_Port, LCD_D1_Pin, LCD_D2_GPIO_Port, LCD_D2_Pin, LCD_EN_GPIO_Port, LCD_EN_Pin, LCD_RS_GPIO_Port, LCD_RS_Pin);

    // This initializes the structure to use the LCD in 4-bit mode along with a PC8574 I2C IO Expander
    // LCD_createI2C(&lcd, &hi2c1);
```

Uncomment the line that initializes the structure according to how it is wired to the microcontroller. **For a single ```LCD_HD44780_t``` instance, only one mode can be used at a time**. The rest of the code can be left as-is.
