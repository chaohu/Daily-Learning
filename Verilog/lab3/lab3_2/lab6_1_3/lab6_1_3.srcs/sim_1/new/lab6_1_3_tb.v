`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 09:51:27
// Design Name: 
// Module Name: lab6_1_3_tb
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


module lab6_1_3_tb(

    );
    reg Clk,ShiftIn;
    wire ShiftOut;
    lab6_1_3 dut(Clk,ShiftIn, ShiftOut);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk +1)
        begin
            #10;
        end
    end
    initial
    begin
        ShiftIn = 0;
        #20 ShiftIn  = 1;
        #40 ShiftIn  = 0;
        #20 ShiftIn  = 1;
        #40 ShiftIn  = 0;
    end
endmodule
