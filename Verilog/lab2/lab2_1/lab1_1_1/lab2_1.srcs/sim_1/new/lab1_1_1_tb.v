`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/23 20:30:29
// Design Name: 
// Module Name: lab1_1_1_tb
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


module lab1_1_1_tb(
    );
    reg x, y, s;
    wire m;
    
    lab1_1_1 dut(.x(x),.y(y),.s(s),.m(m));
 
    initial
    begin
      x = 0; y = 0; s = 0;
      #10 s = 1;
      #10 y = 1; s = 0;
      #10 s = 1;
      #10 x = 1; y = 0; s = 0;
      #10 s = 1;
      #10 y = 1; s = 0;
      #10 s = 1;
    #20;
    end
    
endmodule
