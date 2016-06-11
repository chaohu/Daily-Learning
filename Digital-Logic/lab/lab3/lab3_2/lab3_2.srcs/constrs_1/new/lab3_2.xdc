# Nexys4 Pin Assignments
############################
# On-board Slide Switches  #
############################
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets x_IBUF]

set_property PACKAGE_PIN U9 [get_ports x]
set_property IOSTANDARD LVCMOS33 [get_ports x]

############################
# On-board led             #
############################
set_property PACKAGE_PIN T8 [get_ports q1]
set_property IOSTANDARD LVCMOS33 [get_ports q1]
set_property PACKAGE_PIN V9 [get_ports q2]
set_property IOSTANDARD LVCMOS33 [get_ports q2]
set_property PACKAGE_PIN R8 [get_ports q3]
set_property IOSTANDARD LVCMOS33 [get_ports q3]
set_property PACKAGE_PIN T6 [get_ports q4]
set_property IOSTANDARD LVCMOS33 [get_ports q4]
set_property PACKAGE_PIN T5 [get_ports z]
set_property IOSTANDARD LVCMOS33 [get_ports z]