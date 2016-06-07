`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 17:06:26
// Design Name: 
// Module Name: jishuqi_tb
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


module jishuqi_tb();
reg x,clk;
wire Q1,Q2,z;
jishuqi DUT(.x(x),.clk(clk),.Q1(Q1),.Q2(Q2),.z(z));
initial 
   begin
   x=0;
   clk=0;
   #5 clk=1;x=0;
   #5 clk=0;
   #5 clk=1;x=0;
   #5 clk=0;
   #5 clk=1;x=1;
   #5 clk=0;
   #5 clk=1;x=0;
   #5 clk=0;
   #5 clk=1;x=0;
   #5 clk=0;
   #5 clk=1;x=0;
   #5 clk=0;
   #5 clk=1;x=1;
   end


endmodule
