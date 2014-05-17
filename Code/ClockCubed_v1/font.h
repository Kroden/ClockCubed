char font[63][4] =    {          //3x7 font
  0x7C, 0x82, 0x7C, 0x00,   //0
  0x42, 0xFE, 0x02, 0x00,   //1
  0x8E, 0x92, 0x62, 0x00,   //2
  0x44, 0x92, 0x7C, 0x00,   //3
  0xF0, 0x10, 0xFE, 0x00,   //4
  0xE2, 0x92, 0x8C, 0x00,   //5
  0x7C, 0x92, 0x4C, 0x00,   //6
  0x80, 0x9E, 0xE0, 0x00,   //7
  0x6C, 0x92, 0x6C, 0x00,   //8
  0x60, 0x90, 0xFE, 0x00,   //9
  0x7E, 0x90, 0x7E, 0x00,   //A
  0xFE, 0x92, 0x6C, 0x00,   //B
  0x7C, 0x82, 0x82, 0x00,   //C
  0xFE, 0x82, 0x7C, 0x00,   //D
  0xFE, 0x92, 0x82, 0x00,   //E
  0xFE, 0x90, 0x80, 0x00,   //F
  0x7C, 0x82, 0x8E, 0x00,   //G
  0xFE, 0x10, 0xFE, 0x00,   //H
  0x82, 0xFE, 0x82, 0x00,   //I
  0x82, 0xFC, 0x80, 0x00,   //J
  0xFE, 0x10, 0xEE, 0x00,   //K
  0xFE, 0x02, 0x02, 0x00,   //L
  0xFE, 0x60, 0xFE, 0x00,   //M
  0xFE, 0x30, 0xFE, 0x00,   //N
  0x7C, 0x82, 0x7C, 0x00,   //O
  0xFE, 0x90, 0x60, 0x00,   //P
  0xFC, 0x84, 0xFE, 0x00,   //Q
  0xFE, 0x90, 0x6E, 0x00,   //R
  0x62, 0x92, 0x8C, 0x00,   //S
  0x80, 0xFE, 0x80, 0x00,   //T
  0xFE, 0x02, 0xFE, 0x00,   //U
  0xF8, 0x04, 0xFE, 0x00,   //V
  0xFE, 0x0C, 0xFE, 0x00,   //W
  0xEE, 0x10, 0xEE, 0x00,   //X
  0xF0, 0x1E, 0xF0, 0x00,   //Y
  0x8E, 0x92, 0xE2, 0x00,   //Z
  0x0E, 0x2A, 0x3E, 0x00,   //a
  0xFE, 0x12, 0x1E, 0x00,   //b
  0x1C, 0x22, 0x22, 0x00,   //c
  0x1E, 0x12, 0xFE, 0x00,   //d
  0x3E, 0x2A, 0x1A, 0x00,   //e
  0x7E, 0x90, 0x80, 0x00,   //f
  0x1A, 0x2A, 0x3E, 0x00,   //g
  0xFE, 0x10, 0x0E, 0x00,   //h
  0x00, 0x5E, 0x00, 0x00,   //i
  0x02, 0x5E, 0x00, 0x00,   //j
  0xFE, 0x10, 0x2E, 0x00,   //k
  0x00, 0xFE, 0x00, 0x00,   //l
  0x3E, 0x38, 0x1E, 0x00,   //m
  0x3E, 0x20, 0x1E, 0x00,   //n
  0x1C, 0x22, 0x1C, 0x00,   //o
  0x3E, 0x28, 0x18, 0x00,   //p
  0x18, 0x28, 0x3E, 0x00,   //q
  0x3E, 0x20, 0x10, 0x00,   //r
  0x12, 0x2A, 0x24, 0x00,   //s
  0x7C, 0x22, 0x02, 0x00,   //t
  0x3E, 0x02, 0x3E, 0x00,   //u
  0x38, 0x04, 0x3E, 0x00,   //v
  0x3E, 0x06, 0x3E, 0x00,   //w
  0x36, 0x08, 0x36, 0x00,   //x
  0x32, 0x0A, 0x3C, 0x00,   //y
  0x26, 0x2A, 0x32, 0x00,   //z
  0x00, 0x00, 0x00, 0x00};  //blank

