#include <Adafruit_SSD1306.h>
#include "VoiceRecognitionV3.h"
#include "Keyboard.h"

// Microphone bitmap
int micBitmapSize = 32;
const unsigned char micBitmap [] PROGMEM = {
	0x00, 0x03, 0xe0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x18, 0x0c, 0x00, 
	0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 
	0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 
	0x00, 0x30, 0x06, 0x00, 0x03, 0x30, 0x06, 0x60, 0x03, 0x30, 0x06, 0x60, 0x03, 0x30, 0x06, 0x60, 
	0x03, 0x30, 0x06, 0x60, 0x03, 0x30, 0x06, 0x60, 0x01, 0x98, 0x0c, 0x60, 0x01, 0x9c, 0x1c, 0xc0, 
	0x01, 0xcf, 0xf8, 0xc0, 0x00, 0xc3, 0xf1, 0x80, 0x00, 0xe0, 0x03, 0x80, 0x00, 0x38, 0x0f, 0x00, 
	0x00, 0x1f, 0xfc, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x80
};

// Jump icon bitmap
const unsigned char jumpBitmap [] PROGMEM  = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0x40, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x08, 0x80, 0x00, 0x00, 0x00, 0x02, 0x10, 0x08, 0x80, 
	0x00, 0x00, 0x00, 0x04, 0x08, 0x11, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x11, 0x00, 0x00, 0x00, 
	0x00, 0x08, 0x04, 0x22, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x22, 0x00, 0x00, 0x00, 0x00, 0x08, 
	0x04, 0x44, 0x80, 0x00, 0x00, 0x00, 0x08, 0x04, 0x88, 0x80, 0x00, 0x00, 0x00, 0x04, 0x09, 0x08, 
	0x80, 0x00, 0x00, 0x00, 0x02, 0x11, 0x10, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe2, 0x10, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x0c, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x40, 0x80, 0x00, 0x00, 0x00, 
	0x07, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0xe0, 0x01, 
	0x08, 0x80, 0x00, 0x00, 0x01, 0x00, 0x01, 0x08, 0x80, 0x00, 0x00, 0x02, 0x00, 0x01, 0x08, 0x80, 
	0x00, 0x00, 0x04, 0x1c, 0x01, 0x08, 0x80, 0x00, 0x00, 0x04, 0x22, 0x01, 0x08, 0x80, 0x00, 0x00, 
	0x04, 0x42, 0x01, 0x00, 0x80, 0x00, 0x00, 0x04, 0x42, 0x01, 0x00, 0x80, 0x00, 0x00, 0x02, 0x22, 
	0x01, 0x00, 0x80, 0x00, 0x00, 0x02, 0x22, 0x01, 0x00, 0x80, 0x00, 0x00, 0x01, 0x12, 0x01, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x92, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x4a, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x32, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 
	0x02, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x02, 0x26, 0x02, 0x00, 0x00, 0x00, 0x04, 0x82, 0x21, 
	0x01, 0x00, 0x00, 0x00, 0x04, 0x84, 0x20, 0xc1, 0x00, 0x00, 0x00, 0x04, 0x84, 0x20, 0x21, 0x00, 
	0x00, 0x00, 0x04, 0x84, 0x20, 0x41, 0x00, 0x00, 0x00, 0x04, 0x84, 0x40, 0x81, 0x00, 0x00, 0x00, 
	0x04, 0x84, 0x41, 0x06, 0x00, 0x00, 0x00, 0x04, 0x84, 0x42, 0x08, 0x00, 0x00, 0x00, 0x04, 0x88, 
	0x42, 0x10, 0x00, 0x00, 0x00, 0x04, 0x88, 0x84, 0x20, 0x00, 0x00, 0x00, 0x04, 0x08, 0x84, 0x40, 
	0x00, 0x00, 0x00, 0x04, 0x08, 0x84, 0x80, 0x00, 0x00, 0x00, 0x04, 0x11, 0x03, 0x04, 0x00, 0x00, 
	0x00, 0x04, 0x11, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x11, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
	0x22, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Shoot icon bitmap
