`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/27 21:01:32
// Design Name: 
// Module Name: gate_SR_latch_tb
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


module gate_SR_latch_tb(

    );
    reg R,S,Enable;
    wire Q,Qbar;
    
    gate_SR_latch dut(R,S,Enable,Q,Qbar);
    
    initial
    begin
        R = 0;S = 0;Enable = 0;
        #10 S = 1;
        #10 Enable = 1;
        #10 S = 0;
        #10 R = 1;
        #10 Enable = 0;
        #10 R = 0;S = 1;
        #10 R = 1;S = 0;
        #10 R = 0;S = 1;
        #10 Enable = 1;
        #10 R = 1;S = 0;
    end
endmodule
