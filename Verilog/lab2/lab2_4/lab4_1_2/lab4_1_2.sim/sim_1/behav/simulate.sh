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
ExecStep $xv_path/bin/xsim calc_even_parity_task_tb_behav -key {Behavioral:sim_1:Functional:calc_even_parity_task_tb} -tclbatch calc_even_parity_task_tb.tcl -log simulate.log
