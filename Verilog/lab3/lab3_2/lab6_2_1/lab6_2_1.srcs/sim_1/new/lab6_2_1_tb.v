`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 11:17:23
// Design Name: 
// Module Name: lab6_2_1_tb
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


module lab6_2_1_tb(

    );
    reg Clk,Enable,Clear;
    wire z;
    wire A1,A2,A3,Q1,Q1bar,Q2,Q2bar,Q3,Q3bar,Q4bar;
    lab6_2_1 dut(Enable,Clk,Clear,z,A1,A2,A3,Q1,Q1bar,Q2,Q2bar,Q3,Q3bar,Q4bar);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        Enable = 0;Clear = 0;
        #20 Enable = 1;
        #20 Clear = 1;
        #80 Enable = 0;
        #80 Enable = 1;
    end
endmodule
