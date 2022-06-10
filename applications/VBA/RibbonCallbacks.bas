Attribute VB_Name = "RibbonCallbacks"	'Имя текущего модуля
Option Explicit	'Потребовать явного объявления всех переменных в файле

'customUI (элемент: customUI, атрибут: onLoad), 2007
Private Sub ribOnLoad(ribbon As IRibbonUI)
    'Объявите глобальную переменную объекта ленты: Public myRibbonObject As IRibbonUI
    Set myRibbonObject = ribbon
End Sub

'btnLinear (элемент: button, атрибут: onAction), 2007
Private Sub startLine(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'cbManual0Angle (элемент: checkBox, атрибут: getPressed), 2007
Private Sub cbManualAnglPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'cbManual0Angle (элемент: checkBox, атрибут: getEnabled), 2007
Private Sub cbManualAnglsEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'cbManual0Angle (элемент: checkBox, атрибут: onAction), 2007
Private Sub cbManualAngleAction(control As IRibbonControl, pressed As Boolean)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID & " (нажатость = " & CStr(pressed) & ")"
End Sub

'bxCorrectAngle (элемент: checkBox, атрибут: getPressed), 2007
Private Sub cbxCorAnglPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'bxCorrectAngle (элемент: checkBox, атрибут: getEnabled), 2007
Private Sub cbCorAnglsEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'bxCorrectAngle (элемент: checkBox, атрибут: onAction), 2007
Private Sub cbxCorrectAngleAction(control As IRibbonControl, pressed As Boolean)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID & " (нажатость = " & CStr(pressed) & ")"
End Sub

'btnCorrectAngle (элемент: button, атрибут: onAction), 2007
Private Sub correctAngle(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'cbZeroTrue (элемент: checkBox, атрибут: getPressed), 2007
Private Sub cbxGetZerolPressed(control As IRibbonControl, ByRef pressed)
    pressed = True
End Sub

'cbZeroTrue (элемент: checkBox, атрибут: getEnabled), 2007
Private Sub cbZeroEna(control As IRibbonControl, ByRef enabled)
    enabled = True
End Sub

'cbZeroTrue (элемент: checkBox, атрибут: onAction), 2007
Private Sub cbSetZero(control As IRibbonControl, pressed As Boolean)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID & " (нажатость = " & CStr(pressed) & ")"
End Sub

'oneAngle (элемент: button, атрибут: onAction), 2007
Private Sub angleCheck(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'goAngle (элемент: button, атрибут: onAction), 2007
Private Sub rot1Angle(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'btnManualOn (элемент: button, атрибут: onAction), 2007
Private Sub manualOn(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'lblStep (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblStepManual(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'btnZero (элемент: button, атрибут: onAction), 2007
Private Sub btnSetZero(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'btnSet120 (элемент: button, атрибут: onAction), 2007
Private Sub btnSetAngle120(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'lblcrntUP (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblmainAngle(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'portVolt (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblPortVolt(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'portDriver (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblPortDriver(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'savedVolt (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblSavedVolt(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'savedDriver (элемент: labelControl, атрибут: getLabel), 2007
Private Sub getLblSavedDriver(control As IRibbonControl, ByRef label)
    label = "label элемента " & control.ID
End Sub

'btn120 (элемент: button, атрибут: onAction), 2007
Private Sub btnFind120(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub

'scanPorts (элемент: button, атрибут: onAction), 2007
Private Sub btnScanPortsAction(control As IRibbonControl)
    MsgBox "Сработала процедура, заданная в onAction элемента " & control.ID
End Sub
