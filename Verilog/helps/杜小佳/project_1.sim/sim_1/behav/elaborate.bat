@echo off
set xv_path=D:\\VIVADO\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto b82643ef40af4f478c6a33f8f10d4214 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot jishuqi_tb_behav xil_defaultlib.jishuqi_tb xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
