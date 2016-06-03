`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/02 16:52:54
// Design Name: 
// Module Name: lab3_1
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


module lab3_1(
    input Ai,Bi,Cin,
    output wire Si,Ci,F
    );
    wire X1,A1,A2,A3,A4,C1;
    xor #2
        ux1 (X1,Ai,Bi),
        ux2 (A4,X1,C1);
    and #2
        ua1 (A1,Ai,Bi),
        ua2 (A2,A1,1),
        ua3 (C1,Cin,1),
        ua4 (A3,X1,C1),
        ua5 (Si,A4,1);
    or #2
        uo1 (Ci,A2,A3);
    xnor #2
        un1 (F,Si,Ci);
endmodule
