`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 21:39:16
// Design Name: 
// Module Name: one_comparator
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


module one_comparator(
    input a,b,
    output f1,f2,f3
    );
    wire f21,f22;
    and
        ua1(f1,a,~b),
        ua2(f21,~a,~b),
        ua3(f22,a,b),
        ua4(f3,~a,b);
    or
        uo1(f2,f21,f22);
endmodule
