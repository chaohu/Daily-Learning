`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 17:05:18
// Design Name: 
// Module Name: lab3_2_1_tb
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


module lab3_2_1_tb(

    );
    reg [7:0] v;
    reg en_in_n;
    wire [2:0] y;
    wire en_out,gs;
    
    integer i;
    
    lab3_2_1 dut(v,en_in_n,y,en_out,gs);
    
    initial
    begin
        for (i=0; i < 511; i=i+1)
        begin
             #2 {en_in_n,v} = i;
        end
    end
      
endmodule
