`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 19:48:59
// Design Name: 
// Module Name: lab5_2_2_tb
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


module lab5_2_2_tb(

    );
    reg Clock,D;
    wire Qa,Qb,Qc;
    lab5_2_2 dut(Clock,D,Qa,Qb,Qc);
    
    initial
    begin
        for(Clock = 0;Clock >= 0;Clock=Clock+1)
        begin
            #60;
        end
    end
    
    initial
    begin
        D = 0;
        #50 D = 1;
        #20 D = 0;
        #10 D = 1;
        #20 D = 0;
        #30 D = 1;
        #20 D = 0;
        #10 D = 1;
        #10 D = 0;
        #20 D = 1;
        #10 D = 0;
        #10 D = 1;
        #40 D = 0;
    end
endmodule
