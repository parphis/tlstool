/*
  TCommunication.cpp

  purpose: a class to communicate with TLS3xx device(s) via RS232 serial port.
  
  ACIS Kft. 2006.
  All rights reserved.
*/

#include <windows.h>
#include "tcommunication.h"
#include "msgstrs.h"

using namespace std;

/*************************/
/*   private functions   */
/*************************/

/* range checks */
int TCommunication::CheckBaudRate(int iBaudRate)
{
    if (iBaudRate < 0)  return DEFAULT_BAUDRATE;
    if (iBaudRate > MAXIMUM_BAUDRATE)  return DEFAULT_BAUDRATE;
    
    return iBaudRate;
}
int TCommunication::CheckParity(int iParity)
{
    if (iParity < 0)    return DEFAULT_PARITY;
    if (iParity > 4)    return DEFAULT_PARITY;
    
    return iParity;
}
int TCommunication::CheckStopBit(int iStopBit)
{
    if (iStopBit < 0)   return DEFAULT_STOPBIT;
    if (iStopBit > 2)   return DEFAULT_STOPBIT;
    
    return iStopBit;
}
int TCommunication::CheckDataBits(int iDataBits)
{
    if (iDataBits < 0)  return DEFAULT_BYTESIZE;
    if (iDataBits > 8)  return DEFAULT_BYTESIZE;
    
    return iDataBits;
}
int TCommunication::CheckReadIntervalTimeout(int iReadIntervalTimeout)
{
    if (iReadIntervalTimeout < 0)   return MAXWORD;
    if (iReadIntervalTimeout > MAXWORD) return MAXWORD;
    
    return iReadIntervalTimeout;
}
int TCommunication::CheckReadTotalTimeoutMultiplier(int iReadTotalTimeoutMultiplier)
{
    if (iReadTotalTimeoutMultiplier < 0)   return MAXWORD;
    if (iReadTotalTimeoutMultiplier > MAXWORD) return MAXWORD;

    return iReadTotalTimeoutMultiplier;
}
int TCommunication::CheckReadTotalTimeoutConstant(int iReadTotalTimeoutConstant)
{
    if (iReadTotalTimeoutConstant < 0)   return READ_TIMEOUT;
    if (iReadTotalTimeoutConstant > MAXWORD) return READ_TIMEOUT;

    return iReadTotalTimeoutConstant;
}
int TCommunication::CheckWriteTotalTimeoutMultiplier(int iWriteTotalTimeoutMultiplier)
{
    if (iWriteTotalTimeoutMultiplier < 0)   return WRITE_TIMEOUT;
    if (iWriteTotalTimeoutMultiplier > MAXIMUM_WRITETIMEOUT) return WRITE_TIMEOUT;

    return iWriteTotalTimeoutMultiplier;
}
int TCommunication::CheckWriteTotalTimeoutConstant(int iWriteTotalTimeoutConstant)
{
    if (iWriteTotalTimeoutConstant < 0)   return WRITE_TIMEOUT;
    if (iWriteTotalTimeoutConstant > MAXIMUM_WRITETIMEOUT) return WRITE_TIMEOUT;

    return iWriteTotalTimeoutConstant;
}
int TCommunication::CheckWriterep(int iWriterep)
{
    if (iWriterep < 0)  return DEFAULT_WRITEREPETITION;
	if (iWriterep > MAXIMUM_WRITEREPETITION)    return DEFAULT_WRITEREPETITION;
	return DEFAULT_WRITEREPETITION;
}
int TCommunication::CheckReadrep(int iReadrep)
{
    if (iReadrep < 0)  return DEFAULT_READREPETITION;
	if (iReadrep > MAXIMUM_READREPETITION)    return DEFAULT_READREPETITION;
	return DEFAULT_READREPETITION;
}

/*************************/
/*   public functions    */
/*************************/

