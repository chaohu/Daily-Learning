`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/24 09:36:13
// Design Name: 
// Module Name: CLA
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


module CLA(
    input cin,
    input [3:0] p,g,
    output [2:0] c,
    output cout
    );
    assign c[0] = (p[0]&cin)|g[0],
                c[1] = (p[1]&p[0]&cin)|(p[1]&g[0])|g[1],
                c[2] = (p[2]&p[1]&p[0]&cin)|(p[2]&p[1]&g[0])|(p[2]&g[1])|g[2],
                cout = (p[3]&p[2]&p[1]&p[0]&cin)|(p[3]&p[2]&p[1]&g[0])|(p[3]&p[2]&g[1])|(p[3]&g[2])|g[3];
endmodule
