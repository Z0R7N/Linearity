Attribute VB_Name = "RibbonCallbacks"	'��� �������� ������
Option Explicit	'����������� ������ ���������� ���� ���������� � �����

'customUI (�������: customUI, �������: onLoad), 2007
Private Sub ribOnLoad(ribbon As IRibbonUI)
    '�������� ���������� ���������� ������� �����: Public myRibbonObject As IRibbonUI
    Set myRibbonObject = ribbon
End Sub

'btnLinear (�������: button, �������: onAction), 2007
Private Sub startLine(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'cbManual0Angle (�������: checkBox, �������: getPressed), 2007
Private Sub cbManualAnglPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'cbManual0Angle (�������: checkBox, �������: getEnabled), 2007
Private Sub cbManualAnglsEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'cbManual0Angle (�������: checkBox, �������: onAction), 2007
Private Sub cbManualAngleAction(control As IRibbonControl, pressed As Boolean)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID & " (��������� = " & CStr(pressed) & ")"
End Sub

'bxCorrectAngle (�������: checkBox, �������: getPressed), 2007
Private Sub cbxCorAnglPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'bxCorrectAngle (�������: checkBox, �������: getEnabled), 2007
Private Sub cbCorAnglsEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'bxCorrectAngle (�������: checkBox, �������: onAction), 2007
Private Sub cbxCorrectAngleAction(control As IRibbonControl, pressed As Boolean)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID & " (��������� = " & CStr(pressed) & ")"
End Sub

'btnCorrectAngle (�������: button, �������: onAction), 2007
Private Sub correctAngle(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'cbZeroTrue (�������: checkBox, �������: getPressed), 2007
Private Sub cbxGetZerolPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'cbZeroTrue (�������: checkBox, �������: getEnabled), 2007
Private Sub cbZeroEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'cbZeroTrue (�������: checkBox, �������: onAction), 2007
Private Sub cbSetZero(control As IRibbonControl, pressed As Boolean)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID & " (��������� = " & CStr(pressed) & ")"
End Sub

'oneAngle (�������: button, �������: onAction), 2007
Private Sub angleCheck(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'goAngle (�������: button, �������: onAction), 2007
Private Sub rot1Angle(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'btnManualOn (�������: button, �������: onAction), 2007
Private Sub manualOn(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'lblStep (�������: labelControl, �������: getLabel), 2007
Private Sub getLblStepManual(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'btnZero (�������: button, �������: onAction), 2007
Private Sub btnSetZero(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'btnSet120 (�������: button, �������: onAction), 2007
Private Sub btnSetAngle120(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'lblcrntUP (�������: labelControl, �������: getLabel), 2007
Private Sub getLblmainAngle(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'portVolt (�������: labelControl, �������: getLabel), 2007
Private Sub getLblPortVolt(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'portDriver (�������: labelControl, �������: getLabel), 2007
Private Sub getLblPortDriver(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'savedVolt (�������: labelControl, �������: getLabel), 2007
Private Sub getLblSavedVolt(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'savedDriver (�������: labelControl, �������: getLabel), 2007
Private Sub getLblSavedDriver(control As IRibbonControl, ByRef label)
    label = "label �������� " & control.ID
End Sub

'btn120 (�������: button, �������: onAction), 2007
Private Sub btnFind120(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub

'scanPorts (�������: button, �������: onAction), 2007
Private Sub btnScanPortsAction(control As IRibbonControl)
    MsgBox "��������� ���������, �������� � onAction �������� " & control.ID
End Sub
