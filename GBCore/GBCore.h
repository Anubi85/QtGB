#pragma once

#include "IEmulatorCore.h"
#include "GBComponent.h"

extern "C" Q_DECL_EXPORT IEmulatorCore* GetCore();

class GBCore : public IEmulatorCore
{
private:
    GBBus* m_Bus;
    GBComponent* m_Components[COMPONENT_NUM];
    Error m_Error;
public:
    GBCore();
    ~GBCore() override;
    void Exec() override;
    bool HasError() override;
    void GetScreenSize(int& width, int& height) override;
    quint32* GetFrame() override;
    bool Initialize(QString biosFilePath, QString romFilePath) override;
};
