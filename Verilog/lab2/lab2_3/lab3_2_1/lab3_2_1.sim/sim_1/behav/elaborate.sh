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
ExecStep $xv_path/bin/xelab -wto 0303ea328e574a799f2cae8747a5374c -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab3_2_1_tb_behav xil_defaultlib.lab3_2_1_tb xil_defaultlib.glbl -log elaborate.log
