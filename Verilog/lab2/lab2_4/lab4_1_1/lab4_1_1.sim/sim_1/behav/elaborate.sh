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
ExecStep $xv_path/bin/xelab -wto 28c1bdf668b84d468a3f3706824aa4ee -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot add_two_values_task_tb_behav xil_defaultlib.add_two_values_task_tb xil_defaultlib.glbl -log elaborate.log
