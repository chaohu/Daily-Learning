`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 15:58:07
// Design Name: 
// Module Name: lab1_3_2
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


module lab1_3_2(x,y,s,m);
    input [1:0] x, y;
    input s;
    output reg [1:0] m;
    
    always @( x or y or s)
    begin
        m[0] = #3 (~s & x[0]) | (s & y[0]);
        m[1] = #3 (~s & x[1]) | (s & y[1]);
    end
endmodule
