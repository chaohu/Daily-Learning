`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:49:23
// Design Name: 
// Module Name: lab6_1_2
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


module lab6_1_2(
    input Clk,reset,set,load,
    input [3:0] D,S,
    output reg [3:0] Q
    );
    always @(posedge Clk)
    if (reset)
    begin
        Q <= 4'b0;
    end else if (set)
    begin
        Q <= S;
    end else if (load)
    begin
        Q <= D;
    end
endmodule
