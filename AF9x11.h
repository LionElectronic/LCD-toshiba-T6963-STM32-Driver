/*
    created with FontEditor written by H. Reddmann
    HaReddmann at t-online dot de

    File Name           : AF9x11.h
    Date                : 3/3/2021
    Font size in bytes  : 0x09B6, 2486
    Font width          : 13
    Font height         : 12
    Font first char     : 0x00
    Font last char      : 0xFF
    Font bits per pixel : 1
    Font is compressed  : false

    The font data are defined as

    struct _FONT_ {
     // common shared fields
       uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
       uint8_t    font_Width_in_Pixel_for_fixed_drawing;
       uint8_t    font_Height_in_Pixel_for_all_Characters;
       uint8_t    font_Bits_per_Pixels;
                    // if MSB are set then font is a compressed font
       uint8_t    font_First_Char;
       uint8_t    font_Last_Char;
       uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
                    // for each character the separate width in pixels,
                    // characters < 128 have an implicit virtual right empty row
                    // characters with font_Char_Widths[] == 0 are undefined

     // if compressed font then additional fields
       uint8_t    font_Byte_Padding;
                    // each Char in the table are aligned in size to this value
       uint8_t    font_RLE_Table[3];
                    // Run Length Encoding Table for compression
       uint8_t    font_Char_Size_in_Bytes[font_Last_Char - font_First_Char +1];
                    // for each char the size in (bytes / font_Byte_Padding) are stored,
                    // this get us the table to seek to the right beginning of each char
                    // in the font_data[].

     // for compressed and uncompressed fonts
       uint8_t    font_data[];
                    // bit field of all characters
    }
*/

#ifndef AF9x11_H
#define AF9x11_H


#define AF9x11_WIDTH 13
#define AF9x11_HEIGHT 12

