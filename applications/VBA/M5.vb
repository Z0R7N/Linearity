Option Explicit

' module for check linearity
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Public mainAngle As Double         ' current angle
Dim approxAngle As Double       ' approximate angle if not zero set
Public tension As Double
Public setZero As Boolean
Dim accurate As Boolean         ' if main angle is not mach to encoder angle
'Dim countTry As Long            ' for counting try of exact fit angle
Public oldTens As Double           ' for check mounting device

Sub startCheckLine()
    If Not stopBtn Then
        setZero = False
		If Not stopBtn Then Call checkAbs
        If Not stopBtn Then Call checkMount
        If Not stopBtn Then Call clearTable
        If Not stopBtn Then Call exactFit
        If Not stopBtn Then Call fillTable
        If Not stopBtn Then Call ifErrors(11)
        If Not stopBtn Then Call ifErrors(17)
        If Not stopBtn Then Call ifErrors(25)
        Call endOfPrg
    End If
End Sub


Sub clearTable()
    Dim i As Long
    For i = 2 To 25
        If i = 10 Or i = 13 Or i = 16 Then i = i + 1
        Range("C" & i) = ""
    Next i
    Range("A11") = "A"
    Range("B11") = 94
    Range("A17") = "Б"
    Range("B17") = 142
    Range("A25") = "В"
    Range("B25") = 236
End Sub

sub checkAbs()
	tension = getTension
	if tension < 48 or tenson > 58 then
		absAngle = calculateAngle(tension) + 60
	end if
end sub

' check device if mount incorrect
Sub checkMount()
    Dim tmpStr As Double
    Dim oldEnc As Double
    Dim encd As Boolean
    oldTens = tension
    If oldTens > 53 Then
        tmpStr = Val(linkPort("+", 2))
    Else
        tmpStr = Val(linkPort("-", 2))
    End If
    If stopBtn Then Return
	Call driverZero
	oldEnc = Val(linkPort("e", 2))
	tmpStr = Val(linkPort(5, 2))
	If xMinusPlusY(oldEnc, tmpStr) = 0 And Not stopBtn Then
		MsgBox ("Прибор не вращается")
		stopBtn = True
		Exit Do
	End If
    Call driverZero
End Sub

' finish program
Sub endOfPrg()
    If stopBtn Then
        Range(voltMem) = ""
    Else
        Call rotate(120)
        tension = getTension
        'Range(voltMem).Font.Color = vbWhite
        Range(voltMem) = Round(tension, 2)
    End If
End Sub

' check value in row 11, 17 and 25
Sub ifErrors(checkRow As Integer)
    Dim crctAngle As Double
    On Error GoTo Err_H
            crctAngle = Range("A" & checkRow).Value
    On Error GoTo 0
Err_H:
    If Err.Number Then
        crctAngle = 0
    End If
    If crctAngle <> 0 Then
'        dblAngle = Val(crctAngle)
        crctAngle = crctAngle + Range("B" & checkRow)
        Call rotate(crctAngle)
        tension = getTension
        Range("B" & checkRow) = crctAngle
        Call recordVolt(checkRow)
    End If
End Sub

' start fill table
Sub fillTable()
    If Not stopBtn Then
        Dim shiftRow As Integer
        Dim shiftAngle As Integer
        shiftAngle = 0
        shiftRow = 0
        Dim rowNum As Integer
        rowNum = 2
        Dim move As Double
        Dim i As Long
        For i = 1 To 21
            Call recordVolt(rowNum)
            Select Case i
                Case 10
                    shiftRow = shiftRow + 1
                Case 8, 12
                    shiftRow = shiftRow + 1
                    shiftAngle = 2
                Case 20
                    shiftAngle = 4
                Case 21
                    Exit For
            End Select
            If stopBtn Then Exit For
            rowNum = 2 + i + shiftRow
            move = 12 * i - shiftAngle
            Range("C" & rowNum).Activate
            shiftAngle = 0
            Call rotate(move)
            tension = getTension
        Next i
    End If
End Sub

' record voltage to table
Sub recordVolt(row As Integer)
    Dim num As Double
    num = Round(tension, 2)
    Range("C" & row) = num
End Sub

' exact fit angle by voltage
Sub exactFit()
    If Not stopBtn Then
        Do
            DoEvents
            If setZero Or stopBtn Then Exit Do
            tension = getTension
            approxAngle = calculateAngle(tension)
            If xMinusPlusY(tension, 2.7) > 0 Then
                Call rotate2Zero
            Else
                Call smallStep
                Call driverZero
            End If
        Loop While Not setZero Or Not stopBtn
    End If
End Sub

' small step for exact fit voltage
Sub smallStep()
    If Not stopBtn Then
        If xMinusPlusY(tension, 2.3) > 0 And xMinusPlusY(tension, 2.7) < 0 Then
            setZero = True
			absAngle = 60
        End If
        If Not setZero Then
            Dim stepAngle As Double
            stepAngle = calculateStep
            Call rotate(stepAngle)
            tension = getTension
        End If
    End If
End Sub

