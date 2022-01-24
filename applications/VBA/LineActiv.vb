Option Explicit On

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Const maxPort = 19
Dim ports() As String
Dim lBoundVar As Long
Dim uBoundVar As Long
Dim portExist As Boolean
Public workingPort As String
Dim numPort As Long
Dim passControl As String           ' password for check port control
Dim portControl As String           ' portControl in range AA2
Dim portMultimetr As String         ' portMultimetr in range AA1
Dim work As Boolean
Dim checkControl As Boolean         ' if port of control rotation is correct
Dim checkMultimetr As Boolean       ' if port of multimetr is correct



' press button start check coil
Sub startCoil(control As IRibbonControl)
    Call setParameter()
    MsgBox("start coil")
End Sub


' press button start linearity
Sub startLine(control As IRibbonControl)

    Call setParameter()

    If verifyPort() Then

    Else

    End If

End Sub


' set parameters
Sub setParameter()
    work = True
    Call signalWork()
    portMultimetr = Range("AA1").Value
    portControl = Range("AA2").Value
    passControl = "qpzm10qqf"

End Sub

' verify port
Function verifyPort() As Boolean
    verifyPort = False
    If portMultimetr <> "" Then
        Call openPort1
        Sleep(100)
        MsgBox("open")
        Dim testData As Double
        testData = dataMultimetr
        If testData > 0 Then
            verifyPort = True
        End If
    Else
        Exit Function
    End If

    If portControl <> "" Then
        Call openPort2
    Else
        'Exit Function
    End If


End Function

Sub scanPorts()

    Dim prt As String
    Dim i As Long

    Dim portsPro(maxPort) As String
    Dim numPorts As Long
    numPorts = -1


    For i = 0 To maxPort
        prt = initCOM("COM" & i, 115200, 8, 0, 1)
        If prt = "yes" Then
            portsPro(i) = "COM" & i
            numPorts = numPorts + 1
        Else
            portsPro(i) = "no"
        End If
    Next i

    lBoundVar = 0
    uBoundVar = numPorts
    ReDim ports(lBoundVar To uBoundVar)
    numPorts = 0

    For i = 0 To maxPort
        If portsPro(i) <> "no" Then
            ports(numPorts) = portsPro(i)
            numPorts = numPorts + 1
            If Range("AA1") = portsPro(i) Then portExist = True
        End If
    Next i
    workingPort = ports(0)
    If Range("AA1") <> "" And portExist Then
        workingPort = Range("AA1").Value
    Else
        Range("AA1") = workingPort
    End If
    Call saveNamePort()

    MsgBox("workingPort " & workingPort)

End Sub

Sub readNamePort()
    workingPort = Range("AA1")
    Dim i As Long
    numPort = 0
    For i = 0 To uBoundVar
        If ports(i) = workingPort Then
            numPort = i
        End If
    Next i
    If workingPort = "" Then workingPort = ports(0)
End Sub

'save name of port
Sub saveNamePort()
    Range("AA1").Font.Color = vbWhite
    Range("AA1") = workingPort
End Sub


Sub signalWork()
    If work Then
        Range("A32:B32").Interior.Color = RGB(255, 215, 191)
    Else
        Range("A32:B32").Interior.Color = xlNone
    End If
End Sub
