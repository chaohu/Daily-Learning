`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 15:49:03
// Design Name: 
// Module Name: lab5_2_1_tb
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


module lab5_2_1_tb(

    );
    reg in,reset,clk;
    wire z;
    lab5_2_1 dut(in,reset,clk,z);
    initial
    begin
        for(clk = 0;clk >= 0;clk = clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        reset = 1;in = 0;
        #2 reset = 0;
        #8 in = 1;
        #10 in = 0;
        #10 in = 1;
        #20 in = 0;
        #10 in = 1;
        #30 in = 0;
        #10 in = 1;
    end
endmodule
