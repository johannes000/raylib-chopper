@echo off
set SOURCE_DIR=%1
set DEST_DIR=%2

echo .aseprite > exclude.txt
xcopy /E /Y /I /D "%SOURCE_DIR%\assets" "%DEST_DIR%\assets" /EXCLUDE:exclude.txt 
xcopy /E /Y /I /D "%SOURCE_DIR%\Shader" "%DEST_DIR%\Shader"
del exclude.txt

exit /b 0