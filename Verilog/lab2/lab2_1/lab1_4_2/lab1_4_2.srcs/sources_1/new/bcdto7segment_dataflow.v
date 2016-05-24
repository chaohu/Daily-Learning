`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 18:32:41
// Design Name: 
// Module Name: bcdto7segment_dataflow
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


module bcdto7segment_dataflow(
    input [3:0] x,
    output [3:0] an,
    output [6:0] seg
    );
    
    assign #2 an = x;
    assign #1 seg[6] = (x[2]&(~x[1])&(~x[0]))|((~x[3])&(~x[2])&(~x[1])&x[0]);
    assign #1 seg[5] = (x[2]&(~x[1])&x[0])|(x[2]&x[1]&(~x[0]));
    assign #1 seg[4] = (~x[3])&(~x[2])&x[1]&(~x[0]);
    assign #1 seg[3] = (x[2]&(~x[1])&(~x[0]))|(x[2]&x[1]&x[0])|((~x[3])&(~x[2])&(~x[1])&x[0]);
    assign #1 seg[2] = (x[2]&(~x[1]))|x[0];
    assign #1 seg[1] = (x[1]&x[0])|((~x[3])&(~x[2])&x[0])|((~x[3])&(~x[2])&x[1]);
    assign #1 seg[0] = ((~x[3])&(~x[2])&(~x[1]))|(x[2]&x[1]&x[0]);
    
endmodule
