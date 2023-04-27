# Examples

## Overview

The library includes examples to demonstrate its usage. Presently, the examples have been tested on and are available for the following boards -

- [STM32G071RB-NUCLEO](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html)

## Usage

This section explains how to use the examples with STM32CubeIDE, but the process should be similar with other IDEs as well. For instructions to connect the LCD to your microcontroller, refer to the README within the microcontroller's directory.

Before using the examples, the ```libHD44780_LCD.a``` archive file must be built. To do so, import the library into STM32CubeIDE, and build the project as usual. Make sure to allow STM32CubeIDE to search for and import nested projects, by means of which the examples will be automatically imported as well. After this, the examples can be built one by one as well. For detailed instructions on importing and building the library, refer to the top-level README.

**By default, the library and examples are built with the Debug Profile active. The examples will not be able to find the ```libHD44780_LCD.a``` file if the library is built with any other profile. To fix this, change the name of the ```Debug/``` directory within the library search path to the profile that was used. Refer to the top-level README for seeing how the library search paths can be updated.**
