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
ExecStep $xv_path/bin/xelab -wto c46f5cc538594eeabf33ead1db6c5bee -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot gate_SR_latch_tb_behav xil_defaultlib.gate_SR_latch_tb xil_defaultlib.glbl -log elaborate.log
