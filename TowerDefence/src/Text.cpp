
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "Text.hpp"

const int Text::FONT_NORMAL	= 0;
const int Text::FONT_SMALL	= 1;
//const int Text::FONT_LARGE	= 2;

Text::Text()
{
	///////////////////////// NORMAL_FONT /////////////////////////////
	_curfont = FONT_NORMAL;

	{
	GLubyte bm_09[10][13] = {
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xd3, 0xdb, 0xcb, 0xc7, 0xc3, 0x66, 0x3c}, // 0
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18}, // 1
		{0x00, 0x00, 0xff, 0xe0, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x66, 0x3c}, // 2
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0x03, 0x06, 0x1c, 0x06, 0x03, 0xc3, 0x66, 0x3c}, // 3
		{0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0xff, 0xc6, 0x66, 0x36, 0x1e, 0x0e, 0x06}, // 4
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0x03, 0xc3, 0xf6, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, // 5
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xe6, 0xfc, 0xc0, 0x60, 0x30, 0x1e}, // 6
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff}, // 7
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0x66, 0x3c, 0x66, 0xc3, 0xc3, 0x66, 0x3c}, // 8
		{0x00, 0x00, 0x78, 0x0c, 0x06, 0x03, 0x3f, 0x67, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, // 9
	};
	GLubyte bm_az[26][13] = {
		{0x00, 0x00, 0x3d, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // a
		{0x00, 0x00, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x60}, // b
		{0x00, 0x00, 0x3c, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // c
		{0x00, 0x00, 0x3e, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3e, 0x06, 0x06, 0x06, 0x06}, // d
		{0x00, 0x00, 0x3c, 0x66, 0x60, 0x7e, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // e
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x7c, 0x30, 0x30, 0x36, 0x1c}, // f
		{0x3c, 0x66, 0x06, 0x3e, 0x66, 0x66, 0x66, 0x66, 0x3e, 0x00, 0x00, 0x00, 0x00}, // g
		{0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x60}, // h
		{0x00, 0x00, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00}, // i
		{0x3c, 0x66, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00}, // j
		{0x00, 0x00, 0x66, 0x66, 0x6c, 0x78, 0x78, 0x6c, 0x66, 0x60, 0x60, 0x60, 0x60}, // k
		{0x00, 0x00, 0x3c, 0x66, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60}, // l
		{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xd6, 0xd6, 0xfc, 0x00, 0x00, 0x00, 0x00}, // m
		{0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x00, 0x00, 0x00, 0x00}, // n
		{0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // o
		{0x60, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x00, 0x00, 0x00, 0x00}, // p
		{0x06, 0x06, 0x06, 0x3e, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // q
		{0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x6c, 0x7c, 0x00, 0x00, 0x00, 0x00}, // r
		{0x00, 0x00, 0x3c, 0x66, 0x06, 0x3c, 0x60, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00}, // s
		{0x00, 0x00, 0x3c, 0x66, 0x60, 0x60, 0x60, 0x60, 0x60, 0xf8, 0x60, 0x60, 0x60}, // t
		{0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00}, // u
		{0x00, 0x00, 0x18, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00}, // v
		{0x00, 0x00, 0x6c, 0xd6, 0xd6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00}, // w
		{0x00, 0x00, 0x66, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00}, // x
		{0x3c, 0x66, 0x06, 0x3e, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00}, // y
		{0x00, 0x00, 0x7e, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x7e, 0x00, 0x00, 0x00, 0x00}  // z
	};
	GLubyte bm_AZ[26][13] = {
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, // A
		{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // B
		{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, // C
		{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc}, // D
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, // E
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, // F
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, // G
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // H
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, // I
		{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06}, // J
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3}, // K
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, // L
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3}, // M
		{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3}, // N
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e}, // O
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // P
		{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, // Q
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // R
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e}, // S
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff}, // T
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // U
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // V
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, // W
		{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, // X
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, // Y
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}  // Z
	};
	GLubyte bm_ae[13] =				{0x00, 0x00, 0x76, 0x99, 0x98, 0x7e, 0x19, 0xd9, 0x7e, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_AE[13] =				{0x00, 0x00, 0xcf, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xcc, 0xcc, 0xcc, 0x7c, 0x3f};
	GLubyte bm_oe[13] =				{0x00, 0x00, 0x7c, 0x66, 0x76, 0x6e, 0x6e, 0x66, 0x3e, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_OE[13] =				{0x00, 0x00, 0xfe, 0xe7, 0xc3, 0xf3, 0xf3, 0xdb, 0xdf, 0xcf, 0xc7, 0xe7, 0x7f};
	GLubyte bm_aa[13] =				{0x00, 0x00, 0x3d, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x3c, 0x00, 0x18, 0x18, 0x00};
	GLubyte bm_AA[13] =				{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0x7e, 0x3c, 0x18, 0x18};
	GLubyte bm_Space[13] =		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Dot[13] =			{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Comma[13] =		{0x10, 0x08, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Colon[13] =		{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00};
	GLubyte bm_Exclam[13] =		{0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
	GLubyte bm_Question[13] =	{0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0x66, 0x3c};
	GLubyte bm_ParantL[13] =	{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c};
	GLubyte bm_ParantR[13] =	{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30};
	GLubyte bm_Minus[13] =		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Plus[13] =			{0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0x00, 0x00};
	GLubyte bm_Slash[13] =		{0x00, 0x00, 0xc0, 0xc0, 0x60, 0x30, 0x30, 0x18, 0x0c, 0x0c, 0x06, 0x03, 0x03};
	GLubyte bm_Percent[13] =	{0x00, 0x00, 0xc6, 0xc9, 0x69, 0x36, 0x30, 0x18, 0x0c, 0x6c, 0x96, 0x93, 0x63};
	GLubyte bm_Hat[13] =			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3c, 0x18};
	GLubyte bm_GT[13] =				{0x00, 0x00, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x40};
	GLubyte bm_LT[13] =				{0x00, 0x00, 0x02, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02};
	GLubyte bm_Equal[13] =		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00};

	GLubyte bm_NA[13] =				{0x00, 0x00, 0x00, 0x00, 0x09, 0x4f, 0x29, 0x16, 0x08, 0xb4, 0xb2, 0xd1, 0xd0};


	int i;
	for(i = 0; i < 128; i++)		// Reset all characters
		FillBitmapChar(i, bm_NA);

	for(i = 0; i < 10; i++)
		FillBitmapChar('0' + i, bm_09[i]);	// 0-9
	for(i = 0; i < 26; i++)
		FillBitmapChar('a' + i, bm_az[i]);	// a-z
	for(i = 0; i < 26; i++)
		FillBitmapChar('A' + i, bm_AZ[i]);	// A-Z
	FillBitmapChar(3, bm_ae);						// �
	FillBitmapChar(4, bm_AE);						// �
	FillBitmapChar(5, bm_oe);						// �
	FillBitmapChar(6, bm_OE);						// �
	FillBitmapChar(7, bm_aa);						// �
	FillBitmapChar(8, bm_AA);						// �
	FillBitmapChar(' ', bm_Space);				// Space
	FillBitmapChar('.', bm_Dot);					// .
	FillBitmapChar(',', bm_Comma);				// ,
	FillBitmapChar(':', bm_Colon);				// :
	FillBitmapChar('!', bm_Exclam);				// !
	FillBitmapChar('?', bm_Question);			// ?
	FillBitmapChar('(', bm_ParantL);			// (
	FillBitmapChar(')', bm_ParantR);			// )
	FillBitmapChar('-', bm_Minus);				// -
	FillBitmapChar('+', bm_Plus);					// +
	FillBitmapChar('/', bm_Slash);				// /
	FillBitmapChar('%', bm_Percent);			// %
	FillBitmapChar('^', bm_Hat);					// ^
	FillBitmapChar('>', bm_GT);						// >
	FillBitmapChar('<', bm_LT);						// <
	FillBitmapChar('=', bm_Equal);				// =
	}

	////////////////////////// SMALL_FONT /////////////////////////////
	_curfont = FONT_SMALL;
	{
	GLubyte bm_09[10][13] = {
		{0x0e, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0
		{0x0e, 0x04, 0x04, 0x04, 0x04, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 1
		{0x1f, 0x10, 0x08, 0x06, 0x01, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 2
		{0x0e, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 3
		{0x01, 0x01, 0x01, 0x1f, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 4
		{0x0e, 0x11, 0x01, 0x1e, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 5
		{0x0e, 0x11, 0x11, 0x1e, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 6
		{0x04, 0x04, 0x04, 0x04, 0x02, 0x01, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 7
		{0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 8
		{0x0e, 0x11, 0x01, 0x0f, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 9
	};
	GLubyte bm_AZ[26][13] = {
		{0x11, 0x11, 0x11, 0x1f, 0x11, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // A
		{0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // B
		{0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // C
		{0x1e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // D
		{0x1f, 0x10, 0x10, 0x1c, 0x10, 0x10, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // E
		{0x10, 0x10, 0x10, 0x1c, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // F
		{0x0e, 0x11, 0x11, 0x17, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // G
		{0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // H
		{0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // I
		{0x0e, 0x11, 0x01, 0x01, 0x01, 0x01, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // J
		{0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // K
		{0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // L
		{0x11, 0x11, 0x11, 0x15, 0x15, 0x1b, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // M
		{0x11, 0x13, 0x13, 0x15, 0x19, 0x19, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // N
		{0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // O
		{0x10, 0x10, 0x10, 0x1e, 0x11, 0x11, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // P
		{0x0f, 0x13, 0x15, 0x11, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Q
		{0x11, 0x12, 0x14, 0x1e, 0x11, 0x11, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // R
		{0x0e, 0x11, 0x01, 0x0e, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // S
		{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // T
		{0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U
		{0x04, 0x0a, 0x0a, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // V
		{0x0a, 0x15, 0x15, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // W
		{0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // X
		{0x04, 0x04, 0x04, 0x0a, 0x0a, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Y
		{0x1f, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Z
	};
	GLubyte bm_AE[13] =				{0x13, 0x12, 0x12, 0x1f, 0x12, 0x12, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_OE[13] =				{0x1e, 0x19, 0x15, 0x15, 0x15, 0x12, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_AA[13] =				{0x11, 0x11, 0x1f, 0x11, 0x0e, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Space[13] =		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Dot[13] =			{0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Comma[13] =		{0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Colon[13] =		{0x06, 0x06, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Exclam[13] =		{0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Question[13] =	{0x04, 0x00, 0x04, 0x02, 0x01, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_ParantL[13] =	{0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_ParantR[13] =	{0x0c, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Minus[13] =		{0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Plus[13] =			{0x00, 0x00, 0x04, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Slash[13] =		{0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Percent[13] =	{0x13, 0x0b, 0x08, 0x04, 0x02, 0x1a, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Hat[13] =			{0x00, 0x00, 0x00, 0x00, 0x11, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_GT[13] =				{0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_LT[13] =				{0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	GLubyte bm_Equal[13] =		{0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	GLubyte bm_NA[13] =				{0x05, 0x17, 0x0a, 0x04, 0x16, 0x1d, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


	int i;
	for(i = 0; i < 128; i++)		// Reset all characters
		FillBitmapChar(i, bm_NA);

	for(i = 0; i < 10; i++)
		FillBitmapChar('0' + i, bm_09[i]);	// 0-9
	for(i = 0; i < 26; i++)
		FillBitmapChar('a' + i, bm_AZ[i]);	// a-z
	for(i = 0; i < 26; i++)
		FillBitmapChar('A' + i, bm_AZ[i]);	// A-Z
	FillBitmapChar(3, bm_AE);						// �
	FillBitmapChar(4, bm_AE);						// �
	FillBitmapChar(5, bm_OE);						// �
	FillBitmapChar(6, bm_OE);						// �
	FillBitmapChar(7, bm_AA);						// �
	FillBitmapChar(8, bm_AA);						// �
	FillBitmapChar(' ', bm_Space);				// Space
	FillBitmapChar('.', bm_Dot);					// .
	FillBitmapChar(',', bm_Comma);				// ,
	FillBitmapChar(':', bm_Colon);				// :
	FillBitmapChar('!', bm_Exclam);				// !
	FillBitmapChar('?', bm_Question);			// ?
	FillBitmapChar('(', bm_ParantL);			// (
	FillBitmapChar(')', bm_ParantR);			// )
	FillBitmapChar('-', bm_Minus);				// -
	FillBitmapChar('+', bm_Plus);					// +
	FillBitmapChar('/', bm_Slash);				// /
	FillBitmapChar('%', bm_Percent);			// %
	FillBitmapChar('^', bm_Hat);					// ^
	FillBitmapChar('>', bm_GT);						// >
	FillBitmapChar('<', bm_LT);						// <
	FillBitmapChar('=', bm_Equal);				// =
	}

/*
		////////////////////////// LARGE_FONT /////////////////////////////
	_curfont = FONT_LARGE;
	{
	GLubyte bm_09[10][26] = {
		{0x0e, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0
		{0x0e, 0x04, 0x04, 0x04, 0x04, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 1
		{0x1f, 0x10, 0x08, 0x06, 0x01, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 2
		{0x0e, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 3
		{0x01, 0x01, 0x01, 0x1f, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 4
		{0x0e, 0x11, 0x01, 0x1e, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 5
		{0x0e, 0x11, 0x11, 0x1e, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 6
		{0x04, 0x04, 0x04, 0x04, 0x02, 0x01, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 7
		{0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 8
		{0x0e, 0x11, 0x01, 0x0f, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 9
	};

	GLubyte bm_NA[13] =				{0x05, 0x17, 0x0a, 0x04, 0x16, 0x1d, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


	int i;
	for(i = 0; i < 128; i++)		// Reset all characters
		FillBitmapChar(i, bm_NA);

	for(i = 0; i < 10; i++)
		FillBitmapChar('0' + i, bm_09[i]);	// 0-9
	}
*/
	this->setFont(FONT_NORMAL);
}

Text::~Text()
{
	glDeleteLists(_fontOffset[FONT_NORMAL], 128);
	glDeleteLists(_fontOffset[FONT_SMALL], 128);
//	glDeleteLists(_fontOffset[FONT_LARGE], 128);
}


void Text::FillBitmapChar(char index, GLubyte bitmap[])
{
	for(int i = 0; i < 13; i++)
		_letters[_curfont][index][i] = bitmap[i];
}

void Text::makeRasterFont(void)
{
	GLuint i;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	_fontOffset[FONT_NORMAL] = glGenLists(128);
	for (i = 0; i < 128; i++) {
		glNewList(_fontOffset[FONT_NORMAL] + i, GL_COMPILE);
		glBitmap(8, 13, 0.0, 0.0, 9.0, 0.0, _letters[FONT_NORMAL][i]);
		glEndList();
	}

	_fontOffset[FONT_SMALL] = glGenLists(128);
	for (i = 0; i < 128; i++) {
		glNewList(_fontOffset[FONT_SMALL] + i, GL_COMPILE);
		glBitmap(8, 13, 0.0, 0.0, 6.0, 0.0, _letters[FONT_SMALL][i]);
		glEndList();
	}
/*
	_fontOffset[FONT_LARGE] = glGenLists(128);
	for (i = 0; i < 128; i++) {
		glNewList(_fontOffset[FONT_LARGE] + i, GL_COMPILE);
		glBitmap(16, 26, 0.0, 0.0, 18.0, 0.0, _letters[FONT_LARGE][i]);
		glEndList();
	}
*/
}

float Text::getCharWidth(int font) const
{
	if(font == -1) font = _curfont;
	return font == FONT_NORMAL ? 10.0f : 6.0f;
}

void Text::init(void)
{
   makeRasterFont();
}

void Text::printString(const char *s, int font) const
{
	char *c = new char[strlen(s) + 1];
	strcpy(c, s);

	for(unsigned int i = 0; i < strlen(c); i++)
	{
		if(c[i] == '�') c[i] = 3;
		if(c[i] == '�') c[i] = 4;
		if(c[i] == '�') c[i] = 5;
		if(c[i] == '�') c[i] = 6;
		if(c[i] == '�') c[i] = 7;
		if(c[i] == '�') c[i] = 8;
		if((c[i] > 127) || (c[i] < 0)) c[i] = 1;
	}

	if(font == -1) font = _curfont;
	glRasterPos3f(_pos[0], _pos[1], _pos[2]);
	glPushAttrib (GL_LIST_BIT);
	glListBase(_fontOffset[font]);
	glCallLists(strlen(c), GL_UNSIGNED_BYTE, (GLubyte *) c);

	delete[] c;

	glPopAttrib ();
}


