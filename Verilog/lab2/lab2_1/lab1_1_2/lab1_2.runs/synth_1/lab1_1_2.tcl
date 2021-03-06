# 
# Synthesis run script generated by Vivado
# 

debug::add_scope template.lib 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7a100tcsg324-1

set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir /home/huchao/Daily-Learning/Verilog/lab2/lab1_2/lab1_2.cache/wt [current_project]
set_property parent.project_path /home/huchao/Daily-Learning/Verilog/lab2/lab1_2/lab1_2.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
read_verilog -library xil_defaultlib /home/huchao/Daily-Learning/Verilog/lab2/lab1_2/lab1_2.srcs/sources_1/new/lab1_1_2.v
synth_design -top lab1_1_2 -part xc7a100tcsg324-1
write_checkpoint -noxdef lab1_1_2.dcp
catch { report_utilization -file lab1_1_2_utilization_synth.rpt -pb lab1_1_2_utilization_synth.pb }
