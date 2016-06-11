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
ExecStep $xv_path/bin/xelab -wto 10a65e65e26543238c5f66cfe7499c49 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L secureip --snapshot lab4_1_2_tb_func_synth xil_defaultlib.lab4_1_2_tb xil_defaultlib.glbl -log elaborate.log
