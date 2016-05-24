`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 19:30:34
// Design Name: 
// Module Name: lab1_4_2_tb
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


module lab1_4_2_tb();
    reg [3:0] x;
    wire [3:0] an;
    wire [6:0] seg;
        
    bcdto7segment_dataflow dut(.x(x),.an(an),.seg(seg));
    
    initial
    begin
      x = 0;
      #10 x = 1;
      #10 x = 2;
      #10 x = 3;
      #10 x = 4;
      #10 x = 5;
      #10 x = 6;
      #10 x = 7;
      #10 x = 8;
      #10 x = 9;
    #20;
    end
endmodule
