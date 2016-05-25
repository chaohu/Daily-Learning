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
ExecStep $xv_path/bin/xelab -wto f3f3491cdead4c79acb2c6cea8a8328c -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot fulladder_dataflow_tb_behav xil_defaultlib.fulladder_dataflow_tb xil_defaultlib.glbl -log elaborate.log
