`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 20:36:21
// Design Name: 
// Module Name: lab4_1_2_tb
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


module lab4_1_2_tb(

    );
    reg CP,M;
    wire Qd,Qc,Qb,Qa,Z;
    lab4_1_2 dut(CP,M,Qd,Qc,Qb,Qa,Z);
    initial
    begin
        M = 1;
        #200 M = 0;
    end
    initial
    begin
        for(CP = 0;CP >= 0;CP = CP + 1)
        begin
            #5;
        end
    end
endmodule
