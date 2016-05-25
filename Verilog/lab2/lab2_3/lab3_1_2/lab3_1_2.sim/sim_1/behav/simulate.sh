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
ExecStep $xv_path/bin/xsim decoder_74138_dataflow_tb_behav -key {Behavioral:sim_1:Functional:decoder_74138_dataflow_tb} -tclbatch decoder_74138_dataflow_tb.tcl -log simulate.log
