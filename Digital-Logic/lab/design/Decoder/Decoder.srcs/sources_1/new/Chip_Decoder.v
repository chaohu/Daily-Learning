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
    output reg [3:0] CSbar,
    output reg Ebar,DIR
    );
    reg [1:0] A;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3;
    always @(A9 or A8 or AEN or F or IORbar or IOWbar)
    begin
        if((A9 == 1) & (A8 == 1) & (AEN == 0) & F & (IORbar != IOWbar))
            Ebar = 0;
        else
            Ebar = 1;
        if((IORbar == 0) & (IOWbar ==1))
            DIR = 0;
        else
            DIR = 1;
    end
    always @(A3 or A2)
    begin
        A = {A3,A2};
        case(A)
            S0 : CSbar = 4'b1110;
            S1 : CSbar = 4'b1101;
            S2 : CSbar = 4'b1011;
            S3 : CSbar = 4'b0111;
        endcase
    end
endmodule
