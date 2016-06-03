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
ExecStep $xv_path/bin/xsim lab3_3_tb_behav -key {Behavioral:sim_1:Functional:lab3_3_tb} -tclbatch lab3_3_tb.tcl -log simulate.log
