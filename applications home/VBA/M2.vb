Option Explicit

Private BarDCB As DCB
Private CtimeOut As COMMTIMEOUTS

Type COMMTIMEOUTS
        ReadIntervalTimeout As Long
        ReadTotalTimeoutMultiplier As Long
        ReadTotalTimeoutConstant As Long
        WriteTotalTimeoutMultiplier As Long
        WriteTotalTimeoutConstant As Long
End Type
Type DCB
        DCBlength As Long
        BaudRate As Long
        fBitFields As Long
        wReserved As Integer
        XonLim As Integer
        XoffLim As Integer
        ByteSize As Byte
        parity As Byte
        StopBits As Byte
        XonChar As Byte
        XoffChar As Byte
        ErrorChar As Byte
        EofChar As Byte
        EvtChar As Byte
        wReserved1 As Integer
End Type

Type OVERLAPPED
        Internal As Long
        InternalHigh As Long
        offset As Long
        OffsetHigh As Long
        hEvent As Long
End Type

Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, ByVal lpSecurityAttributes As Long, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Declare Function PurgeComm Lib "kernel32" (ByVal hFile As Long, ByVal dwFlags As Long) As Long
Declare Function SetCommTimeouts Lib "kernel32" (ByVal hFile As Long, lpCommTimeouts As COMMTIMEOUTS) As Long
Declare Function SetCommState Lib "kernel32" (ByVal hCommDev As Long, lpDCB As DCB) As Long
Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Declare Function GetLastError Lib "kernel32" () As Long
 
Public Function initCOM(ByVal COMn As String, ByVal baud As Long, ByVal bits As Integer, ByVal parity As Integer, ByVal stops As Integer) As String

    Dim retval As Long
 
    initCOM = "yes"
    Dim ComNum As String
    ComNum = CreateFile(COMn, &HC0000000, 0, 0&, &H3, 0, 0)
    If ComNum = -1 Then
        initCOM = "no"
        Exit Function
      Else
         retval = PurgeComm(ComNum, 0)
    End If
 
    
    BarDCB.DCBlength = 28
    BarDCB.BaudRate = baud
    BarDCB.fBitFields = &H83
    BarDCB.wReserved = 0
    BarDCB.XonLim = 128
    BarDCB.XoffLim = 64
    BarDCB.ByteSize = bits
    BarDCB.parity = parity
    
    If stops >= 2 Then BarDCB.StopBits = 2 Else BarDCB.StopBits = 0
    BarDCB.XonChar = 17
    BarDCB.XoffChar = 19
    BarDCB.ErrorChar = 35
    BarDCB.EofChar = 26
    BarDCB.EvtChar = 0
    BarDCB.wReserved1 = 0
    retval = SetCommState(ComNum, BarDCB)
    If retval = -1 Then
        retval = GetLastError()
        initCOM = "ErrorZZZ: " + retval
        retval = CloseHandle(ComNum)
        Exit Function
    End If
    
    CtimeOut.ReadIntervalTimeout = 1
    CtimeOut.ReadTotalTimeoutConstant = 1
    CtimeOut.ReadTotalTimeoutMultiplier = 1
    CtimeOut.WriteTotalTimeoutConstant = 20
    CtimeOut.WriteTotalTimeoutMultiplier = 5
    retval = SetCommTimeouts(ComNum, CtimeOut)
    If retval = -1 Then
        retval = GetLastError()
        initCOM = "Error: " & retval
    End If
    retval = CloseHandle(ComNum)
End Function

