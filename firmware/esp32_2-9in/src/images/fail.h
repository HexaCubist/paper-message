#pragma once
const unsigned char IMAGE_FAIL[] = {
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x1f,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xdf,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xdf,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xff,0xff,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x81,0xfd,0xdf,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xfc,0xdf,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xfa,0xdf,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x3f,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xf0,0xff,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xf0,0xff,0xc3,0xff,0xff,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xc0,0x3f,0xbd,0xff,0xdf,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xc0,0x3f,0xbd,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xc0,0x3f,0xbd,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xc0,0x3f,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xff,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0f,0xc3,0xff,0xf5,0xff,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0f,0xc3,0xff,0x8d,0xfc,0x3f,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x03,0x00,0xff,0xff,0xfb,0xdf,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x03,0x00,0xff,0xff,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfc,0x3f,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xc0,0x03,0xff,0x01,0xfd,0xdf,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xc0,0x03,0xff,0xdd,0xfd,0xdf,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xf0,0x0f,0xff,0xdd,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xf0,0x0f,0xff,0xdd,0xf0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xf0,0x3f,0xff,0xe3,0xff,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0x3f,0xff,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0x3f,0xff,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xc1,0xff,0xff,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xbf,0xff,0xff,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xdf,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0xc1,0xfb,0xff,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0xff,0xfb,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xff,0xfd,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xc1,0xfc,0x1f,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xad,0xff,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xad,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xc3,0xff,0xad,0xfc,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xc3,0xff,0xf3,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc3,0xc0,0xff,0xff,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc3,0xc0,0xff,0xff,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xff,0xff,0xff,0x81,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xff,0xfc,0xdf,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xc0,0xff,0xf9,0xfa,0xdf,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xc0,0xff,0xfe,0xfa,0xdf,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfa,0xdf,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0x81,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xba,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0xba,0xfb,0xff,0xbd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0xba,0xfb,0xff,0xbd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xc7,0xfd,0xff,0xbd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xff,0xf8,0x1f,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xfd,0xdf,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xbf,0xfb,0xdf,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xdf,0xfb,0xdf,0xf5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xc0,0x03,0xff,0xc1,0xfb,0xdf,0x8d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xc0,0x03,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x03,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x00,0xff,0xbd,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x00,0xff,0xbd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xbd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xc3,0xfa,0xdf,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0xc0,0xff,0xff,0xfd,0xbf,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0xc0,0xff,0xff,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x00,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x00,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xdf,0xff,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0x81,0xff,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0x83,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xfd,0xfa,0xdf,0xcd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xfd,0xfa,0xdf,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xc3,0xfd,0xbf,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0xff,0xff,0xad,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xdf,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xf4,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0xc0,0x03,0xff,0xff,0xfd,0xdf,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xc0,0x03,0xff,0xff,0xff,0xff,0xdd,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0xc0,0x03,0xff,0xff,0xff,0xff,0xdd,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x03,0xff,0xff,0xfe,0x1f,0x03,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x01,0xff,0x8f,0xfd,0xff,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0x00,0xff,0xf3,0xfd,0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0xf5,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc0,0xc0,0xff,0x8d,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0xc0,0xff,0xff,0xff,0xff,0xff,0xfc,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0xc0,0xff,0xff,0xff,0xff,0xff,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xc0,0xff,0xbf,0xfd,0xdf,0x01,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x00,0xff,0xbf,0xfd,0xdf,0xdd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x00,0xff,0xdf,0xfd,0xdf,0xdd,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0x81,0xf0,0x3f,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xe3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xfc,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xcd,0xff,0xff,0xff,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xad,0xff,0xff,0xfd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xad,0xff,0xff,0xfd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xad,0xff,0xff,0x83,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xc3,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xaf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xaf,0x81,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0x8f,0xfb,0xaf,0xfb,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xf3,0xfc,0x7f,0xfd,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xfd,0xff,0xff,0xfd,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xf3,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0x8f,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xfb,0xff,0xff,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xfb,0xff,0xc3,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xfd,0xff,0xbd,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3c,0x00,0xff,0xff,0xfc,0x1f,0xbd,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x3c,0x00,0xff,0xff,0xff,0xff,0xbd,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xdd,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xfc,0x00,0xff,0xdd,0xf4,0x1f,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xfc,0x00,0xff,0xdd,0xfd,0xdf,0xdd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0xfc,0x00,0xff,0x03,0xff,0xff,0xbd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xbd,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xf8,0x3f,0xbd,0xfd,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xc1,0xff,0xdf,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xbf,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xbf,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x3f,0xff,0xdf,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x3f,0xff,0xc1,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcd,0xfc,0x3f,0x7d,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x03,0xff,0xad,0xfb,0xdf,0x01,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x03,0xff,0xad,0xfb,0xdf,0x7d,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x30,0x03,0xff,0xad,0xfb,0xdf,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x30,0x03,0xff,0xc3,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0x83,0xfe,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xfd,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xfd,0xfd,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xc3,0xfe,0xff,0xdf,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xc3,0xc0,0xff,0xfd,0xf0,0x1f,0xdf,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xc3,0xc0,0xff,0xc3,0xff,0xff,0xef,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc3,0xc0,0xff,0xff,0xff,0xff,0x01,0xf0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xc3,0xc0,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfa,0xdf,0xf3,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xfa,0xdf,0xad,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xfd,0xbf,0xad,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0x81,0xff,0xff,0xad,0xfa,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0xff,0xba,0xff,0xff,0xdb,0xfd,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xba,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xba,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0xff,0xff,0xfd,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x41,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xdd,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xfa,0xdf,0xff,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xfa,0xdf,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xfa,0xdf,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xfd,0xbf,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xfd,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xff,0xff,0xdf,0xfd,0xfb,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x03,0xff,0xfd,0xf4,0x1f,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0xff,0x41,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x03,0xff,0xdf,0xff,0xff,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0xff,0xff,0xdf,0xff,0xff,0x7d,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0xff,0xff,0xef,0xfc,0xdf,0x01,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x01,0xfa,0xdf,0x7d,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xfa,0xdf,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xfa,0xdf,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xdd,0xfc,0x3f,0xff,0xfc,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0x03,0xfd,0xdf,0xff,0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfb,0xdf,0xfd,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xcd,0xfb,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xad,0xfc,0x3f,0x83,0xf7,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xad,0xff,0xff,0xfd,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xff,0xff,0xfd,0xf7,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xff,0xdf,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf4,0x1f,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xff,0xfd,0xdf,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xc1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x03,0xff,0xbf,0xf8,0xff,0xc3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xc1,0xff,0x3f,0xbd,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xbf,0xff,0xdf,0xbd,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xbf,0xff,0x3f,0xbd,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xc1,0xf8,0xff,0xc3,0xf0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf0,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,0xf0,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xfc,0x00,0xff,0xc3,0xfc,0xdf,0xc1,0xf8,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xfc,0x00,0xff,0xbd,0xfa,0xdf,0xbf,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xfc,0x00,0xff,0xbd,0xfa,0xdf,0xbf,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0xfc,0x00,0xff,0xbd,0xfa,0xdf,0xdf,0xff,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xf0,0x00,0xff,0xc3,0xfc,0x3f,0xc1,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xf0,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x03,0xff,0xb3,0xf0,0x1f,0xbd,0xfe,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0x6d,0xfd,0xdf,0xdb,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0x6d,0xfd,0xdf,0xe7,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0x6d,0xfd,0xdf,0xf7,0xfd,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0x9b,0xfe,0x3f,0x81,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x33,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x1b,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x51,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x04,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x3b,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x26,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x56,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x49,0xbb,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0x9f,0xe8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x49,0xac,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xe3,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0xe3,0xdc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x55,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x55,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x59,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x25,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x55,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x7d,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x71,0xfc,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03};