`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 20:09:55
// Design Name: 
// Module Name: lab4_3_2_tb
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


module lab4_3_2_tb(

    );
    reg a,g1,g2;
    lab4_3_2 dut(a,g1,g2);
    initial
    begin
        a = 0;g1 = 0;g2 = 1;
        #40 a = 1;
        #20 g1 = 1;
        #20 g2 = 0;
        #20 a = 0;
        #20 g1 = 0;
        #20 g2 = 1;
    end
    
endmodule
