#ifndef IGBCPUSTATECONTEXT_H
#define IGBCPUSTATECONTEXT_H

#include <QtGlobal>
#include "GBInstruction.h"

class IGBCpuState;

class IGBCpuStateContext
{
public:
    IGBCpuStateContext();
    virtual ~IGBCpuStateContext();
    virtual void SetState(IGBCpuState* newState) = 0;
    virtual bool GetImeFlag() = 0;
    virtual quint16 GetPcAndIncrement() = 0;
    virtual GBInstruction* GetInstructionTable() = 0;
    virtual GBInstruction* GetCBInstructionTable() = 0;
};

#endif // IGBCPUSTATECONTEXT_H
