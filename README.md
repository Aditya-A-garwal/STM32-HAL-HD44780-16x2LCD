# STM32-HAL-HD44780-16x2LCD

## Overview
This is an easy-to-use library for ARM based STM32 microcontrollers to drive 16x2 LCDs based on the HD44780 Controller. It allows the display to be controlled in the following modes -

- *4-bit mode* - Requires 6 GPIO pins from the microcontroller (4 for the bus and 2 for RS & EN) to drive the display.
- *8-bit mode* - Requires 10 GPIO pins from the microcontroller (8 for the bus and 2 for RS & EN) to drive the display.
- *Shift Register* - Requires 5 GPIO pins from the microcontorller (3 for the shift register and 2 for RS & EN) to drive the display.
- *PC8574 I2C IO Extender* - Requires 2 pins from the microcontroller (a single I2C interface).

The library only supports writing to the display memory, and does not use the RW Pin as such, which can be wired to ground. The library and examples have been written in STM32CubeIDE and uses the STM32Cube HAL APIs to control the required peripherals (GPIO Pins and I2C interface) and create delays.

This README aims to explain the APIs provided by the library along with how to use it in your own projects, and is accordingly divided into sections.

## Examples

Examples have also been provided with the library to demonstrate its usage. Navigate to the ```Examples/``` directory for more information. As of now, the libraries have only been tested with the [NUCLEO-STM32G071RB](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) Board, which is based on ARM Cortex M0+ design.

## Usage

The process to use the library in your own projects via consists only of a few simple steps. This section covers how to use the library with the STM32CubeIDE, but the process should be similar for other IDEs as well. For a usage guide on the examples, navigate to the ```Examples/``` directory.

The steps to use the library in STM32CubeIDE along with your own project are shown below -

1. Importing and building the library
    - Clone the repository and import it within STM32CubeIDE by navigating to *File>import>General>Projects from Folder or Archive* and selecting the repository. Note that the name of the project is different from the name of the repository. This should also import the examples.
    - Select the project in the *Project Explorer* and click the build button in the *toolbar* to build it. This should create an archive file called ```libHD44780_LCD.a```, which can be seen in the Archives drop-down under the *HD44780_LCD* Project.
2. Using the library in your own projects
    - First, the include path of the project must be updated so that it can find the ```HD44780_LCD.h``` header file. Select the Project and open its *Properties*.
    - Navigate to *C/C++ Build>Settings* and then to *MCU GCC Compiler>Include Paths*. In the list of Include paths, add the ```Src/``` directory within the ```HD44780_LCD``` Project. This can be done as a relative path, absolute path or by using variables, according to the project's requirements. Apply and Close.
    - Next, the archive file must be added to the linker to allow it to be linked with the final binary. Once again, select the Project and open its *Properties*.
    - Navigate to *C/C++ Build>Settings* and then to *MCU GCC Linker>Libraries*. In the list of Libraries, add ```HD44780_LCD```. The linker automatically adds the ```lib``` prefix and ```.a``` extension.
    - In the list of Library Search Paths, add the path to the ```Debug/``` directory of the ```HD44780_LCD``` Project. If the library is built with the *Release* Profile, add the ```Release/``` directory instead. Apply and Close.
    - Finally, to automatically build the library while building the project, open the Project's *Properties* and navigate to *Project References*. Select the HD44780_LCD Project. Apply and Close.
    - Include the ```HD44780_LCD.h``` header file to enable intellisense and autocomplete by the IDE.

The library allows flexibility in choosing pins to drive the display. For more information and examples on wiring the display to the LCD, navigate to the ```Examples/``` directory.

## Documentation

A brief documentation of the structures and functions provided by the library are shown below. For detailed instructions, refer to the doxygen compliant documentation within the ```HD44780_LCD.c``` file.

### Structures

The list of structures provided by the library is shown below -

|Name|Description|
|-|-|
|LCD_HD4480_t|Structure to encapsulate the GPIO Pins and state of a physical LCD display|

### Functions

The list of functions provided by the library (along with brief descriptions) is shown below.

