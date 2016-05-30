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
ExecStep $xv_path/bin/xelab -wto 2939f42df6324bc6b76c0b2e58977afe -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot D_latch_dataflow_tb_behav xil_defaultlib.D_latch_dataflow_tb xil_defaultlib.glbl -log elaborate.log
