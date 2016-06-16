`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/16 10:57:38
// Design Name: 
// Module Name: Paragraph_Decoder
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


module Paragraph_Decoder(
    input A7,A6,A5,A4,
    input [3:0] DIP,
    output reg F
    );
    always @(A7 or A6 or A5 or A4 or DIP)
    begin
        if((DIP[3] == A7) & (DIP[2] == A6) &  (DIP[1] == A5) &  (DIP[0] == A4))
            F = 1;
        else
            F = 0;
    end 
endmodule
