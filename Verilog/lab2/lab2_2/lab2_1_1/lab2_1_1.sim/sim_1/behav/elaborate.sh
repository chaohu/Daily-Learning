#!/bin/sh -f
xv_path="/home/huchao/vivado/Vivado/2015.2"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xelab -wto 24956da0f9b04ed7b2c0c41685f06a90 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab2_1_1_tb_behav xil_defaultlib.lab2_1_1_tb xil_defaultlib.glbl -log elaborate.log
