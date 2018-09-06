#ifndef GBMEMORY_H
#define GBMEMORY_H

#include <QtCore>

#define BIOS_SIZE 0x0100
#define BIOS_MD5 "32fbbd84168d3482956eb3c5051637f5"
#define ZRAM_SIZE 0x0080
#define MEMORY_SIZE 0xFFFF
#define BIOS_MAPPED_ADDRESS 0xFF50
#define ZRAM_START_ADDRESS 0xFF80

class GBMemory
{
private:
    QByteArray m_Bios;
    bool m_IsBiosMapped;
    QByteArray m_ZRAM;
public:
    GBMemory();
    void Reset();
    bool LoadBios(QString biosFilePath);
    quint8 ReadByte(quint16 address);
    quint16 ReadWord(quint16 address);
    void WriteByte(quint16 address, quint8 value);
    void WriteWord(quint16 address, quint16 value);
};

#endif // GBMEMORY_H
