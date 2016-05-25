`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 15:30:40
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
    input cin
    input [3:0] v,
    output wire z,
    output wire seg
    );
    
    assign z = ((cin ==1) || (v > 9)) ? 1 : 0;
    assign seg = (v > 9) ? 9
    
endmodule