/* tcommunication constructor */
TCommunication::TCommunication(void)
{
    /* initialize all values */
    
    /* max. count of read and write operation */
    settWriterep = DEFAULT_WRITEREPETITION;
    settReadrep = DEFAULT_READREPETITION;
    
    /* init port name */
    memset(serPortName, 0, PORTNAME_SIZE);
    /************************/
    
    /* handle of the port */
    comHandle = NULL;
    /********************/
    
    /* communication settings */
    serBaudRate = DEFAULT_BAUDRATE;
    serParity = DEFAULT_PARITY;
    serStopBit = DEFAULT_STOPBIT;
    serDataBits = DEFAULT_BYTESIZE;
    /*************************/
    
    /* timeout settings */
    serReadIntervalTimeout = INTERVAL_TIMEOUT;
    serReadTotalTimeoutMultiplier = MULTIPLY_TIMEOUT;
    serReadTotalTimeoutConstant = READ_TIMEOUT;
    serWriteTotalTimeoutMultiplier = WRITE_TIMEOUT;
    serWriteTotalTimeoutConstant = WRITE_TIMEOUT;
    /************************************/
    
    /* init the write and read buffers */
    bufferToWrite = "";
    bufferToRead = "";
    /************************************/
    
    /* init the count of read/readed//write/written bytes */
    bytesToWrite = 0;
    bytesWritten = 0;
    bytesToRead = 0;
    bytesReaded = 0;
    /******************************************************/
}

/* tcommunication destructor */
TCommunication::~TCommunication(void)
{
    /* free communication handle */
    ClosePort();
    comHandle = NULL;
 
    /* freeing all resources 
    memset(serPortName, 0, PORTNAME_SIZE);
    serBaudRate = DEFAULT_BAUDRATE;
    serParity = DEFAULT_PARITY;
    serStopBit = DEFAULT_STOPBIT;
    serDataBits = DEFAULT_BYTESIZE;
    serReadIntervalTimeout = MAXWORD;
    serReadTotalTimeoutMultiplier = 0;
    serReadTotalTimeoutConstant = 0;
    serWriteTotalTimeoutMultiplier = 0;
    serWriteTotalTimeoutConstant = 0;
    memset(bufferToWrite, 0, WRITEBUFFER_SIZE);
    memset(bufferToRead, 0, READBUFFER_SIZE);
    bytesToWrite = 0;
    bytesWritten = 0;
    bytesToRead = 0;
    bytesReaded = 0;*/
}

/* it opens a serial line */
int TCommunication::OpenPort(char *iserPortName)
{
    /* save port name in the private buffer */
    strncpy(serPortName, iserPortName, PORTNAME_SIZE);
    
    /* open the serial line and create handle */
	comHandle = CreateFile(iserPortName,
                           GENERIC_READ | GENERIC_WRITE,
                           0,
                           0,
                           OPEN_EXISTING,
                           0,
                           0);

    /* the communication resource not exists */
    if (comHandle==INVALID_HANDLE_VALUE)
            return e_noserialdevice;
    else
    {
        /* it inits the dcb structure with previous values */
        if (!GetCommState(comHandle, &structDCB))
                return e_initsettings;
        /* it inits the timeout structure with previous values */
        if (!GetCommTimeouts(comHandle, &timeouts))
                return e_initsettings;

        /* set up the device needed settings */
        structDCB.BaudRate = serBaudRate;               // set the baud rate
        structDCB.ByteSize = serDataBits;               // data size, xmit, and rcv
        structDCB.Parity = serParity;                   // odd parity bit
        structDCB.StopBits =serStopBit ;                // one stop bit
        
        timeouts.ReadIntervalTimeout = serReadIntervalTimeout;
        timeouts.ReadTotalTimeoutMultiplier = serReadTotalTimeoutMultiplier;
        timeouts.ReadTotalTimeoutConstant = serReadTotalTimeoutConstant;
        timeouts.WriteTotalTimeoutMultiplier = serWriteTotalTimeoutMultiplier;
        timeouts.WriteTotalTimeoutConstant = serWriteTotalTimeoutConstant;
        
        /* it sets the program specific port properties (see constructor) */
        if (!SetCommState(comHandle, &structDCB))
                return e_updatesettings;
        else if (!SetCommTimeouts(comHandle, &timeouts))
                return e_settimeout;
        else    return e_noerror;
    }
}

