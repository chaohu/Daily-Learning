`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:38:16
// Design Name: 
// Module Name: multiplexer
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


module multiplexer(
    input [width-1:0] A,B,
    input S0,
    output reg [width-1:0] Z
    );
    parameter width = 8;
    always @(A or B or S0)
    begin
        if(S0)
            Z = A;
        else
            Z = B;
    end
endmodule