char font2[62][4] = {              //4x7 font top aligned (uppercase 4x7)
  0x7C, 0x82, 0x82, 0x7C,   //0
  0x00, 0x42, 0xFE, 0x02,   //1
  0x0C, 0x92, 0x92, 0x60,   //2
  0x44, 0x92, 0x92, 0x6C,   //3
  0xF0, 0x10, 0x10, 0xFE,   //4
  0xF4, 0x92, 0x92, 0x8C,   //5
  0x7C, 0x92, 0x92, 0x4C,   //6
  0x80, 0x8E, 0x90, 0xE0,   //7
  0x6C, 0x92, 0x92, 0x6C,   //8
  0x60, 0x90, 0x90, 0xFE,   //9
  0x7E, 0x90, 0x90, 0x7E,   //A
  0xFE, 0x92, 0x92, 0x6C,   //B
  0x7C, 0x82, 0x82, 0x44,   //C
  0xFE, 0x82, 0x82, 0x7C,   //D
  0xFE, 0x92, 0x92, 0x82,   //E
  0xFE, 0x90, 0x90, 0x80,   //F
  0x7C, 0x82, 0x8A, 0x4C,   //G
  0xFE, 0x10, 0x10, 0xFE,   //H
  0x00, 0x82, 0xFE, 0x82,   //I
  0x04, 0x02, 0x82, 0xFC,   //J
  0xFE, 0x10, 0x28, 0xC6,   //K
  0xFE, 0x02, 0x02, 0x02,   //L
  0xFE, 0x60, 0x60, 0xFE,   //M
  0xFE, 0x60, 0x18, 0xFE,   //N
  0x7C, 0x82, 0x82, 0x7C,   //O
  0xFE, 0x90, 0x90, 0x60,   //P
  0x7C, 0x82, 0x86, 0x7E,   //Q
  0xFE, 0x90, 0x90, 0x6E,   //R
  0x64, 0x92, 0x92, 0x4C,   //S
  0x80, 0x80, 0xFE, 0x80,   //T
  0xFC, 0x02, 0x02, 0xFC,   //U
  0xFC, 0x02, 0x04, 0xF8,   //V
  0xFE, 0x0E, 0x0E, 0xFE,   //W
  0xEE, 0x10, 0x10, 0xEE,   //X
  0xE0, 0x1E, 0x10, 0xE0,   //Y
  0x8E, 0x92, 0xA2, 0xC2,   //Z
  0x04, 0x2A, 0x2A, 0x1E,   //a
  0xFE, 0x12, 0x12, 0x0C,   //b
  0x1C, 0x22, 0x22, 0x14,   //c
  0x0C, 0x12, 0x12, 0xFE,   //d
  0x1C, 0x2A, 0x2A, 0x18,   //e
  0x00, 0x7E, 0x90, 0x40,   //f
  0x18, 0x25, 0x25, 0x1E,   //g
  0xFE, 0x10, 0x10, 0x0E,   //h
  0x00, 0x00, 0x2E, 0x00,   //i
  0x02, 0x01, 0x2E, 0x00,   //j
  0xFE, 0x08, 0x14, 0x22,   //k
  0x00, 0x00, 0xFE, 0x00,   //l
  0x1E, 0x18, 0x18, 0x1E,   //m
  0x1E, 0x10, 0x10, 0x0E,   //n
  0x0C, 0x12, 0x12, 0x0C,   //o
  0x1F, 0x12, 0x12, 0x0C,   //p
  0x0C, 0x12, 0x12, 0x1F,   //q
  0x1E, 0x08, 0x10, 0x10,   //r
  0x10, 0x2A, 0x2A, 0x04,   //s
  0x00, 0x3C, 0x12, 0x04,   //t
  0x1C, 0x02, 0x02, 0x1C,   //u
  0x1C, 0x02, 0x04, 0x18,   //v
  0x1E, 0x06, 0x06, 0x1E,   //w
  0x12, 0x0C, 0x0C, 0x12,   //x
  0x19, 0x05, 0x07, 0x1C,   //y
  0x12, 0x16, 0x1A, 0x12};  //z



