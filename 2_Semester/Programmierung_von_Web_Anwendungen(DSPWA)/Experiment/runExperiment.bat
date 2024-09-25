@echo off
setlocal enabledelayedexpansion

REM Wiederhole 3 mal
for /L %%i in (1,1,3) do (
    echo Iteration %%i

    REM Für jede .yml Datei
    for %%f in (*.yml) do (
		del stop.txt
        echo Running main.py in pythonProject

        REM Starte main.py mit CSV-Dateinamen und Prozess-ID und speichere die PID
        start /B python pythonProject\main.py t_%%f_%%i_asynchron.csv 7268
        
        REM Warte kurz, um sicherzustellen, dass der Prozess gestartet wurde
        timeout /t 2 /nobreak >nul

        
        echo Running python 

        REM Führe Artillery Test aus
        artillery run %%f --output t_%%f_%%i_result_a.json

        REM Stoppe main.py durch Beenden der gespeicherten PID
        echo Stopping python 
        echo stop > stop.txt
        timeout /t 1 >nul
 

        REM Erstelle Artillery Report
        artillery report --output report_t_%%f_%%i_a.html t_%%f_%%i_result_a.json

    )
)

echo Alle Durchläufe abgeschlossen!