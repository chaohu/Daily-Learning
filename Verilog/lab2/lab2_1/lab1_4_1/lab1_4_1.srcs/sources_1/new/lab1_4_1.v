`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 16:07:10
// Design Name: 
// Module Name: lab1_4_1
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


module lab1_4_1(u,y,w,s0,s1,m);
    input u,y,w,s0,s1;
    output wire m;
    wire med;
    
    lab1_1_1 dut1(.x(u),.y(y),.s(s0),.m(med));
    lab1_1_1 dut2(.x(med),.y(w),.s(s1),.m(m));
    
endmodule
