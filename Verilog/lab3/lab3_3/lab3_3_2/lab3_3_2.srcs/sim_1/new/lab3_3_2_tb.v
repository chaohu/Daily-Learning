`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/09 13:22:01
// Design Name: 
// Module Name: lab3_3_2_tb
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


module lab3_3_2_tb(

    );
    reg [1:0] a,b;
    wire [3:0] z;
    lab3_3_2 dut(a,b,z);
    initial
    begin
        a = 0;b = 0;
        #20 a = 1;b = 0;
        #20 a = 3;b = 1;
        #20 a = 2;b = 3;
    end
endmodule
