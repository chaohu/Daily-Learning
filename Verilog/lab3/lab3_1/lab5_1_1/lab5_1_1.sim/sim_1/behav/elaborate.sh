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
ExecStep $xv_path/bin/xelab -wto 54a996b8d2df4a0ba7287f8622e973ea -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot SR_latch_dataflow_tb_behav xil_defaultlib.SR_latch_dataflow_tb xil_defaultlib.glbl -log elaborate.log
