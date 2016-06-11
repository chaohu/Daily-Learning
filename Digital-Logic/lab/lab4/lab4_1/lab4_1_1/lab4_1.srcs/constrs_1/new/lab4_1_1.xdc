# Nexys4 Pin Assignments
############################
# On-board Slide Switches  #
############################

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets CP_IBUF]

set_property PACKAGE_PIN U9 [get_ports CP]
set_property IOSTANDARD LVCMOS33 [get_ports CP]
set_property PACKAGE_PIN U8 [get_ports CLR]
set_property IOSTANDARD LVCMOS33 [get_ports CLR]
set_property PACKAGE_PIN R7 [get_ports LD]
set_property IOSTANDARD LVCMOS33 [get_ports LD]
set_property PACKAGE_PIN R6 [get_ports M]
set_property IOSTANDARD LVCMOS33 [get_ports M]
set_property PACKAGE_PIN R5 [get_ports A]
set_property IOSTANDARD LVCMOS33 [get_ports A]
set_property PACKAGE_PIN V7 [get_ports B]
set_property IOSTANDARD LVCMOS33 [get_ports B]
set_property PACKAGE_PIN V6 [get_ports C]
set_property IOSTANDARD LVCMOS33 [get_ports C]
set_property PACKAGE_PIN V5 [get_ports D]
set_property IOSTANDARD LVCMOS33 [get_ports D]

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
