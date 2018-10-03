#include "GBVideo.h"
#include "GBBus.h"
#include "GBUtils.h"

GBVideo::GBVideo() :
    m_Registers(VIDEO_REG_SIZE, 0),
    m_VideoRAM(VIDEO_RAM_SIZE, 0)
{
    Reset();
}

void GBVideo::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    m_VideoRAM.fill(0);
    m_Registers.fill(0);
    m_Registers[*VideoRegister::LCDC] = static_cast<char>(0x91);
    m_Registers[*VideoRegister::STAT] = static_cast<char>(0x02);
    m_Registers[*VideoRegister::SCY] = static_cast<char>(0x00);
    m_Registers[*VideoRegister::BGP] = static_cast<char>(0xFC);
}

quint16 GBVideo::GetModeCycles()
{
    switch (GetVideoMode())
    {
    case VideoMode::HBLANK:
        return 204;
    case VideoMode::VBLANK:
        return 4560;
    case VideoMode::SCANLINE1:
        return 80;
    case VideoMode::SCANLINE2:
        return 172;
    }
}

void GBVideo::Tick(GBBus* bus)
{
    //update video mode
    if (++m_Cycles > GetModeCycles())
    {
        switch (GetVideoMode())
        {
        case VideoMode::SCANLINE1:
            SetVideoMode(VideoMode::SCANLINE2);
            break;
        case VideoMode::SCANLINE2:
            SetVideoMode(VideoMode::VBLANK);
            break;
        case VideoMode::HBLANK:
            IncreaseYLineCount();
            SetVideoMode(static_cast<quint8>(m_Registers[*VideoRegister::LY]) < VIDEO_MAX_HBLANK ? VideoMode::SCANLINE1 : VideoMode::VBLANK);
            break;
        case VideoMode::VBLANK:
            if ((m_Cycles % VIDEO_LINE_CYCLE_COUNT) == 0)
            {
                IncreaseYLineCount();
            }
            SetVideoMode(VideoMode::SCANLINE2);
            break;
        }
        m_Cycles = 0;
    }
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()) && GetVideoMode() != VideoMode::SCANLINE2)
        {
            bus->SetData(static_cast<quint8>(m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET]));
            bus->ReadReqAck();
        }
        if (IsAddressInVideoReg(bus->GetAddress()))
        {
            switch (static_cast<VideoRegister>(bus->GetAddress() - VIDEO_REG_ADDRESS_OFFSET))
            {
            case VideoRegister::LCDC:
                bus->SetData(static_cast<quint8>(m_Registers[*VideoRegister::LCDC]));
                bus->ReadReqAck();
                break;
            case VideoRegister::STAT:
                bus->SetData(static_cast<quint8>(m_Registers[*VideoRegister::STAT]));
                bus->ReadReqAck();
                break;
            case VideoRegister::SCY:
                bus->SetData(static_cast<quint8>(m_Registers[*VideoRegister::SCY]));
                bus->ReadReqAck();
                break;
            case VideoRegister::LY:
                bus->SetData(static_cast<quint8>(m_Registers[*VideoRegister::LY]));
                bus->ReadReqAck();
                break;
            case VideoRegister::BGP:
                bus->SetData(static_cast<quint8>(m_Registers[*VideoRegister::BGP]));
                bus->ReadReqAck();
                break;
            }
        }
    }
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()) && GetVideoMode() != VideoMode::SCANLINE2)
        {
            m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET] = static_cast<char>(bus->GetData());
            bus->WriteReqAck();
        }
        if (IsAddressInVideoReg(bus->GetAddress()))
        {
            switch (static_cast<VideoRegister>(bus->GetAddress() - VIDEO_REG_ADDRESS_OFFSET))
            {
            case VideoRegister::LCDC:
                m_Registers[*VideoRegister::LCDC] = static_cast<char>(bus->GetData());
                //controllare se il display va disabilitato!!
                //quando disabilitato mode = VBLANK, quando abilito mode = SCANLINE1
                bus->WriteReqAck();
                break;
            case VideoRegister::STAT:
                m_Registers[*VideoRegister::STAT] = (m_Registers[*VideoRegister::STAT] & 0x03) | static_cast<char>(bus->GetData() & 0xFC);
                bus->WriteReqAck();
                break;
            case VideoRegister::SCY:
                m_Registers[*VideoRegister::SCY] = static_cast<char>(bus->GetData());
                bus->WriteReqAck();
                break;
            case VideoRegister::BGP:
                m_Registers[*VideoRegister::BGP] = static_cast<char>(bus->GetData());
                bus->WriteReqAck();
                break;
            case VideoRegister::LY:
                //read only registers
                bus->WriteReqAck();
                break;
            }
        }
    }
}
