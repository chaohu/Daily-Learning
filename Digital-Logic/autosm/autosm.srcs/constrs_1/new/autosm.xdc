# Nexys4 Pin Assignments

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets clk_IBUF]

############################
# On-board Slide Switches  #
############################

set_property PACKAGE_PIN U9 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property PACKAGE_PIN U8 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]
set_property PACKAGE_PIN R7 [get_ports op_start]
set_property IOSTANDARD LVCMOS33 [get_ports op_start]
set_property PACKAGE_PIN R6 [get_ports cancel_flag]
set_property IOSTANDARD LVCMOS33 [get_ports cancel_flag]
set_property PACKAGE_PIN R5 [get_ports coin_val[0]]
set_property IOSTANDARD LVCMOS33 [get_ports coin_val[0]]
set_property PACKAGE_PIN V7 [get_ports coin_val[1]]
set_property IOSTANDARD LVCMOS33 [get_ports coin_val[1]]

############################
# On-board led             #
############################
set_property PACKAGE_PIN T8 [get_ports hold_ind]
set_property IOSTANDARD LVCMOS33 [get_ports hold_ind]
set_property PACKAGE_PIN V9 [get_ports drinktk_ind]
set_property IOSTANDARD LVCMOS33 [get_ports drinktk_ind]
set_property PACKAGE_PIN R8 [get_ports charge_ind]
set_property IOSTANDARD LVCMOS33 [get_ports charge_ind]
set_property PACKAGE_PIN T6 [get_ports charge_val[0]]
set_property IOSTANDARD LVCMOS33 [get_ports charge_val[0]]
set_property PACKAGE_PIN T5 [get_ports charge_val[1]]
set_property IOSTANDARD LVCMOS33 [get_ports charge_val[1]]
set_property PACKAGE_PIN T4 [get_ports charge_val[2]]
set_property IOSTANDARD LVCMOS33 [get_ports charge_val[2]]