`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:40:30
// Design Name: 
// Module Name: e_fulladder
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


module e_fulladder(
    input [width-1:0] A,B,
    output reg [width-1:0] Z
    );
    parameter width = 8;
    always @(A or B)
    begin
        Z = A + B;
    end
endmodule
