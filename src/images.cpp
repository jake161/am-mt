#define test_width 128
#define test_height 32
#define JAB_width 126
#define JAB_height 64

static unsigned char test_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
   0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
   0xc0, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x00, 0x00, 0xe0, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x40, 0x00, 0xf0, 0x01, 0x1c, 0x00, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x0e, 0x1c,
   0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0x00, 0x04, 0x18, 0x60, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x10, 0x80, 0x01, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0x0e, 0x00,
   0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0x00, 0xe1, 0x01, 0x00, 0x0c, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x0c, 0x80, 0xff,
   0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x70, 0x60, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x40, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static unsigned char Mrry_Christmas_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x07, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5f, 0x00, 0xfe, 0xff, 0xff, 0xff,
   0x7f, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x87, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x7f, 0xf0, 0xff, 0xff,
   0x7f, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xbf, 0xef, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xdf, 0xdf, 0x7f, 0xfe, 0x47, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xef, 0xdf, 0x9f, 0xff,
   0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xef, 0xdf, 0xe3, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xf7, 0x5f, 0xf8, 0xff, 0xff, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xf7, 0x9f, 0xff, 0xff,
   0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xfb, 0x2f, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xfb, 0xf7, 0xf9, 0xff, 0xff, 0xfd, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x1b, 0xf8, 0xe7, 0xff,
   0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xfb, 0xff, 0x9f, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xfb, 0xff, 0x7f, 0xfe, 0xff, 0xfd, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xfb, 0xff, 0xff, 0xf9,
   0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xf7, 0xff, 0xff, 0xf7, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xdf, 0xff, 0xf7, 0xff, 0xfd, 0xef, 0xff, 0xfd, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xef, 0xff, 0xfc, 0xe7,
   0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
   0xef, 0x7f, 0xff, 0xfb, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x9f, 0x9f, 0xff, 0xfc, 0xff, 0xfd, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0x3f, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

