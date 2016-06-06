`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 17:24:02
// Design Name: 
// Module Name: check101_tb
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


module check101_tb(

    );
    reg x,CP,reset;
    wire z;
    check101 dut(x,CP,reset,z);
    initial
    begin
        for(CP = 1;CP >= 0;CP = CP + 1)
        begin
            #5;
        end
    end
        
    initial
    begin
        reset = 0;x = 0;
        #1 reset = 1;
        #1 reset = 0;
        #18 x = 1;
        #10 x = 0;
        #10 x = 1;
        #10 x = 0;
        #10 x = 1;
        #20 x = 0;
        #10 x = 1;
        #10 x = 0;
    end
        
endmodule
