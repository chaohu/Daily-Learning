`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 20:40:58
// Design Name: 
// Module Name: lab5_2_3
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


module lab5_2_3(
    input Clk,D,reset,
    output reg Q
    );
    always @(posedge Clk)
    if (reset)
        begin
        Q <= 1'b0;
        end 
    else
    begin
        Q <= D;
    end
endmodule
