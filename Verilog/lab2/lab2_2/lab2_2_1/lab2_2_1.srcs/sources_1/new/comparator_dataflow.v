`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 23:07:45
// Design Name: 
// Module Name: comparator_dataflow
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module comparator_dataflow(
    input [3:0] v,
    output wire z
    );
    
    assign z = (v > 9) ? 1 : 0;
    
endmodule