|Name|Description|
|-|-|
|```LCD_createHalfBus```|Initialize an ```LCD_HD44780_t``` instance structure to control the LCD in 4-bit mode| <!-- initialization of structure -->
|```LCD_createFullBus```|Initialize an ```LCD_HD44780_t``` instance structure to control the LCD in 8-bit mode|
|```LCD_createShiftRegister```|Initialize an ```LCD_HD44780_t``` instance structure to control the LCD in 4-bit mode via a shift register|
|```LCD_createI2C```|Initialize an ```LCD_HD44780_t``` instance structure to control the LCD via a PC8574 I2C IO Expander (uses the default 0x27 address)|
|```LCD_createI2C_addr```|Initialize an ```LCD_HD44780_t``` instance structure to control the LCD via a PC8574 I2C IO Exapnder (accepts a custom address)|
|```LCD_init```|Initialize the physical LCD according to the settings provided to the ```LCD_HD44780_t``` instance during its initialization| <!-- initialization of LCD hardware -->
|```LCD_sendNibble```|Send a single nibble of data to the LCD when in 4-bit mode, i.e. if the LCD was setup via ```LCD_createHalfBus``` **(this function should not normally be needed while using the library, and is only meant for advanced usage)**| <!-- private functions for sending values -->
|```LCD_sendByte```|Send a single byte of data to the LCD when in 8-bit mode, i.e. if the LCD was setup via ```LCD_createFullBus``` **(this function should not normally be needed while using the library, and is only meant for advanced usage)**|
|```LCD_shiftByte```|Shift a single byte of data to the LCD via a shift register, i.e. if the LCD was setup via ```LCD_createShiftRegister``` **(this function should not normally be needed while using the library, and is only meant for advanced usage)**|
|```LCD_sendNibble_I2C```|Send a single nibble of data to the LCD via the PC8574 I2C IO Expander, i.e. if the LCD was setup via ```LCD_createI2C``` or ```LCD_createI2C_addr``` **(this function should not normally be needed while using the library, and is only meant for advanced usage)**|
|```LCD_sendInstruction```|Send a single byte instruction (along with its masked parameters) to the LCD (agnostic to how the LCD is being driven)|
|```LCD_sendData```|Send a single byte of data to the LCD (agnostic to how the LCD is being driven)|
|```LCD_sendBuffer```|Send a buffer of data to the LCD (agnostic to how the LCD is being driven)|
|```LCD_enableBacklight```|Enable the backlight of the LCD (only applicable when the LCD is driven via I2C)| <!-- backlight control (I2C only) -->
|```LCD_disableBacklight```|Disable the backlight of the LCD (only applicable when the LCD is driven via I2C)|
|```LCD_toggleBacklight```|Toggle the backlight of the LCD (only applicable when the LCD is driven via I2C)|
|```LCD_setCursorAutoDec```|Set the LCD cursor to automatically decrement/move left after printing a character| <!-- entry behaviour control -->
|```LCD_setCursorAutoInc```|Set the LCD cursor to automatically increment/move right after printing a character|
|```LCD_setDisplayAutoDec```|Set the LCD to to automatically shift the display left after printing a character|
|```LCD_setDisplayAutoInc```|Set the LCD to to automatically shift the display right after printing a character|
|```LCD_clearDisplay```|Clear the contents being displayed by the LCD **(this takes ~2 milliseconds to execute, during when any instructions/data sent to the display will cause it to malfunction)**| <!-- display management -->
|```LCD_disableDisplay```|Hide the contents of the display without deleting it from memory|
|```LCD_enableDisplay```|Stop hiding the contents of the display|
|```LCD_toggleDisplay```|Toggles being the display contents being hidden and visible|
|```LCD_setCursorHome```|Set the cursor's position to the top-left| <!-- cursor control -->
|```LCD_setCursorPos```|Set the cursor's position to the specified row and column|
|```LCD_enableCursor```|Enable displaying the underline cursor|
|```LCD_disableCursor```|Disable displaying the underline cursor|
|```LCD_toggleCursor```|Toggle the visibility of the underline cursor|
|```LCD_enableBlinkingCursor```|Enable displaying the blinking cursor|
|```LCD_disableBlinkingCursor```|Disable displaying the blinking cursor|
|```LCD_toggleBlinkingCursor```|Toggle the visibility of the blinking cursor|
|```LCD_moveCursorLeft```|Move the cursor one position to the left (wraps around to the right in case of an underflow)| <!-- movement of display and cursor -->
|```LCD_moveCursorRight```|Move the cursor one position to the right (wraps around to the left in case of an overflow)|
|```LCD_scrollDisplayLeft```|Move the display contents one position to the left (characters at the left wrap around to the right)|
|```LCD_scrollDisplayRight```|Move the display contennts one position to the right (characters at the right wrap around to the left)|
|```LCD_createCustomChar```|Create a custom glyph to use with the LCD (the LCD can store 8 such glyphs at a time)|
