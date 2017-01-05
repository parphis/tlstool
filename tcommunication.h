#ifndef TCOMMUNICATIONH
#define TCOMMUNICATIONH

#include <windows.h>
#include <string>

/* module definitions */
#define PORTNAME_SIZE               6

#define DEFAULT_BAUDRATE            2400
#define MAXIMUM_BAUDRATE            57600
#define DEFAULT_PARITY              1
#define DEFAULT_STOPBIT             0
#define DEFAULT_BYTESIZE            7

#define INTERVAL_TIMEOUT            10
#define MULTIPLY_TIMEOUT            20
#define READ_TIMEOUT                100
#define WRITE_TIMEOUT               0
#define MAXIMUM_WRITETIMEOUT        10000
#define DEFAULT_WRITEREPETITION     10
#define MAXIMUM_WRITEREPETITION     500
#define DEFAULT_READREPETITION      10
#define MAXIMUM_READREPETITION      500

#define STARTOFANSWER_CHAR			0x01
#define ENDOFANSWER_CHAR            0x03

class TCommunication
{
private:
        char serPortName[PORTNAME_SIZE];
        HANDLE comHandle;
        DCB structDCB;
        int serBaudRate;
        int serParity;
        int serStopBit;
        int serDataBits;
        int serReadIntervalTimeout;
        int serReadTotalTimeoutMultiplier;
        int serReadTotalTimeoutConstant;
        int serWriteTotalTimeoutMultiplier;
        int serWriteTotalTimeoutConstant;
        std::string bufferToWrite;
        std::string bufferToRead;
        int bytesToWrite;
        DWORD bytesWritten;
        int bytesToRead;
        DWORD bytesReaded;
        OVERLAPPED ovl;
        COMMTIMEOUTS timeouts;
        int settWriterep;
        int settReadrep;
		DWORD serModemStatus;
        
        int CheckBaudRate(int iBaudRate);
        int CheckParity(int iParity);
        int CheckStopBit(int iStopBit);
        int CheckDataBits(int iDataBits);
        int CheckReadIntervalTimeout(int iReadIntervalTimeout);
        int CheckReadTotalTimeoutMultiplier(int iReadTotalTimeoutMultiplier);
        int CheckReadTotalTimeoutConstant(int iReadTotalTimeoutConstant);
        int CheckWriteTotalTimeoutMultiplier(int iWriteTotalTimeoutMultiplier);
        int CheckWriteTotalTimeoutConstant(int iWriteTotalTimeoutConstant);
        int CheckWriterep(int iWriterep);
        int CheckReadrep(int iReadrep);
        
public:
    std::string global_buffer;
    
    TCommunication(void);
    ~TCommunication(void);
    int OpenPort(char *iserPortName);
    bool ClosePort(void);
    bool ClearBuffers(void);
    bool UpdateSerialSettings(void);
    void setBaudRate(int iserBaudRate);
    int getBaudRate(void);
    void setParity(int iserParity);
    int getParity(void);
    void setStopBit(int iserStopBit);
    int getStopBit(void);
    void setDataBits(int iserDataBits);
    int getDataBits(void);
    void setReadIntervalTimeout(int iserReadIntervalTimeout);
    int getReadIntervalTimeout(void);
    void setReadTotalTimeoutMultiplier(int iserReadTotalTimeoutMultiplier);
    int getReadTotalTimeoutMultiplier(void);
    void setReadTotalTimeoutConstant(int iserReadTotalTimeoutConstant);
    int getReadTotalTimeoutConstant(void);
    void setWriteTotalTimeoutMultiplier(int iserWriteTotalTimeoutMultiplier);
    int getWriteTotalTimeoutMultiplier(void);
    void setWriteTotalTimeoutConstant(int iserWriteTotalTimeoutConstant);
    int getWriteTotalTimeoutConstant(void);
    void setbufferToWrite(std::string ibufferToWrite);
    std::string getbufferToWrite(void);
    void setbufferToRead(std::string ibufferToRead);
    std::string getbufferToRead(void);
    void setbytesToWrite(int ibytesToWrite);
    int getbytesToWrite(void);
    void setbytesWritten(int ibytesWritten);
    int getbytesWritten(void);
    void setbytesToRead(int ibytesToRead);
    int getbytesToRead(void);
    void setbytesReaded(int ibytesReaded);
    int getbytesReaded(void);
    void setPortName(char *iserPortName);
    void getPortName(char *iserPortName, int count);
    void setPortHandle(HANDLE icomHandle);
    HANDLE getPortHandle(void);
    int sendBuffer(char *buffer, int count);
    int readBuffer(void);
    void setsettableWriteRepetition(int isettWriterep);
    void setsettableReadRepetition(int isettReadrep);
    int getsettableReadRepetition(void);
    int getsettableWriteRepetition(void);
    bool getCTSStatus(void);
    bool getDSRStatus(void);
    bool getRINGStatus(void);
    bool getRLSDStatus(void);
    int CheckModemStatus(void);
};

#endif
