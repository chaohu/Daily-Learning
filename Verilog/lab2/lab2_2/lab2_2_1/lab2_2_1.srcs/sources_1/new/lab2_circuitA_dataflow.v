`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 23:08:08
// Design Name: 
// Module Name: lab2_circuitA_dataflow
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


module lab2_circuitA_dataflow(
    input [3:0] v,
    output wire [3:0] c
    );
    assign c = v - 10;
    
endmodule
