`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 23:36:17
// Design Name: 
// Module Name: lab2_2_1
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


module lab2_2_1(
    input [3:0] v,
    output wire [6:0] seg0
    );
    wire z;
    wire [3:0] m;
    
    lab2_2_1_partA par(v,z,m);
    
    bcdto7segment_dataflow seg(m,seg0);
    
endmodule
