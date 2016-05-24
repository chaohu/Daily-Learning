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
ExecStep $xv_path/bin/xsim lab1_1_1_tb_behav -key {Behavioral:sim_1:Functional:lab1_1_1_tb} -tclbatch lab1_1_1_tb.tcl -log simulate.log