/* it closes a serial port */
bool TCommunication::ClosePort(void)
{
    bool result = true;

    if (comHandle)
        result = CloseHandle(comHandle);
    
    if (!result)
            return e_closing;
	else
	{
		if (comHandle)	comHandle = NULL;
		return e_noerror;
	}
}

/* it clears the input and output buffers of the port */
bool TCommunication::ClearBuffers(void)
{
    bool result = false;
    
    if (comHandle)
    {
        result = PurgeComm(comHandle, PURGE_RXCLEAR);
        result &= PurgeComm(comHandle, PURGE_TXCLEAR);
    }
    
    if (!result)
            return e_clearing;
    else    return e_noerror;
}

/* it sets up the dcb struct of the serial port */
bool TCommunication::UpdateSerialSettings(void)
{
    bool result = false;
    
    if (comHandle)
    {
        result = SetCommState(comHandle, &structDCB);
        result &= SetCommTimeouts(comHandle, &timeouts);
    }
    
    if (!result)
            return e_updatesettings;
    else    return e_noerror;
}

/* set and get baud rate value */
void TCommunication::setBaudRate(int iserBaudRate)
{
    iserBaudRate = CheckBaudRate(iserBaudRate);
    serBaudRate = iserBaudRate;
    structDCB.BaudRate = serBaudRate;
}
int TCommunication::getBaudRate(void)
{
    return serBaudRate;
}

/* set  and get parity */
void TCommunication::setParity(int iserParity)
{
    iserParity = CheckParity(iserParity);
    serParity = iserParity;
    structDCB.Parity= serParity;
}
int TCommunication::getParity(void)
{
    return serParity;
}

/* set  and get stop bit value */
void TCommunication::setStopBit(int iserStopBit)
{
    iserStopBit = CheckStopBit(iserStopBit);
    serStopBit = iserStopBit;
    structDCB.StopBits= serStopBit;
}
int TCommunication::getStopBit(void)
{
    return serStopBit;
}

/* set  and get byte size */
void TCommunication::setDataBits(int iserDataBits)
{
    iserDataBits = CheckDataBits(iserDataBits);
    serDataBits = iserDataBits;
    structDCB.ByteSize= serDataBits;
}
int TCommunication::getDataBits(void)
{
    return serDataBits;
}
        
/* set  and get read interval timeout */
void TCommunication::setReadIntervalTimeout(int iserReadIntervalTimeout)
{
    iserReadIntervalTimeout = CheckReadIntervalTimeout(iserReadIntervalTimeout);
    serReadIntervalTimeout = iserReadIntervalTimeout;
    timeouts.ReadIntervalTimeout= serReadIntervalTimeout;
}
int TCommunication::getReadIntervalTimeout(void)
{
    return serReadIntervalTimeout;
}
        
/* set  and get read total timeout multiplier */
void TCommunication::setReadTotalTimeoutMultiplier(int iserReadTotalTimeoutMultiplier)
{
    iserReadTotalTimeoutMultiplier = CheckReadTotalTimeoutMultiplier(iserReadTotalTimeoutMultiplier);
    serReadTotalTimeoutMultiplier = iserReadTotalTimeoutMultiplier;
    timeouts.ReadTotalTimeoutMultiplier = serReadTotalTimeoutMultiplier;
}
int TCommunication::getReadTotalTimeoutMultiplier(void)
{
    return serReadTotalTimeoutMultiplier;
}
        
