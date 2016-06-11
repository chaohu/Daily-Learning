`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/02 23:54:22
// Design Name: 
// Module Name: lab3_3
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


module lab3_3(
    input INPUT,CLK,
    output wire Q1,N1,OUT
    );
    D_lator DL1(INPUT,CLK,Q1);
    D_lator2 DL2(N1,CLK,OUT);
    not #17 un1(N1,Q1);
    
endmodule
