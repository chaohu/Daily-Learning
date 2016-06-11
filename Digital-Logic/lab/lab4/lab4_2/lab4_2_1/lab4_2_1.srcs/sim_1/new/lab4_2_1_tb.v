`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 21:53:34
// Design Name: 
// Module Name: lab4_2_1_tb
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


module lab4_2_1_tb(

    );
    reg [1:0] A,B;
    wire F1,F2,F3;
    integer i,j;
    lab4_2_1 dut(A,B,F1,F2,F3);
    initial
    begin
        A = 0;B = 0;
        for(i = 0;i <= 3;i = i + 1)
        begin
            for(j = 0;j <= 3;j = j + 1)
            begin
                #10;
                B = B + 1;
            end
            A = A + 1;
        end
    end
endmodule
