`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/16 11:19:21
// Design Name: 
// Module Name: Chip_Decoder_tb
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


module Chip_Decoder_tb(

    );
    reg A9,A8,F,A3,A2,AEN,IORbar,IOWbar;
    wire [3:0] CSbar;
    wire Ebar,DIR;
    Chip_Decoder dut(A9,A8,F,A3,A2,AEN,IORbar,IOWbar,CSbar,Ebar,DIR);
    initial
    begin
        A9 = 1;A8 = 1;F = 1;A3 = 1;A2 = 0;AEN = 0;IORbar = 0;IOWbar = 1;
        #20 A3 = 0;A2 = 1;
        #20 IORbar = 1;IOWbar = 0;
        #20 A9 = 0;
        #20 A8 = 0;A9 = 1;
        #20 F = 1;A8 = 1;
        #20 F = 0;AEN = 1;
        #20 AEN = 0;IORbar = 0;
        #20 IOWbar = 1; 
    end
endmodule
