/*******************************************************************
User_setup file to be added to the User_Setups directory if the TFT_Espi library
The "#include <User_Setup.h>" line in User_Setup_Select.h must then be replaced by "#include <User_Setups/TFT_ST7789_Setup.h>"
*******************************************************************/

// #define ILI9341_DRIVER
#define ST7789_DRIVER

#define TFT_RGB_ORDER TFT_BGR

#define TFT_CS   15  // Chip select broche D15
#define TFT_DC   5  // Data Command broche D5
#define TFT_RST  4  // Reset broche D4

#define TFT_MOSI 23 // SPI MOSI broche D23
#define TFT_SCLK 18 // SPI SCLK broche D18

#define TFT_WIDTH 240  // ST7789 172 x 320
#define TFT_HEIGHT 320  // ST7789 240 x 320

// #define TOUCH_CS 19     // Touch Screen Chip select pin broche D19

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

#define SPI_FREQUENCY  40000000

#define SPI_READ_FREQUENCY  20000000

#define SPI_TOUCH_FREQUENCY  2500000