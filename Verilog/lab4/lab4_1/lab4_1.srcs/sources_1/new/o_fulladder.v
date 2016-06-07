`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:13:48
// Design Name: 
// Module Name: o_fulladder
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


module o_fulladder(
    input a,b,Cin,
    output z,C
    );
    assign z = a ^ b ^ Cin;
    assign C = ((a ^ b)&Cin)|(a & b); 
endmodule
