`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/08 15:24:33
// Design Name: 
// Module Name: lab6_2_3_tb
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


module lab6_2_3_tb(

    );
    reg Clock,Enable,Clear,Load;
    wire [3:0] Q;
    lab6_2_3 dut(Clock,Enable,Clear,Load,Q);
    initial
    begin
        for(Clock = 0;Clock >= 0;Clock = Clock + 1)
        begin
            #5;
        end
    end
    initial
    begin
        Enable = 0;Clear = 0;Load = 0;
        #20 Enable = 1;
        #20 Clear = 1;
        #20 Clear = 0;
        #20 Load = 1;
        #10 Load = 0;
        #80 Enable = 0;
        #40 Enable = 1;
    end
    
        
endmodule
