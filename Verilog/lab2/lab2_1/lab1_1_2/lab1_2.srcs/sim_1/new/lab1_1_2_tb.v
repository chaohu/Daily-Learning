`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/23 21:37:45
// Design Name: 
// Module Name: lab1_1_2_tb
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


module lab1_1_2_tb(

    );
    reg [1:0] x, y;
    reg s;
    wire [1:0] m;
    
    lab1_1_2 dut(.x(x),.y(y),.s(s),.m(m));
 
    initial
    begin
      x = 0; y = 0; s = 0;
      #10 x = 1;
      #10 y = 1;
      #10 x = 3; y = 0;
      #10 x = 2; y = 3;
      #10 s = 1;
      #10 x = 1;
      #10 y = 1;
      #10 x = 3; y = 0;
      #10 x = 2; y = 3;
    #20;
    end
endmodule
