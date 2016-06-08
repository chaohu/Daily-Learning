`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 10:02:26
// Design Name: 
// Module Name: lab6_1_4_tb
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


module lab6_1_4_tb(

    );
    reg Clk,ShiftIn,out,ShiftEn;
    wire ShiftOut;
    wire [3:0] RegContent,ParallelOut;
    lab6_1_4 dut(Clk,ShiftIn,out,ShiftEn,ShiftOut,RegContent,ParallelOut);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk + 1)
        begin
            #10;
        end
    end
    initial
    begin
        ShiftIn = 1;out = 0;ShiftEn = 0;
        #40 out = 1;
        #20 out  = 0;
        #20 ShiftEn = 1;
        #20 out  = 1;
        #20 out  = 0;
        #55 out  = 1;
        #20 out  = 0;
    end
endmodule
