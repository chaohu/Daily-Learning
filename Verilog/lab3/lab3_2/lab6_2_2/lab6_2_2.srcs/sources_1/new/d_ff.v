`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 11:27:26
// Design Name: 
// Module Name: d_ff
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


module d_ff(
    input d,Clk,
    output reg q,qbar
    );
    initial
    begin
        q = 0;qbar = 1;
    end
    always @(posedge Clk)
    begin
        q = d;
        qbar = ~q;
    end
endmodule
