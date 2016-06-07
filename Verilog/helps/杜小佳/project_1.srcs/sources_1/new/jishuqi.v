`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 16:38:29
// Design Name: 
// Module Name: erjinzhimosijishuqi
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


module jishuqi(input x,input clk,output Q1,output Q2,output z);
wire XOR1;
JK W1(1,1,clk,Q1,Qbar1);
xor S1(XOR1,x,Q1);
JK W2(XOR1,XOR1,clk,Q2,Qbar2);
assign z= (x & Qbar2 & Qbar1)| ((~x) & Q1 & Q2);

endmodule

module JK(input j,input k,input clk,output reg Q,output reg Qbar);
   initial
   begin
   Q=0;
   Qbar=1;
   end
   
   always @(negedge clk)
   begin
   Q=(j & Qbar)|(~k & Q);  //JK´¥·¢Æ÷¹¦ÄÜ
   Qbar=~Q;
   end
   
endmodule

