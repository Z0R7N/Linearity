Option Explicit

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Dim baudrate As Long
Dim COMMulty As String
Dim Cmnd As String
Dim COMFile1 As Integer
Dim COMString1 As Variant
Dim aaa As String

Sub openPort1()
    COMMulty = Range("A1").Value
    baudrate = 9600
    COMFile1 = FreeFile
    COMString1 = COMMulty & ":" & baudrate & ",N,8,1"
    Close #COMFile1
    Open COMString1 For Binary Access Read Write As #COMFile1
    Sleep 1700
End Sub

Sub closePort1()
    Close #COMFile1
End Sub

Function getDataMulty(strVar As String) As Double
    Debug.Print strVar
    Dim rec As String * 1
    Dim result As Variant
    aaa = "3333" & Chr(13)
    getDataMulty = -1
    result = ""
    strVar = strVar & Chr(13)
    Put #COMFile1, , aaa
    Sleep 2
    Do
        DoEvents
        Get #COMfile, , rec
        If rec = Chr(13) Then
            Exit Do
        End If
        result = result & rec
    Loop
End Function
