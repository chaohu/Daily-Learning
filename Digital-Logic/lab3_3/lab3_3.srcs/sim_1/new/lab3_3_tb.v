`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/03 10:59:17
// Design Name: 
// Module Name: lab3_3_tb
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


module lab3_3_tb(

    );
    reg INPUT,CLK;
    wire Q1,N1,OUT;
    lab3_3 dut(INPUT,CLK,Q1,N1,OUT);
    
    initial
    begin
        for(CLK = 0;CLK >= 0;CLK = CLK + 1)
        begin
            #10;
        end
    end
    initial
    begin
        INPUT = 1;
        #40 INPUT = 0;
        #20 INPUT = 1;
        #20 INPUT = 0;
    end
        
    
endmodule
