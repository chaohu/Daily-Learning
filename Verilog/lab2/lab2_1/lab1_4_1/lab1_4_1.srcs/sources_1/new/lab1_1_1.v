`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 16:16:03
// Design Name: 
// Module Name: lab1_1_1
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


module lab1_1_1(x,y,s,m);
    input x,y,s;
    output m;
    wire s1,s2,s3;
    not
        un1(s1,s);
    and
        ux1(s2,s,y),
        ux2(s3,x,s1);
    or
        uo1(m,s2,s3);
endmodule
