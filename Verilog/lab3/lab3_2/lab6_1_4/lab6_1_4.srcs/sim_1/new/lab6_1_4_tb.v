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
    reg Clk,ShiftIn,load,ShiftEn;
    reg [3:0] ParallelIn;
    wire ShiftOut;
    wire [3:0] RegContent;
    lab6_1_4 dut(Clk,ShiftIn,load,ShiftEn,ParallelIn,ShiftOut,RegContent);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk + 1)
        begin
            #10;
        end
    end
    initial
    begin
        ShiftIn = 1;load = 0;ShiftEn = 0;ParallelIn = 4'b0;
        #20 ParallelIn = 4'b0101;
        #40 load = 1;
        #20 load  = 0;
        #20 ShiftEn = 1;
        #80 ParallelIn = 4'b1001;
        #20 load  = 1;
        #20 load  = 0;
        #55 load  = 1;
        #20 load  = 0;
    end
endmodule
