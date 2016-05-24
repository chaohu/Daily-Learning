`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/23 21:36:32
// Design Name: 
// Module Name: lab1_1_2
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


module lab1_1_2(
    input [1:0] x,
    input [1:0] y,
    input s,
    output [1:0] m
    );
    wire s1,s2,s3,s4,s5;
    not
        un1(s1,s);
    and
        ua1(s2,s,y[0]),
        ua2(s3,x[0],s1);
    or
        uo1(m[0],s2,s3);
    and
        ua3(s4,s,y[1]),
        ua4(s5,x[1],s1);
    or
        uo2(m[1],s4,s5);
endmodule
