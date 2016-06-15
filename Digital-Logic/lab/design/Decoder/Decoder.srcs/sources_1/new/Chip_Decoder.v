`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/15 23:06:33
// Design Name: 
// Module Name: Chip_Decoder
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


module Chip_Decoder(
    input A9,A8,F,A3,A2,AEN,IORbar,IOWbar,
    output [3:0] CSbar,
    output Ebar,DIR
    );
    always @(A9 or A8 or AEN or F)
    begin
        if((A9 == 1) & (A8 == 1) & AEN & F)
            Ebar = 0;
        else
            Ebar = 1;
    end
endmodule