const unsigned char shootBitmap [] PROGMEM  = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0b, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0x80, 0x00, 0x00, 0x00, 0x40, 0x11, 0x81, 
	0x80, 0x00, 0x00, 0x00, 0x70, 0x21, 0x83, 0x00, 0x00, 0x00, 0x00, 0x50, 0x21, 0x87, 0x00, 0x00, 
	0x00, 0x00, 0x48, 0x61, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x44, 0x41, 0xb3, 0x00, 0x00, 0x08, 0x00, 
	0x42, 0x41, 0xc6, 0x00, 0x00, 0x0e, 0x00, 0x43, 0x81, 0x86, 0x00, 0x00, 0x07, 0xc0, 0x41, 0x81, 
	0x0e, 0x00, 0x00, 0x01, 0x38, 0x40, 0x00, 0x0e, 0x00, 0x30, 0x00, 0x87, 0x40, 0x00, 0x0c, 0x1f, 
	0xe0, 0x00, 0x40, 0xc0, 0x00, 0x1f, 0xf1, 0x80, 0x00, 0x60, 0x00, 0x00, 0x1e, 0x03, 0x80, 0x00, 
	0x30, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0xf0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x1f, 0x80, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x07, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0x7c, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x70, 
	0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x3c, 0x00, 0x1f, 0xff, 0xc1, 0x80, 0x0c, 0x1e, 0x00, 0x3f, 
	0xff, 0xe1, 0xc2, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x23, 0xe7, 0x8f, 0xc7, 0x00, 0x00, 0x00, 0x27, 
	0xf7, 0xc7, 0xf3, 0x80, 0x00, 0x00, 0x27, 0x3e, 0x76, 0x3d, 0xc0, 0x00, 0x00, 0x2f, 0x1c, 0x3e, 
	0x1f, 0xe0, 0x00, 0x00, 0x2e, 0x0c, 0x1e, 0x03, 0xf0, 0x00, 0x00, 0x3c, 0x00, 0x06, 0x00, 0x78, 
	0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 
	0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Run icon bitmap
const unsigned char runBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x08, 0x04, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x10, 0x02, 0x00, 0x3f, 0xfe, 0x31, 0x80, 0x10, 0x02, 
	0x00, 0x00, 0x00, 0x40, 0x40, 0x10, 0x02, 0x00, 0x00, 0x00, 0x80, 0x20, 0x10, 0x02, 0x00, 0x00, 
	0x03, 0x00, 0x10, 0x10, 0x02, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x10, 0x02, 0x00, 0x00, 0x08, 0x0c, 
	0x02, 0x08, 0x04, 0x00, 0x0f, 0x10, 0x12, 0x01, 0x84, 0x08, 0x00, 0x00, 0x20, 0x61, 0x00, 0x43, 
	0xf0, 0x00, 0x00, 0x40, 0x80, 0x80, 0x20, 0x00, 0x3c, 0x00, 0x41, 0x00, 0x40, 0x10, 0x00, 0x42, 
	0x00, 0x42, 0x00, 0x40, 0x08, 0x01, 0x82, 0x00, 0x3c, 0x00, 0x80, 0x04, 0x02, 0x02, 0x00, 0x00, 
	0x03, 0x00, 0x02, 0x04, 0x04, 0x00, 0x00, 0x04, 0x00, 0x01, 0x08, 0x08, 0x00, 0x00, 0x08, 0x00, 
	0x00, 0xf0, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x3f, 0xfc, 0x20, 0x01, 0xe0, 0x00, 
	0x40, 0x00, 0x00, 0x40, 0x02, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x04, 0x0c, 0x01, 0x00, 0x00, 
	0x00, 0x80, 0x08, 0x02, 0x06, 0x00, 0x00, 0x01, 0x00, 0x10, 0x01, 0x88, 0x00, 0x00, 0x01, 0x00, 
	0x20, 0x00, 0x70, 0x00, 0x03, 0xf9, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x02, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x62, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x04, 0x81, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x80, 0x80, 0x00, 0x00, 0x00, 0x02, 
	0x04, 0x80, 0x40, 0x00, 0x00, 0x00, 0x04, 0x08, 0x80, 0x20, 0x00, 0x00, 0x00, 0x04, 0x08, 0x40, 
	0x20, 0x00, 0x00, 0x00, 0x04, 0x08, 0x20, 0x20, 0x00, 0x00, 0x00, 0x08, 0x08, 0x20, 0x20, 0x00, 
	0x00, 0x00, 0x30, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x40, 0x10, 0x40, 0x40, 0x00, 0x00, 0x01, 
	0x80, 0x20, 0x80, 0x80, 0x00, 0x00, 0x06, 0x00, 0x60, 0x81, 0x00, 0x00, 0x00, 0x08, 0x00, 0xc1, 
	0x02, 0x00, 0x00, 0x00, 0x10, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x20, 0x06, 0x02, 0x04, 0x00, 
	0x00, 0x00, 0x40, 0x18, 0x04, 0x08, 0x00, 0x00, 0x00, 0x40, 0x20, 0x04, 0x10, 0x00, 0x00, 0x00, 
	0x40, 0xc0, 0x04, 0x10, 0x00, 0x00, 0x00, 0x43, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x3c, 0x00, 
	0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Left icon bitmap
