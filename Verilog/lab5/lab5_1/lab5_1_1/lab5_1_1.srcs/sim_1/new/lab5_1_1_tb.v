`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/10 23:40:23
// Design Name: 
// Module Name: lab5_1_1_tb
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


module lab5_1_1_tb(

    );
    reg ain,clk,reset;
    wire [3:0] count;
    wire yout;
    
    lab5_1_1 dut(ain,clk,reset,count,yout);
    initial
    begin
        for(clk = 0;clk >= 0;clk = clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        reset = 1;ain = 0;
        #20 reset = 0;
        #20 ain = 1;
        #20 ain = 0;
        #60 ain = 1;
        #40 ain = 0;
        #20 ain = 1;
        #10 reset = 1;
        #10 reset = 0;
        #10 ain = 0;
        #30 ain = 1;
    end
    
endmodule
