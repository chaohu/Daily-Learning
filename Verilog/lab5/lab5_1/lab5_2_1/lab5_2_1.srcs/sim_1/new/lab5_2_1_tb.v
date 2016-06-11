`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 11:25:26
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
    reg [1:0] ain;
    reg clk,reset;
    wire yout;
    lab5_2_1 dut(ain,clk,reset,yout);
    initial
    begin
        for(clk = 0;clk >= 0;clk = clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        ain = 0;reset = 1;
        #20 reset = 0;
        #20 ain = 3;
        #10 ain = 2;
        #10 ain = 0;
        #20 ain = 2;
        #10 ain = 0;
        #10 ain = 3;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
        #10 ain = 2;
        #10 ain = 3;
        #10 ain = 0;
        #10 reset = 1;
        #10 reset = 0;
        #10 ain = 2;
    end
endmodule
