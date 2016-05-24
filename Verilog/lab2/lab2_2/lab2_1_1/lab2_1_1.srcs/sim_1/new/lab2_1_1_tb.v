`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 20:53:52
// Design Name: 
// Module Name: lab2_1_1_tb
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


module lab2_1_1_tb(

    );
    reg [3:0] x;
    wire [6:0] seg;
            
    lab2_1_1 dut(.num(x),.seg(seg));
        
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