const unsigned char AF9x11[] = {
    0x09, 0xB6, 0x0D, 0x0C, 0x01, 0x00, 0xFF,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x08, 0x07, 0x08, 0x07, 0x08, 0x07, 0x0A, 0x0A, 0x09, 
    0x03, 0x03, 0x06, 0x07, 0x08, 0x08, 0x07, 0x08, 0x08, 0x06, 0x09, 0x07, 0x02, 0x03, 0x03, 0x03, 
    0x04, 0x02, 0x04, 0x08, 0x06, 0x0C, 0x08, 0x02, 0x04, 0x04, 0x06, 0x08, 0x03, 0x06, 0x02, 0x09, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x02, 0x03, 0x07, 0x08, 0x07, 0x06, 
    0x0A, 0x08, 0x07, 0x07, 0x08, 0x07, 0x06, 0x08, 0x08, 0x04, 0x05, 0x07, 0x06, 0x09, 0x08, 0x09, 
    0x07, 0x09, 0x07, 0x07, 0x08, 0x08, 0x08, 0x0C, 0x07, 0x08, 0x07, 0x04, 0x0A, 0x04, 0x08, 0x06, 
    0x03, 0x06, 0x07, 0x06, 0x07, 0x07, 0x05, 0x07, 0x07, 0x02, 0x04, 0x06, 0x02, 0x0A, 0x07, 0x07, 
    0x07, 0x07, 0x04, 0x05, 0x05, 0x07, 0x06, 0x0A, 0x06, 0x06, 0x05, 0x06, 0x02, 0x06, 0x08, 0x06, 
    0x06, 0x08, 0x03, 0x06, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0A, 0x05, 0x06, 0x06, 0x03, 0x03, 
    0x03, 0x08, 0x03, 0x05, 0x05, 0x08, 0x06, 0x06, 0x03, 0x02, 0x07, 0x05, 0x09, 0x08, 0x07, 0x09, 
    0x09, 0x03, 0x03, 0x08, 0x06, 0x07, 0x00, 0x05, 0x09, 0x08, 0x06, 0x06, 0x0F, 0x08, 0x08, 0x10, 
    0x05, 0x07, 0x07, 0x09, 0x00, 0x09, 0x0A, 0x03, 0x0E, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x07, 
    0x03, 0x04, 0x05, 0x04, 0x05, 0x04, 0x08, 0x02, 0x08, 0x06, 0x08, 0x08, 0x06, 0x06, 0x06, 0x05, 
    0x05, 0x03, 0x03, 0x0D, 0x0D, 0x0C, 0x0C, 0x08, 0x06, 0x06, 0x05, 0x05, 0x03, 0x08, 0x08, 0x08, 
    0x00, 0x06, 0x00, 0x06, 0x06, 0x05, 0x05, 0x07, 0x07, 0x07, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 
    0x06, 0x06, 0x03, 0x03, 0x00, 0x07, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x00, 0x03, 0x08, 0x03, 
    
    0x00, 0xE0, 0x0F, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0xC0, 0x84, 0x10, 0x00, 0x81, 0x0C, 0x08, 
    0x21, 0x10, 0xC8, 0x00, 0x10, 0x00, 0x01, 0x12, 0x10, 0x01, 0x51, 0xA0, 0x00, 0x0C, 0x80, 0x00, 
    0x70, 0xA0, 0x08, 0x8A, 0x60, 0x0A, 0x84, 0x40, 0x08, 0x04, 0x00, 0x01, 0x10, 0x20, 0x01, 0x11, 
    0x10, 0x01, 0x0A, 0xC0, 0x00, 0x08, 0x00, 0x07, 0x8A, 0xA0, 0x08, 0x86, 0x40, 0x08, 0x84, 0x40, 
    0x00, 0x10, 0x00, 0x01, 0x12, 0x10, 0x41, 0x11, 0xA0, 0x00, 0x0C, 0x80, 0x00, 0x70, 0xA0, 0x08, 
    0x8A, 0x60, 0x88, 0x84, 0x40, 0x08, 0x04, 0x00, 0x01, 0x10, 0xC0, 0x00, 0x10, 0x00, 0x01, 0x10, 
    0xC0, 0x00, 0x10, 0x00, 0x01, 0x0E, 0x00, 0x01, 0x10, 0xC0, 0x00, 0x10, 0x00, 0x81, 0x10, 0xC2, 
    0x80, 0x10, 0x00, 0x01, 0x0E, 0x00, 0x01, 0x10, 0x80, 0x00, 0x10, 0x80, 0x01, 0x16, 0x10, 0x01, 
    0x11, 0xE0, 0x00, 0x00, 0xC0, 0x00, 0x0C, 0x00, 0xC0, 0x00, 0xF0, 0x03, 0x00, 0x0C, 0x80, 0x03, 
    0xD0, 0x03, 0x01, 0x0C, 0x00, 0x00, 0x0C, 0x80, 0x03, 0xD0, 0xC3, 0x00, 0x10, 0xC0, 0x00, 0x00, 
    0x80, 0x00, 0x3C, 0x80, 0x3F, 0x18, 0x40, 0x02, 0x24, 0x00, 0x01, 0x00, 0x00, 0x1C, 0x20, 0x42, 
    0x21, 0x88, 0x01, 0x21, 0x20, 0x02, 0x1C, 0x00, 0x00, 0x20, 0x18, 0x41, 0x0A, 0x64, 0x00, 0x02, 
    0x10, 0x00, 0x00, 0x0C, 0x00, 0x03, 0xC0, 0x00, 0x30, 0xC0, 0x00, 0x03, 0x0C, 0x00, 0x00, 0x00, 
    0x03, 0x0C, 0x30, 0xC0, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x03, 0x00, 0x18, 0x40, 0x02, 0x24, 0x80, 
    0x0F, 0x00, 0x03, 0x10, 0x00, 0x01, 0x08, 0x00, 0x41, 0x18, 0x60, 0x01, 0x11, 0x10, 0x01, 0x0E, 
    0x00, 0x01, 0x10, 0x60, 0x01, 0x19, 0x10, 0x01, 0x09, 0x80, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 
    0x01, 0x14, 0x00, 0x00, 0x14, 0xC0, 0x00, 0x00, 0x60, 0x01, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xFE, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x40, 0x80, 0x34, 0xF8, 0xE0, 0x34, 
    0xF8, 0xE0, 0x04, 0x08, 0x00, 0x00, 0x98, 0x40, 0x12, 0xFE, 0x43, 0x12, 0xC8, 0x00, 0x00, 0x1C, 
    0x20, 0x02, 0x22, 0xC0, 0x21, 0x80, 0x01, 0x07, 0x0C, 0x20, 0x1C, 0x20, 0x02, 0x22, 0xC0, 0x01, 
    0x00, 0xCC, 0x21, 0x23, 0x22, 0x22, 0x25, 0x8C, 0x01, 0x18, 0x60, 0x02, 0x00, 0x0E, 0x00, 0x00, 
    0xF8, 0x61, 0x60, 0x01, 0x08, 0x00, 0x01, 0x68, 0x60, 0xF8, 0x01, 0x00, 0x50, 0x00, 0x02, 0xF8, 
    0x00, 0x02, 0x50, 0x00, 0x00, 0x20, 0x00, 0x02, 0x20, 0xC0, 0x1F, 0x20, 0x00, 0x02, 0x20, 0x00, 
    0x00, 0x00, 0x08, 0x60, 0x00, 0x00, 0x20, 0x00, 0x02, 0x20, 0x00, 0x02, 0x20, 0x00, 0x00, 0x30, 
    0x00, 0x00, 0x20, 0x00, 0x01, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x00, 0x00, 0xFC, 
    0x21, 0x20, 0x02, 0x22, 0x20, 0x02, 0xC2, 0x1F, 0x00, 0x00, 0x00, 0x04, 0x42, 0x20, 0xFE, 0x03, 
    0x20, 0x00, 0x02, 0x00, 0x04, 0x23, 0x28, 0x42, 0x22, 0x24, 0x22, 0xC2, 0x21, 0x00, 0x40, 0x10, 
    0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x01, 0x00, 0x60, 0x00, 0x05, 0x48, 0x40, 0x04, 0xFE, 
    0x03, 0x04, 0x00, 0xE0, 0x11, 0x12, 0x22, 0x21, 0x12, 0x22, 0x21, 0xE2, 0x01, 0x00, 0xF8, 0x41, 
    0x21, 0x12, 0x22, 0x21, 0x12, 0x02, 0x1E, 0x00, 0x20, 0x00, 0x02, 0x22, 0x18, 0x62, 0xA0, 0x01, 
    0x06, 0x00, 0x00, 0xDC, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0xC2, 0x1D, 0x00, 0xC0, 0x03, 0x42, 
    0x22, 0x24, 0x42, 0x22, 0x14, 0xFC, 0x00, 0x00, 0x30, 0x03, 0x00, 0x00, 0x08, 0x66, 0x00, 0x00, 
    0x02, 0x50, 0x00, 0x05, 0x88, 0x80, 0x08, 0x04, 0x01, 0x00, 0x28, 0x80, 0x02, 0x28, 0x80, 0x02, 
    0x28, 0x80, 0x02, 0x28, 0x00, 0x00, 0x04, 0x81, 0x08, 0x88, 0x00, 0x05, 0x50, 0x00, 0x02, 0x00, 
    0x40, 0x00, 0xC2, 0x22, 0x02, 0x22, 0xC0, 0x01, 0x00, 0x00, 0x07, 0x8C, 0x41, 0x17, 0x8A, 0xA2, 
    0x28, 0xFA, 0x42, 0x08, 0x8C, 0x00, 0x07, 0x00, 0x00, 0x30, 0xE0, 0xC0, 0x09, 0x82, 0xC0, 0x09, 
    0xE0, 0x00, 0x30, 0x00, 0xE0, 0x3F, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x01, 0x00, 0xF8, 
    0x40, 0x10, 0x02, 0x22, 0x20, 0x02, 0x22, 0x20, 0x00, 0xE0, 0x3F, 0x02, 0x22, 0x20, 0x02, 0x22, 
    0x20, 0x04, 0x81, 0x0F, 0x00, 0xE0, 0x3F, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x02, 0x02, 0x00, 
    0xFE, 0x23, 0x02, 0x22, 0x20, 0x02, 0x02, 0x00, 0x00, 0xF8, 0x40, 0x10, 0x02, 0x22, 0x20, 0x22, 
    0x22, 0x22, 0xE4, 0x03, 0x00, 0xFE, 0x03, 0x02, 0x20, 0x00, 0x02, 0x20, 0x00, 0x02, 0xFE, 0x03, 
    0x00, 0x02, 0xE2, 0x3F, 0x02, 0x02, 0x00, 0x00, 0x22, 0x20, 0x02, 0xE2, 0x1F, 0x00, 0xE0, 0x3F, 
    0x20, 0x00, 0x05, 0x88, 0x40, 0x10, 0x02, 0x02, 0x00, 0xFE, 0x03, 0x20, 0x00, 0x02, 0x20, 0x00, 
    0x02, 0x00, 0xFE, 0x63, 0x00, 0x38, 0x00, 0x0C, 0xC0, 0x80, 0x03, 0x06, 0xE0, 0x3F, 0x00, 0xE0, 
    0x3F, 0x06, 0x80, 0x01, 0x20, 0x00, 0x0C, 0x00, 0xE3, 0x3F, 0x00, 0x80, 0x0F, 0x04, 0x21, 0x20, 
    0x02, 0x22, 0x20, 0x02, 0x42, 0x10, 0xF8, 0x00, 0x00, 0xFE, 0x23, 0x04, 0x42, 0x20, 0x04, 0x42, 
    0xC0, 0x03, 0x00, 0x80, 0x0F, 0x04, 0x21, 0x20, 0x02, 0x22, 0x60, 0x02, 0x4A, 0x90, 0xF8, 0x00, 
    0x00, 0xFE, 0x23, 0x02, 0x22, 0x20, 0x06, 0x9C, 0x01, 0x20, 0x00, 0xC0, 0x11, 0x22, 0x22, 0x22, 
    0x22, 0x22, 0x22, 0xC4, 0x01, 0x00, 0x02, 0x20, 0x00, 0x02, 0xE0, 0x3F, 0x02, 0x20, 0x00, 0x02, 
    0x00, 0x00, 0xFE, 0x00, 0x10, 0x00, 0x02, 0x20, 0x00, 0x02, 0x10, 0xFE, 0x00, 0x00, 0x06, 0x80, 
    0x03, 0xC0, 0x01, 0x20, 0xC0, 0x81, 0x03, 0x06, 0x00, 0x00, 0x06, 0x80, 0x07, 0x80, 0x03, 0x0C, 
    0x38, 0x60, 0x00, 0x38, 0x00, 0x0C, 0x80, 0x83, 0x07, 0x06, 0x00, 0x00, 0x02, 0xC2, 0x18, 0x70, 
    0x00, 0x07, 0x8C, 0x21, 0x20, 0x00, 0x20, 0x00, 0x0C, 0x00, 0x01, 0xE0, 0x03, 0x01, 0x0C, 0x20, 
    0x00, 0x00, 0x20, 0x30, 0x82, 0x22, 0x26, 0x12, 0xA2, 0x20, 0x06, 0x02, 0x00, 0x01, 0x18, 0x80, 
    0xFF, 0x0F, 0x00, 0x02, 0x40, 0x00, 0x08, 0x00, 0x01, 0x20, 0x00, 0x04, 0x80, 0x00, 0x10, 0x00, 
    0x02, 0x00, 0xFF, 0x1F, 0x80, 0x01, 0x08, 0x00, 0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x04, 0x80, 
    0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x02, 0x20, 0x00, 0x02, 0x00, 0x02, 0x40, 0x00, 
    0x00, 0x00, 0x18, 0x50, 0x02, 0x25, 0x50, 0x02, 0x3E, 0x00, 0xE0, 0x3F, 0x20, 0x02, 0x21, 0x10, 
    0x02, 0x21, 0xE0, 0x01, 0x00, 0xE0, 0x01, 0x21, 0x10, 0x02, 0x21, 0x10, 0x02, 0x00, 0xE0, 0x01, 
    0x21, 0x10, 0x02, 0x21, 0x10, 0xE1, 0x3F, 0x00, 0x00, 0x1E, 0x50, 0x02, 0x25, 0x50, 0x02, 0x25, 
    0x60, 0x01, 0x00, 0x10, 0xC0, 0x3F, 0x12, 0x20, 0x01, 0x00, 0x00, 0x1E, 0x10, 0x0A, 0xA1, 0x10, 
    0x0A, 0x91, 0xF0, 0x07, 0x00, 0xFE, 0x03, 0x02, 0x10, 0x00, 0x01, 0x10, 0x00, 0x3E, 0x00, 0x80, 
    0x3E, 0x00, 0x00, 0x80, 0x10, 0x48, 0x7F, 0x00, 0xE0, 0x3F, 0x40, 0x00, 0x0A, 0x10, 0x81, 0x20, 
    0x00, 0xE0, 0x3F, 0x00, 0x00, 0x3F, 0x10, 0x00, 0x01, 0x10, 0x00, 0x3E, 0x10, 0x00, 0x01, 0x10, 
    0x00, 0x3E, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x01, 0x10, 0x00, 0x01, 0xE0, 0x03, 0x00, 0xE0, 0x01, 
    0x21, 0x10, 0x02, 0x21, 0x10, 0x02, 0x1E, 0x00, 0x00, 0xFF, 0x20, 0x02, 0x21, 0x10, 0x02, 0x21, 
    0xE0, 0x01, 0x00, 0xE0, 0x01, 0x21, 0x10, 0x02, 0x21, 0x10, 0x01, 0xFF, 0x00, 0x00, 0x3F, 0x20, 
    0x00, 0x01, 0x00, 0x00, 0x23, 0x48, 0x82, 0x24, 0x88, 0x01, 0x00, 0x10, 0xC0, 0x1F, 0x10, 0x02, 
    0x21, 0x00, 0x00, 0x1F, 0x00, 0x02, 0x20, 0x00, 0x02, 0x10, 0xF0, 0x03, 0x00, 0x30, 0x00, 0x0C, 
    0x00, 0x03, 0x0C, 0x30, 0x00, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x03, 0x0C, 0x30, 0x00, 0x0C, 0x00, 
    0x03, 0x0C, 0x30, 0x00, 0x00, 0x10, 0x02, 0x12, 0xC0, 0x00, 0x12, 0x10, 0x02, 0x00, 0x30, 0x00, 
    0x8C, 0x00, 0x07, 0x0C, 0x30, 0x00, 0x00, 0x10, 0x03, 0x29, 0x50, 0x02, 0x23, 0x00, 0x00, 0x04, 
    0x40, 0xE0, 0x7B, 0x01, 0x18, 0x80, 0x00, 0xE0, 0x3F, 0x00, 0x10, 0x80, 0x01, 0xE8, 0x7B, 0x40, 
    0x00, 0x04, 0x00, 0x00, 0x03, 0x08, 0x80, 0x00, 0x10, 0x00, 0x02, 0x20, 0x80, 0x01, 0x00, 0x00, 
    0x70, 0xA0, 0x48, 0x85, 0x50, 0x08, 0x8A, 0x00, 0x09, 0x10, 0x00, 0x01, 0x13, 0x4A, 0x81, 0x14, 
    0xF0, 0x00, 0x0C, 0x20, 0x01, 0x10, 0x00, 0x05, 0x90, 0x00, 0x05, 0x10, 0xE0, 0x00, 0x00, 0x00, 
    0x08, 0x60, 0x00, 0x01, 0x10, 0x32, 0x81, 0x14, 0x4A, 0x01, 0x0F, 0x00, 0x00, 0x80, 0x00, 0x06, 
    0x80, 0x00, 0x06, 0x00, 0x08, 0x40, 0x00, 0x02, 0x40, 0x00, 0x08, 0x00, 0x10, 0x00, 0x01, 0x0C, 
    0x00, 0x01, 0x10, 0x00, 0x01, 0x0C, 0x00, 0x01, 0x10, 0xE0, 0x00, 0x00, 0x20, 0x00, 0x05, 0x88, 
    0x40, 0x10, 0x00, 0x01, 0x10, 0x30, 0x01, 0x15, 0x48, 0x81, 0x08, 0x00, 0x07, 0x8A, 0xA0, 0x08, 
    0xA6, 0x40, 0x0B, 0x84, 0x00, 0x08, 0x80, 0xC0, 0x07, 0x81, 0x04, 0x08, 0x7D, 0x00, 0x20, 0x00, 
    0x04, 0x00, 0x0C, 0x20, 0x01, 0x10, 0x00, 0x41, 0x13, 0x54, 0xA1, 0x14, 0x8A, 0x00, 0x00, 0x04, 
    0x20, 0x00, 0x00, 0x40, 0x00, 0x02, 0x40, 0x00, 0x02, 0x00, 0x00, 0x04, 0x20, 0x00, 0x04, 0x20, 
    0x00, 0x00, 0x01, 0x10, 0xE0, 0x07, 0x51, 0x90, 0x02, 0x16, 0x00, 0x01, 0x10, 0x00, 0x00, 0x04, 
    0x40, 0x00, 0x04, 0x40, 0x00, 0x04, 0x00, 0x00, 0x04, 0x40, 0x00, 0x04, 0x40, 0x00, 0x04, 0x00, 
    0x20, 0x00, 0x04, 0x00, 0xF0, 0x00, 0x0F, 0x70, 0xA0, 0x08, 0x8A, 0x60, 0x08, 0x84, 0x40, 0x08, 
    0x04, 0x00, 0x40, 0x10, 0x88, 0x00, 0x05, 0x20, 0x00, 0x70, 0x00, 0x08, 0x80, 0x00, 0x08, 0x88, 
    0x40, 0x09, 0x64, 0x80, 0x00, 0x10, 0x00, 0x01, 0x10, 0x20, 0x01, 0x51, 0x10, 0x09, 0x4A, 0xC0, 
    0x00, 0x08, 0x00, 0x07, 0x8A, 0xA0, 0x08, 0xA6, 0x40, 0x0B, 0x84, 0x40, 0x00, 0x00, 0x06, 0x80, 
    0x11, 0x60, 0x01, 0x18, 0x80, 0xE1, 0x0F, 0x00, 0x01, 0x10, 0x00, 0x07, 0x80, 0x00, 0x08, 0x80, 
    0x80, 0x08, 0x94, 0x40, 0x06, 0x08, 0x00, 0x01, 0x00, 0x80, 0x01, 0x14, 0x10, 0x81, 0x11, 0xC8, 
    0xF0, 0x00, 0x1F, 0xB0, 0xFF, 0xFB, 0xBF, 0xFF, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 
    0x00, 0xC0, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x06, 0x80, 0x11, 0x60, 0x01, 0x18, 0x80, 0xE1, 0x0F, 
    0x34, 0xA2, 0x45, 0x92, 0x24, 0x52, 0xC4, 0x02, 0xF0, 0x00, 0x0F, 0x00, 0xC0, 0x0F, 0xFC, 0x00, 
    0x00, 0xFF, 0xF0, 0x0F, 0x00, 0xF0, 0x80, 0x10, 0x64, 0x42, 0x29, 0x94, 0x42, 0x20, 0x08, 0x01, 
    0x0F, 0xF0, 0x0F, 0xFF, 0x00, 0xC0, 0xFF, 0xFC, 0x0F, 0x00, 0x00, 0x00, 0x02, 0x50, 0x80, 0x0A, 
    0x50, 0x80, 0x08, 0xF8, 0x81, 0x10, 0xFF, 0xFF, 0xFF, 0x03, 0xBC, 0xDF, 0xFB, 0xBD, 0xDF, 0xFB, 
    0x3D, 0xC0, 0xFB, 0xBD, 0xDF, 0xFB, 0xBD, 0xDF, 0x03, 0xBC, 0xDF, 0xFB, 0xBD, 0xDF, 0xFB, 0x3D, 
    0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0x08, 0x41, 0x2F, 0x54, 0x42, 0x25, 0xA4, 0x82, 0x10, 
    0xF0, 0xE0, 0x7F, 0xFB, 0x7E, 0xF7, 0xAF, 0xFF, 0xFD, 0xDF, 0xFF, 0xFD, 0xDF, 0xFF, 0xFD, 0xDF, 
    0xFF, 0xFD, 0xAF, 0x7F, 0xF7, 0xFB, 0xEE, 0x7F, 0x00, 0x00, 0x00, 0x0E, 0xA0, 0x00, 0x0E, 0x00, 
    0x00, 0x00, 0x00, 0x22, 0x20, 0x82, 0x2F, 0x20, 0x02, 0x22, 0x00, 0x00, 0x00, 0x04, 0x60, 0x11, 
    0x62, 0x01, 0x18, 0x80, 0xE1, 0x0F, 0x00, 0x40, 0x00, 0x16, 0x21, 0x16, 0x80, 0x01, 0x18, 0xFE, 
    0x00, 0x10, 0x00, 0x01, 0x74, 0x60, 0x08, 0x82, 0x00, 0x08, 0x88, 0x40, 0x09, 0x64, 0x80, 0x00, 
    0x10, 0x88, 0xC0, 0x1D, 0xFE, 0x33, 0x62, 0xFF, 0xE7, 0x3F, 0xD8, 0xC0, 0x18, 0x06, 0x03, 0x00, 
    0xC0, 0x00, 0x0C, 0x00, 0x00, 0x01, 0x18, 0xC0, 0x3F, 0xFE, 0xC3, 0x3F, 0x18, 0x00, 0x09, 0x80, 
    0xC1, 0x3F, 0xFC, 0xC7, 0x3F, 0x80, 0x01, 0x08, 0x00, 0x00, 0x00, 0x60, 0x01, 0x15, 0x00, 0x80, 
    0x08, 0x50, 0x80, 0x0A, 0x50, 0x00, 0x02, 0x00, 0xC0, 0x01, 0x22, 0x20, 0x02, 0xC2, 0x22, 0x00, 
    0x04, 0x00, 0x90, 0x00, 0x01, 0x8C, 0x00, 0x00, 0x10, 0xC0, 0x01, 0x0A, 0x00, 0x40, 0x00, 0xF2, 
    0x41, 0x00, 0x02, 0x00, 0x00, 0x04, 0x60, 0x1F, 0x02, 0x00, 0x00, 0xC8, 0xC8, 0x92, 0x24, 0x09, 
    0x7C, 0x00, 0x00, 0x80, 0xFE, 0x0D, 0x40, 0xE4, 0x60, 0x10, 0x02, 0x01, 0x10, 0x18, 0x41, 0x12, 
    0x24, 0x81, 0x0C, 0x00, 0xE0, 0x1F, 0xC0, 0x00, 0x12, 0x00, 0x01, 0x10, 0x00, 0x05, 0x10, 0x00, 
    0x01, 0x0E, 0x00, 0x20, 0x0C, 0x28, 0x21, 0x11, 0x20, 0x01, 0x0C, 0xC0, 0x00, 0x12, 0x00, 0x81, 
    0x10, 0x00, 0x81, 0x10, 0x00, 0x01, 0x0E, 0xC0, 0x00, 0x12, 0x00, 0x81, 0x10, 0x02, 0x81, 0x10, 
    0x00, 0x01, 0x0E, 0x00, 0x07, 0x8A, 0xA0, 0x08, 0xA6, 0x40, 0x08, 0x84, 0x00, 0x07, 0x8A, 0xA0, 
    0x08, 0x86, 0x40, 0x08, 0x84, 0x00, 0x07, 0x8A, 0xA0, 0x08, 0x86, 0x48, 0x08, 0x84, 0x00, 0x00, 
    0x10, 0x10, 0x01, 0x12, 0xC0, 0x00, 0x00, 0x04, 0x01, 0x11, 0x20, 0x01, 0x0C, 0x00, 0x08, 0x80, 
    0xC0, 0x07, 0x80, 0x00, 0x88, 0x7C, 0x80, 0x03, 0x40, 0x00, 0x04, 0x40, 0x00, 0x04, 0x3C, 0x00, 
    0x01, 0x10, 0x00, 0x01, 0x0C, 0x00, 0x01, 0x10, 0xE0, 0x00, 0x38, 0x00, 0x04, 0x40, 0x00, 0x04, 
    0x40, 0xC0, 0x83, 0x10, 0x02, 0x81, 0x10, 0xC0, 0x00, 0x10, 0x00, 0x01, 0x0E, 0x80, 0x03, 0x40, 
    0x00, 0x04, 0x40, 0x00, 0x04, 0x3C, 0x00, 0x01, 0x18, 0x60, 0x01, 0x11, 0x10, 0x01, 0x0E, 0x80, 
    0x03, 0x40, 0x00, 0x04, 0x40, 0x00, 0x04, 0x3C, 0x00, 0x01, 0x18, 0x60, 0x41, 0x11, 0x10, 0x01, 
    0x0E, 0x00, 0x40, 0x10, 0x88, 0x00, 0x05, 0x20, 0x00, 0x05, 0x88, 0x40, 0x10, 0x00, 0xE1, 0x1F, 
    0x60, 0x01, 0x11, 0x10, 0x01, 0x0E, 0x00, 0xE1, 0x1F, 0x60, 0x41, 0x11, 0x10, 0x01, 0x0E, 0x60, 
    0x07, 0x89, 0x90, 0x08, 0x85, 0x40, 0x08, 0x76, 0x90, 0x48, 0x89, 0x50, 0x08, 0x84, 0x00, 0x01, 
    0x10, 0x00, 0x01, 0x0C, 0x20, 0x01, 0x10, 0x00, 0x01, 0x13, 0x4A, 0x81, 0x14, 0xF0, 0x00, 0x38, 
    0x00, 0x04, 0x40, 0x00, 0x44, 0x46, 0x90, 0x44, 0x29, 0xE0, 0x01, 0x0C, 0x20, 0x01, 0x10, 0x00, 
    0x01, 0x13, 0x50, 0x81, 0x14, 0x88, 0x00, 0x38, 0x00, 0x04, 0x40, 0x00, 0x04, 0x40, 0xFE, 0x03, 
    0x40, 0x00, 0x03, 0x0E, 0x10, 0x01, 0x11, 0xE0, 0x00, 0x38, 0x00, 0x04, 0x42, 0x00, 0x04, 0x40, 
    0x80, 0x03, 0x0C, 0x28, 0x01, 0x11, 0x20, 0x01, 0x0C, 0x00, 0x00, 0x8C, 0x20, 0x09, 0x92, 0xC0, 
    0x07, 0x03, 0x48, 0x80, 0x04, 0x48, 0x00, 0x0F, 0x00, 0x01, 0x10, 0x30, 0xA0, 0x04, 0x4B, 0x90, 
    0x04, 0xF0, 0x00, 0x10, 0x00, 0x01, 0x03, 0x4A, 0x80, 0x04, 0x4A, 0x00, 0x0F, 0x00, 0x01, 0x10, 
    0xE0, 0x00, 0x10, 0x00, 0x01, 0x50, 0x18, 0x41, 0x52, 0x24, 0x81, 0x0C, 0xE0, 0x00, 0x10, 0x00, 
    0x01, 0x10, 0x18, 0x41, 0x12, 0x24, 0x81, 0x0C, 0x00, 0x01, 0x14, 0xA0, 0x00, 0x0A, 0x40, 0x01, 
    0x10, 0x00, 0x07, 0x8A, 0x50, 0x08, 0x85, 0xA0, 0x08, 0x90, 0x00, 0x01, 0x10, 0xE4, 0x00, 0x10, 
    0x00, 0xE1, 0x0F, 0x00, 0x01, 0x10, 0x60, 0x21, 0x19, 0x10, 0x01, 0x09, 0x80, 0x00, 0x10, 0x40, 
    0x41, 0x0A, 0xA0, 0x00, 0x14, 0x00, 0x01, 0x10, 0x00, 0x01, 0x0E, 0x10, 0x01, 0x11, 0xE0, 0x00, 
    0x10, 0x00, 0x41, 0x13, 0x54, 0xA1, 0x14, 0x8A, 0x00, 0x50, 0x00, 0x09, 0x4C, 0x00, 0x01, 0x10, 
    0xE0, 0x41, 0x11, 0x14, 0x81, 0x1E, 0x10, 0x01, 0x0E, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00
};

#endif
