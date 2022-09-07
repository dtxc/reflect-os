/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

#define HOME 0x47
#define END 0x4F

#define SYSRQ 0x54
#define SYSRQ_RELEASE 0xD4
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define DELETE 0x53
#define ALT 0x38
#define ALT_RELEASE 0xB8
#define CTRL 0x1D
#define CTRL_RELEASE 0x9D
#define TAB 0x0F

#define SHIFT 0x2A
#define RSHIFT 0x36
#define CAPS_LOCK 0x3A
#define SHIFT_RELEASE 0xAA 
#define RSHIFT_RELEASE 0xB6

#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define RIGHT_ARROW 0x4D
#define LEFT_ARROW 0x4B

#define FUNCTION1 0x3B
#define FUNCTION2 0x3C
#define FUNCTION3 0x3D
#define FUNCTION4 0x3E
#define FUNCTION5 0x3F
#define FUNCTION6 0x40
#define FUNCTION7 0x41
#define FUNCTION8 0x42
#define FUNCTION9 0x43
#define FUNCTION10 0x44

/*
#define POWER 0xE05E
#define POWER1 0xE0DE
*/

void init_keyboard();
