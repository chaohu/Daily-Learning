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
    input [7:0] A,B,
    output [7:0] Z
    );
    wire [8:0] c;
    assign c[0] = 0;
    o_fulladder add1(A[0],B[0],c[0],Z[0],c[1]);
    o_fulladder add2(A[1],B[0],c[1],Z[1],c[2]);
    o_fulladder add3(A[2],B[0],c[2],Z[2],c[3]);
    o_fulladder add4(A[3],B[0],c[3],Z[3],c[4]);
    o_fulladder add5(A[4],B[0],c[4],Z[4],c[5]);
    o_fulladder add6(A[5],B[0],c[5],Z[5],c[6]);
    o_fulladder add7(A[6],B[0],c[6],Z[6],c[7]);
    o_fulladder add8(A[7],B[0],c[7],Z[7],c[8]);
endmodule
