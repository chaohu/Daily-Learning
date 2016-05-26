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
ExecStep $xv_path/bin/xelab -wto 5a76542ee0b14607b01b0bbcaf554269 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot calc_even_parity_task_tb_behav xil_defaultlib.calc_even_parity_task_tb xil_defaultlib.glbl -log elaborate.log
