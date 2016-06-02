`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/02 21:10:01
// Design Name: 
// Module Name: lab3_2_tb
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


module lab3_2_tb(

    );
    reg x;
    wire q1,q2,q3,q4,z;
    
    lab3_2 dut(x,q1,q2,q3,q4,z);
    
    initial
    begin
        for (x=0; x >= 0; x=x+1)
        begin
            #10;
        end
    end
endmodule
