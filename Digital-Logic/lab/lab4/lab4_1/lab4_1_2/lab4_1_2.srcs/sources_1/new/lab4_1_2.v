`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 19:55:01
// Design Name: 
// Module Name: lab4_1_2
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


module lab4_1_2(
    input CP,
    output wire Qd,Qc,Qb,Qa,
    output reg Z
    );
    reg LD,CLR;
    wire Qcc;
    fb_count cou1(CP,1,0,0,1,0,LD,CLR,Qd,Qc,Qb,Qa,Qcc);
    initial
    begin
        LD = 0;CLR = 1;
        #1 LD = 1;
    end
    always @(posedge CP)
    begin
        CLR = ~(Qc & Qb & Qa);
        Z = Qc & Qb & Qa;
    end
    
endmodule
