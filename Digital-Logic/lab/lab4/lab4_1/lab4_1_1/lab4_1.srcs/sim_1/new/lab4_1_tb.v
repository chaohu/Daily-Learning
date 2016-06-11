`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 17:42:40
// Design Name: 
// Module Name: lab4_1_tb
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


module lab4_1_tb(

    );
    reg CP,M,D,C,B,A,LD,CLR;
    wire Qd,Qc,Qb,Qa,Qcc;
    lab4_1 dut(CP,M,D,C,B,A,LD,CLR,Qd,Qc,Qb,Qa,Qcc);
    initial
    begin
        for(CP = 0;CP >= 0;CP = CP + 1)
        begin
            #5;
        end
    end
    initial
    begin
        LD = 0;D = 0;C = 1;B = 0;A = 1;CLR = 1;M = 1;
        #10 LD = 1;
    end
endmodule
