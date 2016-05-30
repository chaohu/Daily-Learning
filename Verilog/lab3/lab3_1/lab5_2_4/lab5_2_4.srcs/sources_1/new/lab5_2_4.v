`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 20:56:37
// Design Name: 
// Module Name: lab5_2_4
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


module lab5_2_4(
    input D,Clk,reset,ce,
    output reg Q
    );
    always @(posedge Clk)
    if (reset)
    begin
        Q <= 1'b0;
    end else if (ce)
    begin
        Q <= D;
    end
endmodule
