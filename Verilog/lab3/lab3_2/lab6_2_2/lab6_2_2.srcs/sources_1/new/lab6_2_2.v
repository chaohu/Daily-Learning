`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 11:25:38
// Design Name: 
// Module Name: lab6_2_2
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


module lab6_2_2(
    input Enable,Clk,
    output Z
    );
    wire O1,O2,O3,O4,Q1,Q1bar,Q2,Q2bar,Q3,Q3bar,Q4bar;
    xor
        uo1(O1,Enable,Q1),
        uo2(O2,Q1,Q2),
        uo3(O3,Q2,Q3),
        uo4(O4,Q3,Z);
    d_ff
        t1(O1,Clk,Q1,Q1bar),
        t2(O2,Clk,Q2,Q2bar),
        t3(O3,Clk,Q3,Q3bar),
        t4(O4,Clk,Z,Q4bar);
endmodule
