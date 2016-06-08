`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 11:46:57
// Design Name: 
// Module Name: lab6_2_2_tb
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


module lab6_2_2_tb(

    );
    reg Enable,Clk;
    wire Z;
    lab6_2_2 dut(Enable,Clk,Z);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        Enable = 0;
        #20 Enable = 1;
        #80 Enable = 0;
        #80 Enable = 1;
    end
endmodule
