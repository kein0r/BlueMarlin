echo off
:: set title and size of the command window
TITLE BlueMarlin Build Environment
mode con:cols=130 lines=3000
color F1
:: Add your compiler to PATH if needed
PATH=C:\compiler\TDM-GCC-64;%PATH%
:: Unfortunately TDM-GCC make is called mingw32-make. Create a batchfile
echo @echo off > make.bat
echo call mingw32-make %%* >> make.bat
:: Show initial help
echo ----------------------------------------------
echo  Welcome to BlueMarlin Build Environment
echo ----------------------------------------------
:: Leave command window open
cmd /c "make help"
cmd