/* set  and get write total timeout constant;  */
void TCommunication::setReadTotalTimeoutConstant(int iserReadTotalTimeoutConstant)
{
    iserReadTotalTimeoutConstant = CheckReadTotalTimeoutConstant(iserReadTotalTimeoutConstant);
    serReadTotalTimeoutConstant = iserReadTotalTimeoutConstant;
    timeouts.ReadTotalTimeoutConstant = serReadTotalTimeoutConstant;
}
int TCommunication::getReadTotalTimeoutConstant(void)
{
    return serReadTotalTimeoutConstant;
}

/* set and get write total timeout multiplier */
void TCommunication::setWriteTotalTimeoutMultiplier(int iserWriteTotalTimeoutMultiplier)
{
    iserWriteTotalTimeoutMultiplier = CheckWriteTotalTimeoutMultiplier(iserWriteTotalTimeoutMultiplier);
    serWriteTotalTimeoutMultiplier = iserWriteTotalTimeoutMultiplier;
    timeouts.WriteTotalTimeoutMultiplier = serWriteTotalTimeoutMultiplier;
}
int TCommunication::getWriteTotalTimeoutMultiplier(void)
{
    return serWriteTotalTimeoutMultiplier;
}

/* set and get write total timeout constant */
void TCommunication::setWriteTotalTimeoutConstant(int iserWriteTotalTimeoutConstant)
{
    iserWriteTotalTimeoutConstant = CheckWriteTotalTimeoutConstant(iserWriteTotalTimeoutConstant);
    serWriteTotalTimeoutConstant = iserWriteTotalTimeoutConstant;
    timeouts.WriteTotalTimeoutConstant = serWriteTotalTimeoutConstant;
}
int TCommunication::getWriteTotalTimeoutConstant(void)
{
    return serWriteTotalTimeoutConstant;
}
        
/* set and get write buffer */
void TCommunication::setbufferToWrite(std::string ibufferToWrite)
{
    bufferToWrite = ibufferToWrite;
}
std::string TCommunication::getbufferToWrite(void)
{
    return bufferToWrite;
}

/* set and get read buffer */
void TCommunication::setbufferToRead(std::string ibufferToRead)
{
    bufferToRead = ibufferToRead;
}
std::string TCommunication::getbufferToRead(void)
{
    return bufferToRead;
}

/* set and get bytes to write */
void TCommunication::setbytesToWrite(int ibytesToWrite)
{
    if (ibytesToWrite < 0)  ibytesToWrite = 0;
    bytesToWrite = ibytesToWrite;
}
int TCommunication::getbytesToWrite(void)
{
    return bytesToWrite;
}

/* set and get bytes written */
void TCommunication::setbytesWritten(int ibytesWritten)
{
    if (ibytesWritten < 0)  ibytesWritten = 0;
    bytesWritten = ibytesWritten;
}
int TCommunication::getbytesWritten(void)
{
    return bytesWritten;
}

/* set and get bytes to read */
void TCommunication::setbytesToRead(int ibytesToRead)
{
    if (ibytesToRead < 0)  ibytesToRead = 0;
    bytesToRead = ibytesToRead;
}
int TCommunication::getbytesToRead(void)
{
    return bytesToRead;
}

/* set and get bytes readed */
void TCommunication::setbytesReaded(int ibytesReaded)
{
    if (ibytesReaded < 0)  ibytesReaded = 0;
    bytesReaded = ibytesReaded;
}
int TCommunication::getbytesReaded(void)
{
    return bytesReaded;
}

/* set and get serial port name */
void TCommunication::setPortName(char *iserPortName)
{
    strncpy(serPortName, iserPortName, PORTNAME_SIZE);
}
void TCommunication::getPortName(char *iserPortName, int count)
{
	if ((unsigned)count <= strlen(iserPortName))
        strncpy(iserPortName, serPortName, count);
}

/* set and get serial port handle */
void TCommunication::setPortHandle(HANDLE icomHandle)
{
    comHandle = icomHandle;
}
HANDLE TCommunication::getPortHandle(void)
{
    return comHandle;
}

