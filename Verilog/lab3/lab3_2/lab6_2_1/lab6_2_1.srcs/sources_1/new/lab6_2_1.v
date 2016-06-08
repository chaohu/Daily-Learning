`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 10:30:50
// Design Name: 
// Module Name: lab6_2_1
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


module lab6_2_1(
    input Enable,Clk,Clear,
    output z,
    output wire A1,A2,A3,Q1,Q1bar,Q2,Q2bar,Q3,Q3bar,Q4bar
    );
    and
        ua1(A1,Enable,Q1),
        ua2(A2,A1,Q2),
        ua3(A3,A2,Q3);
    t_ff
        t1(Enable,Clk,Clear,Q1,Q1bar),
        t2(A1,Clk,Clear,Q2,Q2bar),
        t3(A2,Clk,Clear,Q3,Q3bar),
        t4(A3,Clk,Clear,z,Q4bar);
endmodule
