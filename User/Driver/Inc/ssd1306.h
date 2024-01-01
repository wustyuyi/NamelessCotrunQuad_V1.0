#ifndef __SSD1306_LIB_H
#define __SSD1306_LIB_H

#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

#include <stdint.h>

typedef volatile uint8_t PortReg;
typedef uint32_t PortMask;





#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define SSD1306_I2C_ADDRESS   (0x3C)	// 011110+SA0+RW - 0x3C or 0x3D
// Address for 128x32 is 0x3C
// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)

/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
    Select the appropriate display below to create an appropriately
    sized framebuffer, etc.
    SSD1306_128_64  128x64 pixel display
    SSD1306_128_32  128x32 pixel display
    SSD1306_96_16
    -----------------------------------------------------------------------*/
#define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16
/*=========================================================================*/


#if defined SSD1306_128_64
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
#endif


#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


int16_t ssd1306_width(void);
int16_t ssd1306_height(void);
void set_rotation(uint8_t x);
void ssd1306_init(uint32_t dc, uint32_t rs, uint32_t cs, uint32_t clk, uint32_t mosi);
void ssd1306_init_i2c(uint32_t scl, uint32_t sda);
void ssd1306_command(uint8_t c);
void ssd1306_begin(uint8_t vccstate);
void ssd1306_draw_pixel(int16_t x, int16_t y, uint16_t color);
void ssd1306_invert_display(uint8_t i);
void ssd1306_start_scroll_right(uint8_t start, uint8_t stop);
void ssd1306_start_scroll_left(uint8_t start, uint8_t stop);
void ssd1306_start_scroll_diag_right(uint8_t start, uint8_t stop);
void ssd1306_start_scroll_diag_left(uint8_t start, uint8_t stop);
void ssd1306_stop_scroll(void);
void ssd1306_dim(uint8_t dim);
void ssd1306_data(uint8_t c);
void ssd1306_display(void);
void ssd1306_clear_display(void);
void ssd1306_draw_fast_hline(int16_t x, int16_t y, int16_t w, uint16_t color);
void ssd1306_draw_fast_hline_internal(int16_t x, int16_t y, int16_t w, uint16_t color);
void ssd1306_draw_fast_vline(int16_t x, int16_t y, int16_t h, uint16_t color);
void ssd1306_draw_fast_vline_internal(int16_t x, int16_t __y, int16_t __h, uint16_t color);
void ssd1306_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ssd1306_draw_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void ssd1306_fill_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ssd1306_fill_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void ssd1306_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ssd1306_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ssd1306_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ssd1306_fill_screen(uint16_t color);
void ssd1306_draw_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ssd1306_fill_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ssd1306_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ssd1306_fill_triangle( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ssd1306_draw_bitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
void ssd1306_draw_bitmap_bg(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
void ssd1306_draw_xbitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
size_t ssd1306_write(uint8_t c);
void ssd1306_draw_char(int16_t x, int16_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size);
void ssd1306_set_cursor(int16_t x, int16_t y);
int16_t ssd1306_get_cursor_x(void);
int16_t ssd1306_get_cursor_y(void);
void ssd1306_set_textsize(uint8_t s);
void ssd1306_set_textcolor(uint16_t c);
void ssd1306_set_textcolor_bg(uint16_t c, uint16_t b);
void ssd1306_set_textwrap(uint8_t w);
uint8_t ssd1306_get_rotation(void);
void ssd1306_set_rotation(uint8_t x);
void ssd1306_cp437(uint8_t x);
void ssd1306_putstring(char* buffer);
void ssd1306_puts(char* buffer);
void draw_oled(void);

#endif /* __SSD1306_LIB_H */

