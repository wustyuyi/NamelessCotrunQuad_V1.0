::@echo off 

@for /d /r %%c in (Debug,settings,Release,Output,DebugConfig) do @if exist %%c ( rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c) 

@for /r  %%c in (*.tmp,*.bak ,*.dep,*.sfr,Backup* ) do del "%%c"
pause