static unsigned char JAB_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x0c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0x08,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfe, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x08,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xf8, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xf8,
   0xff, 0x03, 0x00, 0xc0, 0x80, 0x03, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x40, 0x00, 0x80, 0xff, 0x1f, 0x00, 0xc0, 0x80, 0x07, 0xfe, 0x0f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xfc, 0xff, 0x00, 0xc0,
   0x80, 0x0f, 0xbf, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
   0xe0, 0xff, 0x00, 0xc0, 0x9f, 0x1f, 0x0f, 0xf8, 0x3f, 0x00, 0x00, 0x00,
   0x00, 0x30, 0x00, 0x00, 0x00, 0xf8, 0x03, 0xc0, 0xff, 0xff, 0x0f, 0x80,
   0xff, 0x03, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x80, 0x03, 0xc0,
   0xc3, 0xff, 0x0f, 0x00, 0xd0, 0xff, 0x1e, 0x00, 0x00, 0x38, 0x00, 0x00,
   0x00, 0x00, 0x02, 0xe0, 0x83, 0xff, 0x0f, 0x00, 0x00, 0xfc, 0xff, 0x07,
   0x00, 0xfc, 0xe0, 0x01, 0x00, 0x00, 0x02, 0xe0, 0x81, 0xff, 0x1f, 0x00,
   0x00, 0xc0, 0xff, 0x3f, 0x00, 0xfe, 0xff, 0x3f, 0x00, 0x00, 0x02, 0xe0,
   0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0xf8, 0x3f, 0x00, 0xfe, 0xff, 0xff,
   0x03, 0x00, 0x02, 0xf0, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0xe0, 0x0f,
   0x00, 0xfc, 0xff, 0xff, 0x1f, 0x00, 0x02, 0x70, 0x00, 0xf0, 0x1f, 0x80,
   0x7f, 0x00, 0x80, 0x07, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x00, 0x02, 0x38,
   0x00, 0xf0, 0x1f, 0xc0, 0x3e, 0x00, 0x80, 0x07, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0x01, 0x02, 0x1c, 0x00, 0xe0, 0x1f, 0xc0, 0x00, 0x00, 0xe0, 0x07,
   0x00, 0x06, 0x80, 0xff, 0xff, 0x01, 0x12, 0x0e, 0x00, 0xc0, 0x1f, 0x00,
   0x00, 0x00, 0xf0, 0x0f, 0xf0, 0x03, 0x00, 0xff, 0xff, 0x01, 0x17, 0x06,
   0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0xfc, 0x0f, 0xfc, 0x01, 0x00, 0xfc,
   0xff, 0x01, 0x1f, 0x03, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xff, 0x0f,
   0x0c, 0x00, 0x00, 0xc0, 0xe1, 0x00, 0x0f, 0x03, 0x60, 0x00, 0x1c, 0x00,
   0x00, 0xc0, 0xff, 0x0f, 0x04, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x8f, 0x01,
   0xf0, 0x00, 0x18, 0x00, 0x00, 0xf0, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x00, 0xc7, 0x00, 0xf0, 0x00, 0x10, 0x00, 0x00, 0xf0, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xe7, 0x00, 0xf0, 0x01, 0x10, 0x00,
   0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x67, 0x00,
   0xf0, 0x03, 0x10, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x60, 0x00, 0x3f, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x80, 0x7f, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0x7f, 0x80, 0x3f, 0x00, 0xfc, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0xef, 0x00, 0x00, 0x78, 0x80, 0x1f, 0x00,
   0xfe, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0xe0, 0x07, 0x00, 0x00,
   0x20, 0x80, 0x0f, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
   0x70, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x80, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x30, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
   0x30, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x02, 0xe0,
   0x01, 0x00, 0x80, 0x01, 0x30, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
   0x00, 0x00, 0x02, 0xe0, 0x01, 0x00, 0x00, 0x01, 0x30, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x01, 0x00, 0xf0, 0x0f, 0x03, 0x60, 0x00, 0x00, 0x00, 0x02,
   0x30, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x3f, 0xff, 0x01, 0x20,
   0x00, 0x00, 0x00, 0x06, 0x38, 0x00, 0x80, 0x03, 0x00, 0x80, 0x01, 0xe0,
   0x03, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x38, 0x00, 0x80, 0xff,
   0x00, 0x80, 0x01, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
   0x3c, 0x00, 0xc0, 0xff, 0x07, 0x80, 0x01, 0xfe, 0xff, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x20, 0x7c, 0x00, 0xc0, 0xff, 0x1f, 0x80, 0x01, 0xff,
   0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0xfc, 0x07, 0xc0, 0xff,
   0xff, 0x80, 0xc1, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xfc, 0x1f, 0xe0, 0xff, 0xff, 0xc1, 0xf1, 0xff, 0xff, 0xff, 0x00, 0xe0,
   0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xe0, 0xff, 0xff, 0xc7, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0xf8, 0xff, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff,
   0xff, 0xef, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xfc, 0xff, 0xff, 0x03, 0x00,
   0xdc, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xfe,
   0xff, 0xff, 0xff, 0x07, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff,
   0xff, 0x3f, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x04, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xe0, 0xff, 0xff, 0x07, 0xe0, 0x3f,
   0x04, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf0, 0xff,
   0xff, 0x00, 0x80, 0x3f, 0x04, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x1f, 0xfc, 0xff, 0x1f, 0x00, 0x00, 0x3f, 0x04, 0xc0, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x07, 0x00, 0x00, 0x3e,
   0x04, 0x80, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff,
   0x00, 0x00, 0x00, 0x3c, 0x04, 0x80, 0x0f, 0x00, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xdf, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x38, 0x04, 0x00, 0x0f, 0x00,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x30,
   0x04, 0x00, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x20, 0x04, 0x00, 0x07, 0x00, 0x00, 0xfc, 0xff, 0x0f,
   0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x06, 0x00,
   0x00, 0xf0, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x04, 0x00, 0x06, 0x00, 0x00, 0xf0, 0xff, 0x00, 0xe0, 0xff, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00,
   0xe0, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };