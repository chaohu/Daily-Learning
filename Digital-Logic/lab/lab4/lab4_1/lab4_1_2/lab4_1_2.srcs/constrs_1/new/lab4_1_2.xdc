# Nexys4 Pin Assignments
############################
# On-board Slide Switches  #
############################

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets CP_IBUF]

set_property PACKAGE_PIN F15 [get_ports CP]
set_property IOSTANDARD LVCMOS33 [get_ports CP]
set_property PACKAGE_PIN U9 [get_ports M]
set_property IOSTANDARD LVCMOS33 [get_ports M]

############################
# On-board led             #
############################
set_property PACKAGE_PIN T8 [get_ports Qa]
set_property IOSTANDARD LVCMOS33 [get_ports Qa]
set_property PACKAGE_PIN V9 [get_ports Qb]
set_property IOSTANDARD LVCMOS33 [get_ports Qb]
set_property PACKAGE_PIN R8 [get_ports Qc]
set_property IOSTANDARD LVCMOS33 [get_ports Qc]
set_property PACKAGE_PIN T6 [get_ports Qd]
set_property IOSTANDARD LVCMOS33 [get_ports Qd]
set_property PACKAGE_PIN T5 [get_ports Z]
set_property IOSTANDARD LVCMOS33 [get_ports Z]