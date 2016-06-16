`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/16 11:03:20
// Design Name: 
// Module Name: Paragraph_Decoder_tb
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


module Paragraph_Decoder_tb(
    
    );
    reg A7,A6,A5,A4;
    reg [3:0] DIP;
    wire F;
    Paragraph_Decoder dut(A7,A6,A5,A4,DIP,F);
    initial
    begin
        DIP = 4'b0100;A7 = 0;A6 = 1;A5 = 0;A4 = 0;
        #20 A7 = 1;
        #20 DIP = 4'b1100;
        #20 DIP = 4'b1001;
    end
endmodule
