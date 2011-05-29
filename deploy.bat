
set CONFIG=%1

xcopy /Y %CONFIG%\musli.dll %MUSLI_DIR%\bin 
xcopy /Y %CONFIG%\musli.dll %MUSLI_DIR%\lib
xcopy /Y musli\*.h %MUSLI_DIR%\include\musli
