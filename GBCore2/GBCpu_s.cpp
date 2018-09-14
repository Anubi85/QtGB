#include "GBCpu.h"

GBInstruction GBCpu::s_InstructionTable[INSTRUCTIONS_NUM] =
{
    //Regular instruction set
    nullptr,            //0x00
    &GBCpu::LD_rr_nn,   //0x01
    nullptr,            //0x02
    nullptr,            //0x03
    nullptr,            //0x04
    nullptr,            //0x05
    nullptr,            //0x06
    nullptr,            //0x07
    nullptr,            //0x08
    nullptr,            //0x09
    nullptr,            //0x0A
    nullptr,            //0x0B
    nullptr,            //0x0C
    nullptr,            //0x0D
    nullptr,            //0x0E
    nullptr,            //0x0F
    nullptr,            //0x10
    &GBCpu::LD_rr_nn,   //0x11
    nullptr,            //0x12
    nullptr,            //0x13
    nullptr,            //0x14
    nullptr,            //0x15
    nullptr,            //0x16
    nullptr,            //0x17
    nullptr,            //0x18
    nullptr,            //0x19
    nullptr,            //0x1A
    nullptr,            //0x1B
    nullptr,            //0x1C
    nullptr,            //0x1D
    nullptr,            //0x1E
    nullptr,            //0x1F
    nullptr,            //0x20
    &GBCpu::LD_rr_nn,   //0x21
    nullptr,            //0x22
    nullptr,            //0x23
    nullptr,            //0x24
    nullptr,            //0x25
    nullptr,            //0x26
    nullptr,            //0x27
    nullptr,            //0x28
    nullptr,            //0x29
    nullptr,            //0x2A
    nullptr,            //0x2B
    nullptr,            //0x2C
    nullptr,            //0x2D
    nullptr,            //0x2E
    nullptr,            //0x2F
    nullptr,            //0x30
    &GBCpu::LD_rr_nn,   //0x31
    nullptr,            //0x32
    nullptr,            //0x33
    nullptr,            //0x34
    nullptr,            //0x35
    nullptr,            //0x36
    nullptr,            //0x37
    nullptr,            //0x38
    nullptr,            //0x39
    nullptr,            //0x3A
    nullptr,            //0x3B
    nullptr,            //0x3C
    nullptr,            //0x3D
    nullptr,            //0x3E
    nullptr,            //0x3F
    nullptr,            //0x40
    nullptr,            //0x41
    nullptr,            //0x42
    nullptr,            //0x43
    nullptr,            //0x44
    nullptr,            //0x45
    nullptr,            //0x46
    nullptr,            //0x47
    nullptr,            //0x48
    nullptr,            //0x49
    nullptr,            //0x4A
    nullptr,            //0x4B
    nullptr,            //0x4C
    nullptr,            //0x4D
    nullptr,            //0x4E
    nullptr,            //0x4F
    nullptr,            //0x50
    nullptr,            //0x51
    nullptr,            //0x52
    nullptr,            //0x53
    nullptr,            //0x54
    nullptr,            //0x55
    nullptr,            //0x56
    nullptr,            //0x57
    nullptr,            //0x58
    nullptr,            //0x59
    nullptr,            //0x5A
    nullptr,            //0x5B
    nullptr,            //0x5C
    nullptr,            //0x5D
    nullptr,            //0x5E
    nullptr,            //0x5F
    nullptr,            //0x60
    nullptr,            //0x61
    nullptr,            //0x62
    nullptr,            //0x63
    nullptr,            //0x64
    nullptr,            //0x65
    nullptr,            //0x66
    nullptr,            //0x67
    nullptr,            //0x68
    nullptr,            //0x69
    nullptr,            //0x6A
    nullptr,            //0x6B
    nullptr,            //0x6C
    nullptr,            //0x6D
    nullptr,            //0x6E
    nullptr,            //0x6F
    nullptr,            //0x70
    nullptr,            //0x71
    nullptr,            //0x72
    nullptr,            //0x73
    nullptr,            //0x74
    nullptr,            //0x75
    nullptr,            //0x76
    nullptr,            //0x77
    nullptr,            //0x78
    nullptr,            //0x79
    nullptr,            //0x7A
    nullptr,            //0x7B
    nullptr,            //0x7C
    nullptr,            //0x7D
    nullptr,            //0x7E
    nullptr,            //0x7F
    nullptr,            //0x80
    nullptr,            //0x81
    nullptr,            //0x82
    nullptr,            //0x83
    nullptr,            //0x84
    nullptr,            //0x85
    nullptr,            //0x86
    nullptr,            //0x87
    nullptr,            //0x88
    nullptr,            //0x89
    nullptr,            //0x8A
    nullptr,            //0x8B
    nullptr,            //0x8C
    nullptr,            //0x8D
    nullptr,            //0x8E
    nullptr,            //0x8F
    nullptr,            //0x90
    nullptr,            //0x91
    nullptr,            //0x92
    nullptr,            //0x93
    nullptr,            //0x94
    nullptr,            //0x95
    nullptr,            //0x96
    nullptr,            //0x97
    nullptr,            //0x98
    nullptr,            //0x99
    nullptr,            //0x9A
    nullptr,            //0x9B
    nullptr,            //0x9C
    nullptr,            //0x9D
    nullptr,            //0x9E
    nullptr,            //0x9F
    nullptr,            //0xA0
    nullptr,            //0xA1
    nullptr,            //0xA2
    nullptr,            //0xA3
    nullptr,            //0xA4
    nullptr,            //0xA5
    nullptr,            //0xA6
    nullptr,            //0xA7
    &GBCpu::XOR_n,      //0xA8
    &GBCpu::XOR_n,      //0xA9
    &GBCpu::XOR_n,      //0xAA
    &GBCpu::XOR_n,      //0xAB
    &GBCpu::XOR_n,      //0xAC
    &GBCpu::XOR_n,      //0xAD
    &GBCpu::XOR_n,      //0xAE
    &GBCpu::XOR_n,      //0xAF
    nullptr,            //0xB0
    nullptr,            //0xB1
    nullptr,            //0xB2
    nullptr,            //0xB3
    nullptr,            //0xB4
    nullptr,            //0xB5
    nullptr,            //0xB6
    nullptr,            //0xB7
    nullptr,            //0xB8
    nullptr,            //0xB9
    nullptr,            //0xBA
    nullptr,            //0xBB
    nullptr,            //0xBC
    nullptr,            //0xBD
    nullptr,            //0xBE
    nullptr,            //0xBF
    nullptr,            //0xC0
    nullptr,            //0xC1
    nullptr,            //0xC2
    nullptr,            //0xC3
    nullptr,            //0xC4
    nullptr,            //0xC5
    nullptr,            //0xC6
    nullptr,            //0xC7
    nullptr,            //0xC8
    nullptr,            //0xC9
    nullptr,            //0xCA
    nullptr,            //0xCB
    nullptr,            //0xCC
    nullptr,            //0xCD
    nullptr,            //0xCE
    nullptr,            //0xCF
    nullptr,            //0xD0
    nullptr,            //0xD1
    nullptr,            //0xD2
    nullptr,            //0xD3
    nullptr,            //0xD4
    nullptr,            //0xD5
    nullptr,            //0xD6
    nullptr,            //0xD7
    nullptr,            //0xD8
    nullptr,            //0xD9
    nullptr,            //0xDA
    nullptr,            //0xDB
    nullptr,            //0xDC
    nullptr,            //0xDD
    nullptr,            //0xDE
    nullptr,            //0xDF
    nullptr,            //0xE0
    nullptr,            //0xE1
    nullptr,            //0xE2
    nullptr,            //0xE3
    nullptr,            //0xE4
    nullptr,            //0xE5
    nullptr,            //0xE6
    nullptr,            //0xE7
    nullptr,            //0xE8
    nullptr,            //0xE9
    nullptr,            //0xEA
    nullptr,            //0xEB
    nullptr,            //0xEC
    nullptr,            //0xED
    &GBCpu::XOR_n,      //0xEE
    nullptr,            //0xEF
    nullptr,            //0xF0
    nullptr,            //0xF1
    nullptr,            //0xF2
    nullptr,            //0xF3
    nullptr,            //0xF4
    nullptr,            //0xF5
    nullptr,            //0xF6
    nullptr,            //0xF7
    nullptr,            //0xF8
    nullptr,            //0xF9
    nullptr,            //0xFA
    nullptr,            //0xFB
    nullptr,            //0xFC
    nullptr,            //0xFD
    nullptr,            //0xFE
    nullptr,            //0xFF
};

