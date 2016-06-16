`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/15 22:42:34
// Design Name: 
// Module Name: Decoder
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


module Decoder(
    input [9:0] A,
    input [3:0] DIP,
    input AEN,IORbar,IOWbar,
    output [3:0] CSbar,
    output Ebar,DIR
    );
    wire F;
    Paragraph_Decoder PD1(A[7],A[6],A[5],A[4],DIP,F);
    Chip_Decoder CD1(A[9],A[8],F,A[3],A[2],AEN,IORbar,IOWbar,CSbar,Ebar,DIR);
endmodule
