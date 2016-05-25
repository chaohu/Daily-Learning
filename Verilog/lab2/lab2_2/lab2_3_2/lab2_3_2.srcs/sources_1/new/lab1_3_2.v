`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 14:39:20
// Design Name: 
// Module Name: lab1_3_2
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


module lab1_3_2(
    input [3:0] x,y,
    output wire cout,
    output wire [6:0] seg
    );
    
    wire [1:0] cin1,carr;
    wire [3:0] s;
    wire up;
    assign #1 cin1[0] = 0;
    
    fulladder_dataflow dut1(x[0],y[0],cin1[0],s[0],carr[0]);
    fulladder_dataflow dut2(x[1],y[1],carr[0],s[1],cin1[1]);
    fulladder_dataflow dut3(x[2],y[2],cin1[1],s[2],carr[1]);
    fulladder_dataflow dut4(x[3],y[3],carr[1],s[3],up);
    
    bcdto7segment_dataflow dut5(s,seg);
    
endmodule