char font1[62][4] = {              //4x7 font base aligned (uppercase 4x7)
  0x3E, 0x51, 0x49, 0x3E,   //0
  0x00, 0x21, 0x7F, 0x01,   //1
  0x06, 0x49, 0x49, 0x30,   //2
  0x22, 0x49, 0x49, 0x36,   //3
  0x78, 0x08, 0x08, 0x7F,   //4
  0x7A, 0x49, 0x49, 0x46,   //5
  0x3E, 0x49, 0x49, 0x26,   //6
  0x40, 0x47, 0x48, 0x70,   //7
  0x36, 0x49, 0x49, 0x36,   //8
  0x32, 0x49, 0x49, 0x3E,   //9
  0x3F, 0x48, 0x48, 0x3F,   //A
  0x7F, 0x49, 0x49, 0x36,   //B
  0x3E, 0x41, 0x41, 0x22,   //C
  0x7F, 0x41, 0x41, 0x3E,   //D
  0x7F, 0x49, 0x49, 0x41,   //E
  0x7F, 0x48, 0x48, 0x40,   //F
  0x3E, 0x41, 0x45, 0x26,   //G
  0x7F, 0x08, 0x08, 0x7F,   //H
  0x00, 0x41, 0x7F, 0x41,   //I
  0x02, 0x01, 0x41, 0x7E,   //J
  0x7F, 0x08, 0x14, 0x63,   //K
  0x7F, 0x01, 0x01, 0x01,   //L
  0x7F, 0x30, 0x30, 0x7F,   //M
  0x7F, 0x30, 0x0C, 0x7F,   //N
  0x3E, 0x41, 0x41, 0x3E,   //O
  0x7F, 0x48, 0x48, 0x30,   //P
  0x3E, 0x41, 0x43, 0x3F,   //Q
  0x7F, 0x48, 0x48, 0x37,   //R
  0x32, 0x49, 0x49, 0x26,   //S
  0x40, 0x40, 0x7F, 0x40,   //T
  0x7E, 0x01, 0x01, 0x7E,   //U
  0x7E, 0x01, 0x02, 0x7C,   //V
  0x7F, 0x07, 0x07, 0x7F,   //W
  0x77, 0x08, 0x08, 0x77,   //X
  0x70, 0x0F, 0x08, 0x70,   //Y
  0x47, 0x49, 0x51, 0x61,   //Z
  0x02, 0x15, 0x15, 0x0F,   //a
  0x7F, 0x09, 0x09, 0x06,   //b
  0x0E, 0x11, 0x11, 0x0A,   //c
  0x06, 0x09, 0x09, 0x7F,   //d
  0x0E, 0x15, 0x15, 0x0C,   //e
  0x00, 0x3F, 0x48, 0x20,   //f
  0x18, 0x25, 0x25, 0x1E,   //g
  0x7F, 0x08, 0x08, 0x07,   //h
  0x00, 0x00, 0x17, 0x00,   //i
  0x02, 0x01, 0x2E, 0x00,   //j
  0x7F, 0x04, 0x0A, 0x11,   //k
  0x00, 0x00, 0x7F, 0x00,   //l
  0x0F, 0x0C, 0x0C, 0x0F,   //m
  0x0F, 0x08, 0x08, 0x07,   //n
  0x06, 0x09, 0x09, 0x06,   //o
  0x1F, 0x12, 0x12, 0x0C,   //p
  0x0C, 0x12, 0x12, 0x1F,   //q
  0x0F, 0x04, 0x08, 0x08,   //r
  0x08, 0x15, 0x15, 0x02,   //s
  0x00, 0x1E, 0x09, 0x02,   //t
  0x0E, 0x01, 0x01, 0x0E,   //u
  0x0E, 0x01, 0x02, 0x0C,   //v
  0x0F, 0x03, 0x03, 0x0F,   //w
  0x09, 0x06, 0x06, 0x09,   //x
  0x19, 0x05, 0x07, 0x1C,   //y
  0x09, 0x0B, 0x0D, 0x09};  //z

