#include "GBBus.h"
#include "GBApu_FrameSequencer.h"
#include "GBApu_SweepSquareChannel.h"
#include "GBApu_FrequencySweepModule.h"
#include "GBApu_SquareWaveModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_SweepSquareChannel::GBApu_SweepSquareChannel(quint8& apuStatus) :
	GBApu_ChannelBase(AUDIO_REG_ADDRESS_OFFSET, apuStatus)
{
    m_FrequencySweeper = new GBApu_FrequencySweepModule(AUDIO_CHANNEL1_ENABLE_MASK, m_ApuStatus, m_Registers);
	m_SquareWave = new GBApu_SquareWaveModule(m_Registers);
    m_LengthCounter = new GBApu_LengthCounterModule(0x3F, AUDIO_CHANNEL1_ENABLE_MASK, m_ApuStatus, m_Registers);
    m_VolumeEnvelope = new GBApu_VolumeEnvelopeModule(m_Registers);
}

GBApu_SweepSquareChannel::~GBApu_SweepSquareChannel()
{
    delete m_FrequencySweeper;
	delete m_SquareWave;
	delete m_LengthCounter;
    delete m_VolumeEnvelope;
}

void GBApu_SweepSquareChannel::ReadRegister(GBBus *bus)
{
	switch (bus->GetAddress() - c_StartRegAddress)
	{
		case AUDIO_CHANNEL_NRX0_ADDRESS:
			bus->SetData(m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] | 0x80);
			break;
		case AUDIO_CHANNEL_NRX1_ADDRESS:
			bus->SetData(m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] | 0x3F);
			break;
		case AUDIO_CHANNEL_NRX2_ADDRESS:
			bus->SetData(m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS]);
			break;
		case AUDIO_CHANNEL_NRX3_ADDRESS:
			bus->SetData(0xFF);
			break;
		case AUDIO_CHANNEL_NRX4_ADDRESS:
			bus->SetData(m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] | 0xBF);
			break;
		default:
			return;
	}
	bus->ReadReqAck();
}

void GBApu_SweepSquareChannel::WriteRegister(GBBus *bus)
{
	switch (bus->GetAddress() - c_StartRegAddress)
	{
		case AUDIO_CHANNEL_NRX0_ADDRESS:
			m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] = bus->GetData() & 0x7F;
			break;
		case AUDIO_CHANNEL_NRX1_ADDRESS:
			m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] = bus->GetData();
			break;
		case AUDIO_CHANNEL_NRX2_ADDRESS:
			m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] = bus->GetData();
			break;
		case AUDIO_CHANNEL_NRX3_ADDRESS:
			m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] = bus->GetData();
			break;
		case AUDIO_CHANNEL_NRX4_ADDRESS:
			m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] = bus->GetData() & 0xC7;
			Trigger();
			break;
		default:
			return;
	}
	bus->WriteReqAck();
}

void GBApu_SweepSquareChannel::Reset()
{
	GBApu_ChannelBase::Reset();
    m_FrequencySweeper->Reset();
	m_SquareWave->Reset();
	m_LengthCounter->Reset();
    m_VolumeEnvelope->Reset();
}

void GBApu_SweepSquareChannel::Trigger()
{
	if ((m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x80) != 0)
	{
        m_FrequencySweeper->Trigger();
		m_SquareWave->Trigger();
		m_LengthCounter->Trigger();
        m_VolumeEnvelope->Trigger();
	}
}

void GBApu_SweepSquareChannel::Tick(GBApu_FrameSequencer *sequencer)
{
	m_Sample = 0;
    if ((m_ApuStatus & AUDIO_CHANNEL1_ENABLE_MASK) != 0)
    {
        m_FrequencySweeper->Tick(sequencer->IsFrequencySweepTick(), &m_Sample);
        m_SquareWave->Tick(true, &m_Sample);
        m_LengthCounter->Tick(sequencer->IsLengthCounterTick(), &m_Sample);
        m_VolumeEnvelope->Tick(sequencer->IsVolumeEnvelopeTick(), &m_Sample);
    }
}
