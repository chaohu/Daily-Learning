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
ExecStep $xv_path/bin/xelab -wto 0d818293aa754e25b2fbf216e53a57f2 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab3_3_2_tb_behav xil_defaultlib.lab3_3_2_tb xil_defaultlib.glbl -log elaborate.log
