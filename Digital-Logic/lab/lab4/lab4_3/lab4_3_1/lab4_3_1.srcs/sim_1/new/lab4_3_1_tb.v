`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 22:32:41
// Design Name: 
// Module Name: lab4_3_1_tb
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


module lab4_3_1_tb(

    );
    reg m,clk;
    wire [3:0] Z;
    lab4_3_1 dut(m,clk,Z);
    initial
    begin
        for(clk = 0;clk >= 0;clk = clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        m = 1;
        #300 m = 0;
    end
endmodule
