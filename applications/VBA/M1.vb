Option Explicit

Dim ports() As String
Dim lBoundVar As Long
Dim uBoundVar As Long
Public workingPort As String
Dim numPort As Long
Const maxPort = 19
Public work As Boolean
Dim rw As Long
Dim cl As Long
Dim portExist As Boolean

Dim intPortID As Integer ' Ex. 1, 2, 3, 4 for COM1 - COM4
Dim lngStatus As Long
Dim strError  As String
Dim strData   As String


Sub scanPorts()
    Dim prt As String
    Dim i As Long
    work = False
    portExist = False
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
    Call saveNamePort
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

'------------------------------------------------------
'ddPorts (элемент: dropDown, атрибут: getItemCount), 2007
Private Sub ddCount(control As IRibbonControl, ByRef count)
    Call scanPorts
    count = uBoundVar + 1
End Sub

'ddPorts (элемент: dropDown, атрибут: getItemLabel), 2007
Private Sub ddLabel(control As IRibbonControl, index As Integer, ByRef label)
    label = ports(index)
End Sub

'ddPorts (элемент: dropDown, атрибут: onAction), 2007
Private Sub ddClicked(control As IRibbonControl, selectedId As String, selectedIndex As Integer)
    If uBoundVar >= 0 Then
        workingPort = ports(selectedIndex)
        Call saveNamePort
    End If
End Sub

'ddPorts (элемент: dropDown, атрибут: getSelectedItemIndex), 2007
Private Sub ddSelect(control As IRibbonControl, ByRef index)
    Call readNamePort
    index = numPort
End Sub
'-----------------------------------------------------------

'btnScan (элемент: button, атрибут: onAction), 2007
Private Sub scanerPortsBtn(control As IRibbonControl)
    'Call scanPort
    Call ShipRegion_KeyPress
End Sub

'btnStart (элемент: button, атрибут: onAction), 2007
Private Sub StartReadingBtn(control As IRibbonControl)
    Call startRequest
End Sub


'btnStop (элемент: button, атрибут: onAction), 2007
Private Sub StopReadingBtn(control As IRibbonControl)
    Call stopRequest
End Sub

Sub pressEnter()
    If work Then
        Call callMethods
    End If
    cl = ActiveCell.Column
    rw = ActiveCell.Row
    rw = rw + 1
    If work And (rw = 10 Or rw = 13 Or rw = 16) Then rw = rw + 1
    Cells(rw, cl).Activate
    'Application.SendKeys "~", True
End Sub

Sub callMethods()
    Call openPort
    Call requestData
    Call closePort
End Sub

Sub startStop()
    If work Then
        Call stopRequest
    Else
        Call startRequest
    End If
End Sub


Sub startRequest()
    If work <> True Then
        work = True
        Call signalWork
    End If
End Sub


Sub stopRequest()
    If work Then
        work = False
        Call signalWork
    End If
End Sub


Sub setData()
    If work Then
        Range("B11").Value = 94
        Range("B17").Value = 142
        Range("B25").Value = 236
        Range("C1").Activate
    End If
End Sub
