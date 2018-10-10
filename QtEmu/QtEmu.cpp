#include "QtEmu.h"
#include "ui_QtEmu.h"
#include <QLibrary>
#include "QDisplay.h"

QMap<QString, QtEmu::SupportedRomType> QtEmu::s_RomTypeMap =
{
    { "gb", SupportedRomType::gb}
};

QtEmu::QtEmu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtEmu),
    m_CoreLibrary()
{
    ui->setupUi(this);
    m_Core = nullptr;
    m_CoreExecutingThread = nullptr;
    m_VideoUpdateThread = nullptr;
    m_StopCore = false;
    QObject::connect(this, &QtEmu::FrameReady, ui->display, &QDisplay::RenderFrame);
}

QtEmu::~QtEmu()
{
    delete ui;
    delete m_Core;
    if (m_CoreExecutingThread != nullptr)
    {
        m_CoreExecutingThread->exit();
        m_CoreExecutingThread->wait();
        delete m_CoreExecutingThread;
    }
    if (m_VideoUpdateThread != nullptr)
    {
        m_VideoUpdateThread->exit();
        m_VideoUpdateThread->wait();
        delete m_VideoUpdateThread;
    }
}

void QtEmu::on_actionLoad_ROM_triggered()
{
    //TODO: display file selection
    QString biosFilePath = "Bios.gb";
    QString romFilePath = "Tetris.gb";
    StopEmulatorCore();
    try
    {
        switch (s_RomTypeMap[QFileInfo(romFilePath).suffix()])
        {
        case SupportedRomType::gb:
            m_CoreLibrary.setFileName("GBCore");
            break;
        }
        m_Core = reinterpret_cast<IEmulatorCore*(*)()>(m_CoreLibrary.resolve("GetCore"))();
        int screenWidth, screenHeight;
        m_Core->GetScreenSize(screenWidth, screenHeight);
        //set screen size
        ui->display->setMinimumSize(screenWidth, screenHeight);
        //fix window size
        adjustSize();
        //initialize emulator core
        if (m_Core->Initialize(biosFilePath, romFilePath))
        {
            //start the emulator main loop in a separate thread
            StartEmulatorCore();
        }
        else
        {
            //TODO: handle initialization error
        }
    }
    catch (QException)
    {
        //TODO: proper error handling
    }
}

void QtEmu::StopEmulatorCore()
{
    if (m_Core != nullptr)
    {
        m_StopCore = true;
        if (m_CoreExecutingThread != nullptr && m_CoreExecutingThread->isRunning())
        {
            m_CoreExecutingThread->wait();
            delete m_CoreExecutingThread;
        }
        if (m_VideoUpdateThread != nullptr && m_VideoUpdateThread->isRunning())
        {
            m_VideoUpdateThread->wait();
            delete m_VideoUpdateThread;
        }
        delete m_Core;
    }
    if (m_CoreLibrary.isLoaded())
    {
        m_CoreLibrary.unload();
    }
}

void QtEmu::StartEmulatorCore()
{
    if (m_Core != nullptr)
    {
        m_CoreExecutingThread = QThread::create([this] { EmulatorLoop(); });
        m_VideoUpdateThread = QThread::create([this] { VideoLoop(); });
        m_CoreExecutingThread->start(QThread::HighestPriority);
        m_VideoUpdateThread->start(QThread::HighestPriority);
    }
}

void QtEmu::EmulatorLoop()
{
    while(!m_Core->HasError() && !m_StopCore)
    {
        m_Core->Exec();
    }
}

void QtEmu::VideoLoop()
{
    while(!m_Core->HasError() && !m_StopCore)
    {
        //TODO: process frame data
    }
}
