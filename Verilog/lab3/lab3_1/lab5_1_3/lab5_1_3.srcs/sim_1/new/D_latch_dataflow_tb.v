`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/27 21:18:42
// Design Name: 
// Module Name: D_latch_dataflow_tb
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


module D_latch_dataflow_tb(

    );
    reg D,Enable;
    wire Q,Qbar;
    
    D_latch_dataflow dut(D,Enable,Q,Qbar);
    
    initial
    begin
        D = 0;Enable = 0;
        #10 D = 1;
        #10 Enable =1;
        #10 D = 0;
        #10 D = 1;
        #10 Enable = 0;
        #10 D = 0;
        #10 D = 1;
        #10 D = 0;
        #10 Enable = 1;
        #10 D = 1;
        #10 D = 0;
    end
endmodule
