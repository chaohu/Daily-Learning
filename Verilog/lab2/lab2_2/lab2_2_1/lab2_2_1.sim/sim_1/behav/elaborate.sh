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
ExecStep $xv_path/bin/xelab -wto 9f02c3289fbb4d1c98f65244df86b375 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab2_2_1_partA_tb_behav xil_defaultlib.lab2_2_1_partA_tb xil_defaultlib.glbl -log elaborate.log
