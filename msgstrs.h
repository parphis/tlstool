#ifndef MSGSTRSH
#define MSGSTRSH

enum comm_error{
    e_noerror = 0,
    e_noserialdevice,
    e_closing,
    e_clearing,
    e_updatesettings,
    e_initsettings,
    e_writefailed,
    e_writebytes,
    e_readfailed,
    e_nothingtoread,
    e_readbytes,
    e_chekcstatus,
    e_writecount_msgtodev,
	e_settimeout,
	e_checksum
    };

#endif
