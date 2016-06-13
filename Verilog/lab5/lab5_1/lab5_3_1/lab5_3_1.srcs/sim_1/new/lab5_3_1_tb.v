`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 12:17:32
// Design Name: 
// Module Name: lab5_3_1_tb
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


module lab5_3_1_tb(

    );
    reg ain,reset,clk;
    wire [2:0] yout;
    wire [2:0] state,nextstate;
    lab5_3_1 dut(ain,reset,clk,yout,state,nextstate);
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
        #2 reset = 0; 
        #15 ain = 1;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
        #10 ain = 1;
        #10 ain = 0;
    end
endmodule
