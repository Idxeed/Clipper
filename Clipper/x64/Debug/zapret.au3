; ** Скрипт запрещения двойного запуска приложений**

; Функция Singleton создаёт семафор при помощи  WinAPI. Если такой семафор уже создан, то заканчиваем работу 
Func Singleton($semaphore)
    Local $ERROR_ALREADY_EXISTS = 183
    DllCall("kernel32.dll", "int", "CreateSemaphore", "int", 0, "long", 1, "long", 1, "str", $semaphore)
    Local $lastError = DllCall("kernel32.dll", "int", "GetLastError")
    If $lastError[0] = $ERROR_ALREADY_EXISTS Then Exit -1
EndFunc

Singleton("Mutex")

; Системная функция ShellExecuteWait запускает приложение и ожидает окончания работы с ним
; Дожидаться завершения программы нужно, чтобы корректно работал Mutex
; $CmdLineRaw - параметр запуска получаемый скриптом
ShellExecuteWait(""C:\Users\murza\source\repos\Clipper\x64\Debug\Clipper.exe"", $CmdLineRaw, @ScriptDir, "open", @SW_MAXIMIZE)