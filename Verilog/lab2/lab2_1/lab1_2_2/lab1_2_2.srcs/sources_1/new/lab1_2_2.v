`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 11:43:36
// Design Name: 
// Module Name: lab1_2_2
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


module lab1_2_2(x,y,s,m);
    input [1:0] x;
    input [1:0] y;
    input s;
    output [1:0] m;
    
    assign #3 m = (s) ? y : x;
endmodule
