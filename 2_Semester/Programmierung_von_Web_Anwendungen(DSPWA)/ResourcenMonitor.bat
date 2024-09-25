@echo off
setlocal enabledelayedexpansion

REM Dateipfad für die CSV-Datei
set output=express-server-usage.csv

REM Header in die CSV-Datei schreiben
echo Timestamp,CPU_Usage(%),RAM_Usage(MB) > %output%

REM PID des Express.js Servers herausfinden
for /f "tokens=2 delims==" %%i in ('wmic process where "caption='node.exe' and commandline like '%%express%%'" get ProcessId /value') do set pid=%%i

if "!pid!"=="" (
    echo Express.js Server konnte nicht gefunden werden!
	Pause
    exit /b 1
)

REM Wiederholung alle 10 Sekunden
:loop
    REM Zeitstempel abrufen
    for /f "tokens=1-2" %%i in ('wmic os get localdatetime /value') do set timestamp=%%i%%j

    REM CPU- und RAM-Nutzung abrufen
    for /f "tokens=1,2" %%a in ('wmic path Win32_PerfFormattedData_PerfProc_Process where "IDProcess='!pid!'" get PercentProcessorTime, WorkingSetPrivate /value') do (
        set "cpu=%%a"
        set "ram=%%b"
    )

    REM RAM-Nutzung in MB umrechnen (von Bytes)
    set /a ramMB=!ram! / 1024 / 1024

    REM Ergebnisse in CSV-Datei schreiben
    echo !timestamp!,!cpu!,!ramMB! >> %output%

    REM 10 Sekunden warten
    timeout /t 10 /nobreak >nul
goto loop