/* set and get max. count of write */
void TCommunication::setsettableWriteRepetition(int isettWriterep)
{
    isettWriterep = CheckWriterep(isettWriterep);
    settWriterep = isettWriterep;
}
int TCommunication::getsettableWriteRepetition(void)
{
    return settWriterep;
}

/* set and get max. count of read */
void TCommunication::setsettableReadRepetition(int isettReadrep)
{
    isettReadrep = CheckReadrep(isettReadrep);
    settReadrep = isettReadrep;
}
int TCommunication::getsettableReadRepetition(void)
{
    return settReadrep;
}

/* send a string to the port */
int TCommunication::sendBuffer(char *buffer, int count)
{
    /* chack that serial port exists */
    if (!comHandle) return e_noserialdevice;
    
    /* check that count is greater than null */
    if (count <= 0) return e_writecount_msgtodev;

    bool result = true;
    int write_timeout = settWriterep;
    int read_timeout = settReadrep*100;
    DWORD readed;
    char dummy[1];
    
    /* save the buffer contain in private buffer */
    bufferToWrite = buffer;

    /* how many bytes need to write */
    bytesToWrite = count;
    
    /* empty read buffer */
    do
    {
        result &= ReadFile(comHandle, dummy, 1, &readed, NULL);
        read_timeout--;
    }
    while( (read_timeout > 0) && (readed!=0) );

    /* the empty operation was successful */
    if ( (result) || (read_timeout) )
	{
        /* write the buffer to the port; tries it with 10 times by default (see
           settWriterep) */
        do
        {
			result &= WriteFile(comHandle, buffer, bytesToWrite, &bytesWritten, NULL);
            write_timeout--;
        }
		while( (write_timeout > 0) && (result) && ((unsigned)bytesToWrite!=bytesWritten) );

    	EscapeCommFunction(comHandle,SETDTR);
    
        /* function failure */
        if (!result)
            return e_writefailed;
        else
        {
            /* write is unsuccesfull */
			if ((unsigned)bytesToWrite!=bytesWritten)
                    return e_writebytes;
            else    return e_noerror;
        }
    }
    else    return e_clearing;
}

/* read from the port */
int TCommunication::readBuffer(void)
{
    /* chack that serial port exists */
    if (!comHandle) return e_noserialdevice;

	bool result = true;

	bytesReaded = 1;
	/* empty buffer */
	global_buffer.clear();

	/* read from the port; tries with 10 times by default */
	char dummy[1];
	int i;

	dummy[0] = 0x00;

	for (int i=0; (bytesReaded) && (dummy[0]!=ENDOFANSWER_CHAR); i++)
	{
		result &= ReadFile(comHandle, dummy, 1, &bytesReaded, NULL);

		if ((unsigned)i < global_buffer.max_size())
		{
			if ( (dummy[0]!=ENDOFANSWER_CHAR) && (dummy[0]!=STARTOFANSWER_CHAR) )
				global_buffer += dummy[0];
		}
	}
    
    /* function failure */
    if (!result)
        return e_readfailed;
    else
    {
        /* read buffer is empty */
        if (bytesReaded==0)
                return e_nothingtoread;
        else
        {
            bufferToRead = global_buffer;
            return e_noerror;
        }
    }
}

/* ckecking modem status */
int TCommunication::CheckModemStatus(void)
{
    bool result = true;

    if (comHandle)
        result = GetCommModemStatus(comHandle, &serModemStatus);

    if (!result)
            return e_chekcstatus;
    else    return e_noerror;
}

/* they tell the status of the four modem signal (CTS,DSR,RING,RLSD) */
bool TCommunication::getCTSStatus(void)
{
    return MS_CTS_ON & serModemStatus;
}
bool TCommunication::getDSRStatus(void)
{
    return MS_DSR_ON & serModemStatus;
}
bool TCommunication::getRINGStatus(void)
{
    return MS_RING_ON & serModemStatus;
}
bool TCommunication::getRLSDStatus(void)
{
    return MS_RLSD_ON & serModemStatus;
}
