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
ExecStep $xv_path/bin/xelab -wto cdecb5e4081548cbb68808774b51ed33 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot decoder_3to8_dataflow_tb_behav xil_defaultlib.decoder_3to8_dataflow_tb xil_defaultlib.glbl -log elaborate.log