' calculate step angle for small step
Function calculateStep() As Integer
    calculateStep = Round((25 - tension * 10) / 3)
End Function

' if zero not set
Sub rotate2Zero()
    If Not stopBtn Then
        Do While xMinusPlusY(tension, 2.7) > 0
            DoEvents
            Call rotate(approxAngle - (approxAngle / 3), "+")
            Call driverZero
            'tension = getTension
            approxAngle = calculateAngle(tension)
        Loop
        Call driverZero
    End If
End Sub

' set zero for driver
Sub driverZero()
    If Not stopBtn Then
        Dim tmp As String
        tmp = linkPort("*", 2)
        mainAngle = 0
    End If
End Sub

' control bounderies for rotate
Function bound(ang As Double, dir As String) As boolean
	bound = true
	if dir = "-" then
		
	end if
End Function

' rotate to angle
Sub rotate(ang As Double, Optional ByVal dir As String = "-")
    If Not stopBtn Then
        Dim tmpVolt As Double
        Dim tmpEnc As Double
        Dim newEnc As Double
        tmpEnc = Val(linkPort("e", 2))
        oldTens = tension
        if not bound(ang, dir) then 
			stopBtn = True
			MsgBox("При дальнейшем вращении прибор будет сломан")
			exit sub
		end if
        Dim tmp As String
        tmp = linkPort(dir, 2)
        newEnc = Val(linkPort(CStr(ang), 2))
        tmpVolt = getTension
        If (xMinusPlusY(tmpVolt, oldTens) = 0 Or xMinusPlusY(tmpEnc, newEnc) = 0) And xMinusPlusY(Abs(mainAngle - ang), 1) > 0 And Not stopBtn Then
            Dim ans As Integer
            ans = MsgBox("Прибор не вращается. Прервать замер?", vbQuestion + vbYesNo + vbDefaultButton2, "Ошибка")
            Debug.Print "не крутит volt = " & oldTens & " " & tmpVolt
            Debug.Print "не крутит enc = " & tmpEnc & " " & newEnc
            If ans = vbYes Then
                stopBtn = True
            End If
        End If
        mainAngle = ang
        If Not getEncoder And Not stopBtn And accurate Then
            Dim answer As Integer
            answer = MsgBox("Не совпадает контрольный угол. Прервать замер?", vbQuestion + vbYesNo + vbDefaultButton2, "Ошибка")
            If answer = vbYes Then
                stopBtn = True
            Else
                accurate = False
            End If
        End If
    End If
End Sub

' check angle with encoder
Function getEncoder() As Boolean
    If Not stopBtn Then
        getEncoder = False
        Dim encNum As Double
            Sleep 70
            encNum = Val(linkPort("e", 2))
        If xMinusPlusY(mainAngle, CDbl(encNum) + 1) < 0 And xMinusPlusY(mainAngle, CDbl(encNum) - 1) > 0 Then
            getEncoder = True
            'accurate = True
        End If
    End If
End Function

' get voltage from multimetr
Function getTension() As Double
    If Not stopBtn Then
        getTension = -1
        Call logging("Function getDataMulty", "")
        Dim multy As Double
        Dim oldMulty As Double
        Dim countNum As Integer
        countNum = 0
        'oldMulty = Val(linkPort("val1?", 1))
        Dim getVolt As Double
        Dim rang As String
        Do
            DoEvents
            Sleep (50)
            multy = Val(linkPort("val1?", 1))
            Exit Do            ' <===============DEL=======================>
            If xMinusPlusY(oldMulty, multy) = 0 Then
                oldMulty = multy
                countNum = countNum + 1
                Debug.Print countNum
            End If
        Loop While countNum < 3
        Call logging("answer from multimetr", CStr(multy))
        'rang = linkPort("conf:stat:rang?", 1)
        Call logging("answer from multimetr rang", rang)
'        getVolt = Val(multy)
'        Call logging("answer from multimetr double", CStr(getVolt))
        getVolt = multy * 10
        If xMinusPlusY(getVolt, 0.00001) < 0 And Not stopBtn Then
            Dim answer As Integer
            answer = MsgBox("Проверьте подключение контактов к прибору. Продолжить замер?", vbQuestion + vbYesNo + vbDefaultButton2, "Ошибка")
            If answer = vbNo Then stopBtn = True
        End If
        If rang = "DCV: 1" Then
            'getVolt = getVolt * 100
        End If
        getTension = getVolt
    End If
End Function

' calculates the approximate angle from the voltage
Function calculateAngle(v As Double) As Double
    If Not stopBtn Then
        calculateAngle = 0.0004 * (v * v * v) - 0.0562 * (v * v) + 4.3197 * v - 3.8512
    End If
End Function

' equals numbers
Function xMinusPlusY(x As Double, Optional ByVal y As Double = 0) As Integer
    xMinusPlusY = 0
    Dim tmp As Double
    tmp = x * 100000
    Dim a As Long
    a = Round(tmp)
    tmp = y * 100000
    Dim b As Long
    b = Round(tmp)
    If a < b Then xMinusPlusY = -1
    If a > b Then xMinusPlusY = 1
End Function

