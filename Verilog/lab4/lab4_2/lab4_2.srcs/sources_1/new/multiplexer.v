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
    input [7:0] A,B,
    input S0,
    output [7:0] Z
    );
    assign 
        Z[0] = (A[0]&(~S0))^(B[0]&S0),
        Z[1] = (A[1]&(~S0))^(B[1]&S0),
        Z[2] = (A[2]&(~S0))^(B[2]&S0),
        Z[3] = (A[3]&(~S0))^(B[3]&S0),
        Z[4] = (A[4]&(~S0))^(B[4]&S0),
        Z[5] = (A[5]&(~S0))^(B[5]&S0),
        Z[6] = (A[6]&(~S0))^(B[6]&S0),
        Z[7] = (A[7]&(~S0))^(B[7]&S0);
endmodule
