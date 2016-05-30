`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/27 20:31:48
// Design Name: 
// Module Name: SR_latch_dataflow_tb
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


module SR_latch_dataflow_tb(

    );
    reg R,S;
    wire Q,Qbar;
    
    SR_latch_dataflow dut(R,S,Q,Qbar);
    
    initial
    begin
        R = 0;S = 0;
        #10 S = 1;
        #10 S = 0;
        #10 R = 1;
        #10 R = 0;S = 1;
        #10 R = 1;S = 0;
        #10 R = 0;S = 1;
        #10 R = 1;S = 0;
        #10 S = 1;
    end
endmodule
