`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:28:14
// Design Name: 
// Module Name: lab6_1_1
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


module lab6_1_1(
    input [3:0] D,
    input Clk,reset,load,
    output reg [3:0] Q
    );
    always @(posedge Clk)
    if (reset)
    begin
        Q <= 4'b0;
    end else if (load)
    begin
        Q <= D;
    end
endmodule
