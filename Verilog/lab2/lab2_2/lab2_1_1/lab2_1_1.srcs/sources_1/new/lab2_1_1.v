`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 20:46:40
// Design Name: 
// Module Name: lab2_1_1
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


module lab2_1_1(
    input [3:0] num,
    output [6:0] seg
    );
    wire [3:0] an;
    
    bcdto7segment_dataflow dut(num,an,seg);
    
endmodule
