Const maxPort = 19
Dim numPorts As Long
Dim ports() As String
Dim lBoundVar As Long
Dim uBoundVar As Long
'Public workingPort As String
'Dim numPort As Long
Public portControl As String           ' portControl in range AA2
Public portMultimetr As String         ' portMultimetr in range AA1
Public work1 As Boolean
Public work2 As Boolean
Dim work As Boolean                 ' block buttons
Dim checkControl As Boolean         ' if port of control rotation is correct
Dim checkMultimetr As Boolean       ' if port of multimetr is correct
Dim sendMulty As String
Public cellPort1, cellPort2 As String   ' keeping data serials (in sub setParameter)
Dim cellLog As Long                  ' cells for loging
Dim needLog As Boolean 

