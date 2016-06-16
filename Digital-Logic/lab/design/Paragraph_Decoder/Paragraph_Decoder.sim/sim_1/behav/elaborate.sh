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
ExecStep $xv_path/bin/xelab -wto db5dee98732d4076a0fc905d3fdc68d7 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot Paragraph_Decoder_tb_behav xil_defaultlib.Paragraph_Decoder_tb xil_defaultlib.glbl -log elaborate.log