const unsigned char leftBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x19, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x18, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x02, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x70, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x1c, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x0e, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x39, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Right icon bitmap
const unsigned char rightBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x70, 0x00, 
	0x7f, 0xff, 0xff, 0xff, 0x80, 0x38, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x0e, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x40, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x40, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x40, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x18, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Up icon bitmap
const unsigned char upBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x0e, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x38, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xe0, 
	0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x60, 0x00, 
	0x00, 0x1c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x70, 
	0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0xc0, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0xe0, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0xe0, 0x00, 
	0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Down icon bitmap
const unsigned char downBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xe0, 
	0x07, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x60, 0x00, 0x00, 
	0x00, 0x07, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0xc0, 
	0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0e, 
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x38, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Game button structure
struct GameButton {
  int pin;
  int key;
  bool isPressed;
};

// Button input mappings
int button1Key = 105;
int button2Key = 101;
int button3Key = 97;
int button4Key = 32;
int button5Key = 176;
int button6Key = 122;

// Game buttons array
const int numButtons = 6;
GameButton gameButtons[numButtons] = {
  {4, button1Key, false}, // Button 1
  {5, button2Key, false}, // Button 2
  {6, button3Key, false}, // Button 3
  {7, button4Key, false}, // Button 4
  {8, button5Key, false}, // Button 5
  {9, button6Key, false}  // Button 6
};

// Joystick pins
int xPin = A0;
int yPin = A1;

// Joystick input mapping
int upKey = KEY_UP_ARROW; 
int downKey = KEY_DOWN_ARROW;
int leftKey = KEY_LEFT_ARROW;
int rightKey = KEY_RIGHT_ARROW;

// Joystick states
bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;

// Adafruit OLED object
int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 64;
int SCREEN_ADDRESS = 0x3D; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// Listening animation settings
int centerX = SCREEN_WIDTH / 2;
int centerY = SCREEN_HEIGHT / 2;
int maxRadius = 31; 
int minRadius = 23; 
int animationFrames = 12; 
int animationFrame = 0; 

// Voice command icon settings
int iconSize = 56;
int iconIndex = -1;
bool iconDisplayed = false;
unsigned long iconStartMillis;
const unsigned long iconDuration = 1500; 

// Voice recognition module object
VR myVR(10,11);   

// Voice recognition buffer
uint8_t buf[64];

// Voice command structure
struct VoiceCommand {
  String name;
  int key;
  unsigned long startMillis;
  unsigned long duration;
  bool isPressed;
  const unsigned char* bitmap;
};

// Voice command input mappings
int jumpCommandKey = 32;
int runCommandKey = 101;
int shootCommandKey = 97;
int upCommandKey = KEY_UP_ARROW;
int downCommandKey = KEY_DOWN_ARROW;
int leftCommandKey = KEY_LEFT_ARROW;
int rightCommandKey = KEY_RIGHT_ARROW;

// Game voice commands
const int numCommands = 7;
VoiceCommand voiceCommands[numCommands] = {
  {"Jump", jumpCommandKey, 0, 500, false, jumpBitmap}, // Jump
  {"Run", runCommandKey, 0, 500, false, runBitmap}, // Run
  {"Shoot", shootCommandKey, 0, 250, false, shootBitmap}, // Shoot
  {"Up", upCommandKey, 0, 1000, false, upBitmap}, // Up
  {"Down", downCommandKey, 0, 1000, false, downBitmap}, // Down
  {"Left", leftCommandKey, 0, 1000, false, leftBitmap}, // Left
  {"Right", rightCommandKey, 0, 1000, false, rightBitmap} // Right
};

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize oled display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();

  // Initialize button pins
  for (int i = 0; i < numButtons; i++) {
    pinMode(gameButtons[i].pin, INPUT_PULLUP);
  }

  // Initialize voice recognition
  myVR.begin(9600);
    
  // Clear voice recognizer
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Voice Recognition Module not found.");
    while(1);
  }
  
  // Load trained voice records
  for (int i = 0; i < numCommands; i++) {
    VoiceCommand command = voiceCommands[i];
    myVR.load((uint8_t)i);
    Serial.println(String(command.name) + " loaded");
  }

  // Initialize keyboard output
  Keyboard.begin();
}

void loop() {
  // Process button inputs
  processButtons();

  // Process joystick inputs
  processJoystick();

  // Process voice recognizer
  processVoice();

  // Process display
  processDisplay();
}

