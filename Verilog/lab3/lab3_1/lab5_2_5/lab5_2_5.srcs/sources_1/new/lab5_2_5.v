`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:09:01
// Design Name: 
// Module Name: lab5_2_5
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


module lab5_2_5(
    input Clk,reset_n, T,
    output reg Q
    );
    always @(negedge Clk)
    if (!reset_n)
        Q <= 1'b0;
    else if (T)
        Q <= ~Q;
endmodule
