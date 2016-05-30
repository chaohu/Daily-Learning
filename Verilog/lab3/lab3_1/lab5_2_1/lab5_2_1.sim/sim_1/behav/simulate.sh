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
ExecStep $xv_path/bin/xsim D_ff_behavior_tb_behav -key {Behavioral:sim_1:Functional:D_ff_behavior_tb} -tclbatch D_ff_behavior_tb.tcl -log simulate.log
