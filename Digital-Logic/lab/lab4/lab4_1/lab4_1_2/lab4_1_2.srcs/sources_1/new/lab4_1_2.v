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
    input CP,M,
    output wire Qd,Qc,Qb,Qa,
    output reg Z
    );
    reg LD;
    wire Qcc;
    fb_count cou1(CP,M,0,0,1,0,LD,1,Qd,Qc,Qb,Qa,Qcc);
    initial
    begin
        LD = 0;
        #2 LD = 1;
    end
    always @(Qd or Qc or Qb or Qa)
    begin
            LD = ~(Qd & (~Qc) & Qb & (~Qa));
            Z = (~Qd) & (~Qc) & Qb & (~Qa);
    end
    
endmodule