void processDisplay() {
  // Display command icon if active
  if (iconIndex > -1) {
    if (iconDisplayed == false) {

      // Display the selected icon
      display.clearDisplay();
      display.drawBitmap(
        centerX - iconSize/2, 
        centerY - iconSize/2, 
        voiceCommands[iconIndex].bitmap,
        iconSize, 
        iconSize, 
        WHITE
      );
      iconDisplayed = true;
      iconStartMillis = millis();
    } else {
      unsigned long currentMillis = millis();
      if (currentMillis - iconStartMillis >= iconDuration) {
        iconIndex = -1;
        iconDisplayed = false;
      }
    }
  } 
  // Display listening animation
  else {
    // Calculate circle radius
    float animationProgress = float(animationFrame) / float(animationFrames - 1);
    float animationPhase = animationProgress * 2.0 * PI; 
    float pulsatingFactor = (cos(animationPhase) + 1.0) / 2.0;
    int currentRadius = minRadius + int((maxRadius - minRadius) * pulsatingFactor);

    // Display mic and circle
    display.clearDisplay();
    display.drawBitmap(
      centerX - micBitmapSize/2, 
      centerY - micBitmapSize/2, 
      micBitmap, 
      micBitmapSize, 
      micBitmapSize, 
      WHITE
    );
    display.drawCircle(centerX, centerY, currentRadius, SSD1306_WHITE);

    // Update frame count
    animationFrame = (animationFrame + 1) % animationFrames;
  }

  // Update display
  display.display();
}

void processVoice() {
  // Perform voice recognition
  int ret = myVR.recognize(buf, 50);

  // Process voice record match
  if (ret > 0) {
    int index = buf[1];
    if (voiceCommands[index].isPressed == false) {
      Serial.println(String(voiceCommands[index].name) + " command recognized");
      Keyboard.press(voiceCommands[index].key);
      voiceCommands[index].isPressed = true;
      voiceCommands[index].startMillis = millis();
      iconIndex = index;
    }
  } 
  // Process no voice record match
  else {
    unsigned long currentMillis = millis();
    for (int i = 0; i < numCommands; i++) {
      if (voiceCommands[i].isPressed == true && currentMillis - voiceCommands[i].startMillis >= voiceCommands[i].duration) {      
        Keyboard.release(voiceCommands[i].key);
        voiceCommands[i].isPressed = false;
      }
    }
  }
}

void processButtons() {
  // Loop through all buttons
  for (int i = 0; i < numButtons; i++) {
    
    // Read button digital value - LOW == Pressed 
    int buttonVal = digitalRead(gameButtons[i].pin);

    // Press key on button press
    if (buttonVal == LOW && gameButtons[i].isPressed == false) {
      Keyboard.press(gameButtons[i].key);
      gameButtons[i].isPressed = true;
      Serial.println("Button pressed");
    }

    // Release key on button release
    if (buttonVal == HIGH && gameButtons[i].isPressed == true) {
      Keyboard.release(gameButtons[i].key);
      gameButtons[i].isPressed = false;
      Serial.println("Button released");
    }
  }
}

void processJoystick() {
  // Read X and Y analog values
  int yValue = analogRead(yPin);
  int xValue = analogRead(xPin);

  // Map values between 0-100
  int xMapped = map(xValue, 0, 1023, 0, 100);
  int yMapped = map(yValue, 0, 1023, 0, 100);

  // Apply X keyboard inputs
  if (xMapped < 30) {
    if (leftPressed == false) {
      leftPressed = true;
      Keyboard.press(leftKey);
      Serial.println("Left pressed");
    }
  } else if (xMapped > 60) {
    if (rightPressed == false) {
      rightPressed = true;
      Keyboard.press(rightKey);
      Serial.println("Right pressed");
    }
  } else {
    if (leftPressed == true) {
      leftPressed = false;
      Keyboard.release(leftKey);
      Serial.println("Left released");
    }
    if (rightPressed == true) {
      rightPressed = false;
      Keyboard.release(rightKey);
      Serial.println("Right released");
    }
  }

  // Apply Y keyboard inputs
  if (yMapped < 30) {
    if (downPressed == false) {
      downPressed = true;
      Keyboard.press(downKey);
      Serial.println("Down released");
    }
  } else if (yMapped > 60) {
    if (upPressed == false) {
      upPressed = true;
      Keyboard.press(upKey);
      Serial.println("Up pressed");
    }
  } else {
    if (downPressed == true) {
      downPressed = false;
      Keyboard.release(downKey);
      Serial.println("Down released");
    }
    if (upPressed == true) {
      upPressed = false;
      Keyboard.release(upKey);
      Serial.println("Up released");
    }
  }
}