GBInstruction GBCpu::s_CBInstructionTable[INSTRUCTIONS_NUM] =
{
    //Regular instruction set
    nullptr,            //0x00
    nullptr,            //0x01
    nullptr,            //0x02
    nullptr,            //0x03
    nullptr,            //0x04
    nullptr,            //0x05
    nullptr,            //0x06
    nullptr,            //0x07
    nullptr,            //0x08
    nullptr,            //0x09
    nullptr,            //0x0A
    nullptr,            //0x0B
    nullptr,            //0x0C
    nullptr,            //0x0D
    nullptr,            //0x0E
    nullptr,            //0x0F
    nullptr,            //0x10
    nullptr,            //0x11
    nullptr,            //0x12
    nullptr,            //0x13
    nullptr,            //0x14
    nullptr,            //0x15
    nullptr,            //0x16
    nullptr,            //0x17
    nullptr,            //0x18
    nullptr,            //0x19
    nullptr,            //0x1A
    nullptr,            //0x1B
    nullptr,            //0x1C
    nullptr,            //0x1D
    nullptr,            //0x1E
    nullptr,            //0x1F
    nullptr,            //0x20
    nullptr,            //0x21
    nullptr,            //0x22
    nullptr,            //0x23
    nullptr,            //0x24
    nullptr,            //0x25
    nullptr,            //0x26
    nullptr,            //0x27
    nullptr,            //0x28
    nullptr,            //0x29
    nullptr,            //0x2A
    nullptr,            //0x2B
    nullptr,            //0x2C
    nullptr,            //0x2D
    nullptr,            //0x2E
    nullptr,            //0x2F
    nullptr,            //0x30
    nullptr,            //0x31
    nullptr,            //0x32
    nullptr,            //0x33
    nullptr,            //0x34
    nullptr,            //0x35
    nullptr,            //0x36
    nullptr,            //0x37
    nullptr,            //0x38
    nullptr,            //0x39
    nullptr,            //0x3A
    nullptr,            //0x3B
    nullptr,            //0x3C
    nullptr,            //0x3D
    nullptr,            //0x3E
    nullptr,            //0x3F
    nullptr,            //0x40
    nullptr,            //0x41
    nullptr,            //0x42
    nullptr,            //0x43
    nullptr,            //0x44
    nullptr,            //0x45
    nullptr,            //0x46
    nullptr,            //0x47
    nullptr,            //0x48
    nullptr,            //0x49
    nullptr,            //0x4A
    nullptr,            //0x4B
    nullptr,            //0x4C
    nullptr,            //0x4D
    nullptr,            //0x4E
    nullptr,            //0x4F
    nullptr,            //0x50
    nullptr,            //0x51
    nullptr,            //0x52
    nullptr,            //0x53
    nullptr,            //0x54
    nullptr,            //0x55
    nullptr,            //0x56
    nullptr,            //0x57
    nullptr,            //0x58
    nullptr,            //0x59
    nullptr,            //0x5A
    nullptr,            //0x5B
    nullptr,            //0x5C
    nullptr,            //0x5D
    nullptr,            //0x5E
    nullptr,            //0x5F
    nullptr,            //0x60
    nullptr,            //0x61
    nullptr,            //0x62
    nullptr,            //0x63
    nullptr,            //0x64
    nullptr,            //0x65
    nullptr,            //0x66
    nullptr,            //0x67
    nullptr,            //0x68
    nullptr,            //0x69
    nullptr,            //0x6A
    nullptr,            //0x6B
    nullptr,            //0x6C
    nullptr,            //0x6D
    nullptr,            //0x6E
    nullptr,            //0x6F
    nullptr,            //0x70
    nullptr,            //0x71
    nullptr,            //0x72
    nullptr,            //0x73
    nullptr,            //0x74
    nullptr,            //0x75
    nullptr,            //0x76
    nullptr,            //0x77
    nullptr,            //0x78
    nullptr,            //0x79
    nullptr,            //0x7A
    nullptr,            //0x7B
    nullptr,            //0x7C
    nullptr,            //0x7D
    nullptr,            //0x7E
    nullptr,            //0x7F
    nullptr,            //0x80
    nullptr,            //0x81
    nullptr,            //0x82
    nullptr,            //0x83
    nullptr,            //0x84
    nullptr,            //0x85
    nullptr,            //0x86
    nullptr,            //0x87
    nullptr,            //0x88
    nullptr,            //0x89
    nullptr,            //0x8A
    nullptr,            //0x8B
    nullptr,            //0x8C
    nullptr,            //0x8D
    nullptr,            //0x8E
    nullptr,            //0x8F
    nullptr,            //0x90
    nullptr,            //0x91
    nullptr,            //0x92
    nullptr,            //0x93
    nullptr,            //0x94
    nullptr,            //0x95
    nullptr,            //0x96
    nullptr,            //0x97
    nullptr,            //0x98
    nullptr,            //0x99
    nullptr,            //0x9A
    nullptr,            //0x9B
    nullptr,            //0x9C
    nullptr,            //0x9D
    nullptr,            //0x9E
    nullptr,            //0x9F
    nullptr,            //0xA0
    nullptr,            //0xA1
    nullptr,            //0xA2
    nullptr,            //0xA3
    nullptr,            //0xA4
    nullptr,            //0xA5
    nullptr,            //0xA6
    nullptr,            //0xA7
    nullptr,            //0xA8
    nullptr,            //0xA9
    nullptr,            //0xAA
    nullptr,            //0xAB
    nullptr,            //0xAC
    nullptr,            //0xAD
    nullptr,            //0xAE
    nullptr,            //0xAF
    nullptr,            //0xB0
    nullptr,            //0xB1
    nullptr,            //0xB2
    nullptr,            //0xB3
    nullptr,            //0xB4
    nullptr,            //0xB5
    nullptr,            //0xB6
    nullptr,            //0xB7
    nullptr,            //0xB8
    nullptr,            //0xB9
    nullptr,            //0xBA
    nullptr,            //0xBB
    nullptr,            //0xBC
    nullptr,            //0xBD
    nullptr,            //0xBE
    nullptr,            //0xBF
    nullptr,            //0xC0
    nullptr,            //0xC1
    nullptr,            //0xC2
    nullptr,            //0xC3
    nullptr,            //0xC4
    nullptr,            //0xC5
    nullptr,            //0xC6
    nullptr,            //0xC7
    nullptr,            //0xC8
    nullptr,            //0xC9
    nullptr,            //0xCA
    nullptr,            //0xCB
    nullptr,            //0xCC
    nullptr,            //0xCD
    nullptr,            //0xCE
    nullptr,            //0xCF
    nullptr,            //0xD0
    nullptr,            //0xD1
    nullptr,            //0xD2
    nullptr,            //0xD3
    nullptr,            //0xD4
    nullptr,            //0xD5
    nullptr,            //0xD6
    nullptr,            //0xD7
    nullptr,            //0xD8
    nullptr,            //0xD9
    nullptr,            //0xDA
    nullptr,            //0xDB
    nullptr,            //0xDC
    nullptr,            //0xDD
    nullptr,            //0xDE
    nullptr,            //0xDF
    nullptr,            //0xE0
    nullptr,            //0xE1
    nullptr,            //0xE2
    nullptr,            //0xE3
    nullptr,            //0xE4
    nullptr,            //0xE5
    nullptr,            //0xE6
    nullptr,            //0xE7
    nullptr,            //0xE8
    nullptr,            //0xE9
    nullptr,            //0xEA
    nullptr,            //0xEB
    nullptr,            //0xEC
    nullptr,            //0xED
    nullptr,            //0xEE
    nullptr,            //0xEF
    nullptr,            //0xF0
    nullptr,            //0xF1
    nullptr,            //0xF2
    nullptr,            //0xF3
    nullptr,            //0xF4
    nullptr,            //0xF5
    nullptr,            //0xF6
    nullptr,            //0xF7
    nullptr,            //0xF8
    nullptr,            //0xF9
    nullptr,            //0xFA
    nullptr,            //0xFB
    nullptr,            //0xFC
    nullptr,            //0xFD
    nullptr,            //0xFE
    nullptr,            //0xFF
};
