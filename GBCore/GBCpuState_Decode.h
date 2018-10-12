#ifndef GBCPUSTATE_DECODE_H
#define GBCPUSTATE_DECODE_H

#include "IGBCpuState.h"

class GBCpuState_Decode : public IGBCpuState
{
private:
    bool m_IsCB;
public:
    GBCpuState_Decode(IGBCpuStateContext* context, bool isCB);
    void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::Decode; }
};

#endif // GBCPUSTATE_DECODE_H
