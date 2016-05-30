`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/27 21:31:31
// Design Name: 
// Module Name: D_ff_behavior_tb
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


module D_ff_behavior_tb(

    );
    reg Clk,D;
    wire Q;
    D_ff_behavior dut(D,Clk,Q);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk=Clk+1)
        begin
            #10;
        end
    end
    initial
    begin
        D = 0;
        #30 D = 1;
        #30 D = 0;
        #40 D = 1;
        #20 D = 0;
    end
endmodule
