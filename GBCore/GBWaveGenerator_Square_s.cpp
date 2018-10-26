#include "GBWaveGenerator_Square.h"

quint8 GBWaveGenerator_Square::s_DutyCycles[DUTY_CYCLES_NUM][DUTY_CYCLES_SAMPLES_NUM] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F },
    { 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F },
    { 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F },
    { 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00 },
};
