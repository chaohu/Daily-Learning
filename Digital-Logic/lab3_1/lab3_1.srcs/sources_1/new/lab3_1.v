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
    wire X1,A1,A2;
    xor #2
        ux1 (X1,Ai,Bi),
        ux2 (Si,X1,Cin);
    and #2
        ua1 (A1,Ai,Bi),
        ua2 (A2,X1,Cin);
    or #2
        uo1 (Ci,A1,A2);
    xnor #2
        un1 (F,Si,Ci);
endmodule
