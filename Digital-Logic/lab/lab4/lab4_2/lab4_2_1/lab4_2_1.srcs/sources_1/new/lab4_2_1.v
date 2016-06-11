`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 20:47:59
// Design Name: 
// Module Name: lsb4_2_1
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


module lab4_2_1(
    input [1:0] A,B,
    output reg F1,F2,F3
    );
    wire F11,F12,F21,F22,F31,F32;
    one_comparator com1(A[1],B[1],F12,F22,F32);
    one_comparator com2(A[0],B[0],F11,F21,F31);
    always @(F11,F12,F21,F22,F31,F32)
    begin
        if(F12 | (F22 & F11))
        begin
            F1 = 1;F2 = 0;F3 = 0;
        end
        else if(F22 & F21)
        begin
            F1 = 0;F2 = 1;F3 = 0;
        end
        else
        begin
            F1 = 0;F2 = 0;F3 = 1;
        end
    end
endmodule
