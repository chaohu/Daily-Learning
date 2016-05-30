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
ExecStep $xv_path/bin/xsim gate_SR_latch_tb_behav -key {Behavioral:sim_1:Functional:gate_SR_latch_tb} -tclbatch gate_SR_latch_tb.tcl -log simulate.log
