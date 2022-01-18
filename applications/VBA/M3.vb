Option Explicit

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

' module for receive data from multimetr
Sub openPort()
    Dim port As String
    port = Range("AA1").Value
    Open port & ":115200,N,8,1,X" For Binary Access Read Write As #1
    'Put #1, , "conf:auto 1" & Chr(13)
    'Put #1, , "conf:volt:dc 2" & Chr(13)
End Sub

Sub closePort()
    Close #1
End Sub

Sub requestData()
    Dim Cmnd As String
    Dim answer As String
    Dim char As Variant
    Dim cnt As Integer
    Dim num As Double
    Dim regEx1 As New RegExp
    Dim regEx2 As New RegExp
    Dim patt1 As String
    Dim patt2 As String
    Dim cl As Long
    
    
    patt1 = ",.*"
    patt2 = "\."
    answer = ""
    
    
    While (answer = "")
        Cmnd = "read?" & Chr(13)        'Message assembled to be sent to device on serial port
        cnt = 0
        Put #1, , Cmnd                'Sends assembled message
        'Sleep 40
        'Get #1, , Cmnd
        char = Input(1, #1)
        
        While (char <> Chr(13)) ' And cnt < 40)      'loop until [CR]
        answer = answer + char   'add, if printable char
            'If (char > Chr(31)) Then
                
            'Else
                ' Do what ever you like
            'End If
            'Get #1, , Cmnd        'get the next character
            char = Input(1, #1)          'get first character
            cnt = cnt + 1
        Wend
    Wend
    'answer = "-1.0E-6,0.0E0"
    
    With regEx1
        .Pattern = patt1
    End With
    
    
    If answer <> "" Then
        'ActiveCell.offset(0, -1).Value = answer
        Cmnd = regEx1.Replace(answer, "")
        'Cmnd = Replace(answer, ",.*", "")
        With regEx2
            .Pattern = patt2
        End With
        answer = regEx2.Replace(Cmnd, ",")
        'Cmnd = Replace(answer, ".", ",")
        num = CDbl(answer)
        cl = ActiveCell.Row
        While (num < 100)
            num = num * 10
        Wend
        
        Select Case cl
        Case 2, 3, 4
            While (num > 10)
                num = num / 10
            Wend
        Case 7, 5, 6
            While (num > 50)
                num = num / 10
            Wend
        Case Else
            While (num > 100)
                num = num / 10
            Wend
        End Select
        num = Round(num, 2)
                    
        If ActiveCell.Column = 3 And ActiveCell.Row > 1 And ActiveCell.Row < 27 Then
            ActiveCell.Value = num
        End If
    End If
    
End Sub


Sub signalWork()
    If work Then
        Range("A32:K32").Interior.Color = RGB(150, 235, 140)
    Else
        Range("A32:K32").Interior.Color = xlNone
    End If
End Sub
