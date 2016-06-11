# Nexys4 Pin Assignments
############################
# On-board Slide Switches  #
############################

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets clk_IBUF]

set_property PACKAGE_PIN E3 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]

############################
# On-board led             #
############################
set_property PACKAGE_PIN T8 [get_ports m]
set_property IOSTANDARD LVCMOS33 [get_ports m]
set_property PACKAGE_PIN V9 [get_ports Z[0]]
set_property IOSTANDARD LVCMOS33 [get_ports Z[0]]
set_property PACKAGE_PIN R8 [get_ports Z[1]]
set_property IOSTANDARD LVCMOS33 [get_ports Z[1]]
set_property PACKAGE_PIN T6 [get_ports Z[2]]
set_property IOSTANDARD LVCMOS33 [get_ports Z[2]]
set_property PACKAGE_PIN T5 [get_ports Z[3]]
set_property IOSTANDARD LVCMOS33 [get_ports Z[3]]