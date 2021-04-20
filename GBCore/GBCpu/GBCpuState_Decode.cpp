#include "GBCpuState_Decode.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Decode::Update(GBBus* bus)
{
    if (bus->GetData() == 0xCB)
    {
        m_Context->SetState(CpuState::Fetch, true, NOP_INSTRUCTION);
    }
    else
    {
        m_Context->SetState(CpuState::Execute, m_Context->IsCBInstruction(), bus->GetData());
    }
}
