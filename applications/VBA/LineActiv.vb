Option Explicit

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Sub ReadCommPC()
    Dim COMfile As Integer
    Dim COMfile2 As Integer
    Dim COMstring As Variant
    Dim COMstring2 As Variant
    Dim COMport As String
    Dim baudrate As Long
    Dim record_cat As Variant
    Dim record As String * 1
    Dim cnt As Integer
    Dim ComP2 As String

    COMport = "COM6"   'Enter the COM port here.
    ComP2 = "COM9"
    baudrate = 9600       'Enter the baud rate here.
    Dim Cmnd As String
    Cmnd = "hlo" & Chr(13)
    'Open COM port with baud rate, no parity, 8 data bits and 1 stop bit
    COMfile = FreeFile
    COMfile2 = FreeFile(2)
    COMstring = COMport & ":" & baudrate & ",N,8,1"
    COMstring2 = ComP2 & ":" & baudrate & ",N,8,1"
    Close #COMfile
    Close #COMfile2
    Open COMstring2 For Binary Access Read Write As #COMfile2
    Open COMstring For Binary Access Read Write As #COMfile
    Sleep 1700  ' for waiting opening port
    cnt = 0
    Do
        record = ""
        record_cat = ""
        Put #COMfile, , Cmnd
        Put #COMfile2, , Cmnd
        Sleep 2
        cnt = cnt + 1
        If cnt > 3 Then
            Exit Do
        End If
        DoEvents
        Do
            Sleep 2
            Get #COMfile, , record      'data is read in 1 character at a time
            'Debug.Print record & " " & Asc(record)
            If record = Chr(13) Then
                Exit Do
            End If
            record_cat = record_cat & record
        Loop
        Debug.Print record_cat
        record_cat = ""
        Do
			Sleep 2
            Get #COMfile2, , record      'data is read in 1 character at a time
            If record = Chr(13) Then
                Exit Do
            End If
            record_cat = record_cat & record
        Loop
        Debug.Print record_cat
        record_cat = ""
    Loop
    Close #COMfile
    Close #COMfile2
End Sub

