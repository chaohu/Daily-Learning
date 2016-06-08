`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/08 16:01:57
// Design Name: 
// Module Name: lab3_3_1_tb
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


module lab3_3_1_tb(

    );
    reg a,b;
    wire lt,gt,eq;
    lab3_3_1 dut(a,b,lt,gt,eq);
    initial
    begin
        a = 0;b = 0;
        #10 a = 1;
        #10 b = 1;
        #10 a = 0;b = 0;
        #10 b = 1;
    end
endmodule
