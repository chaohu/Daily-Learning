`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 20:24:38
// Design Name: 
// Module Name: lab2_4_1
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


module lab2_4_1(
    input [3:0] a,b,
    input cin,
    output wire cout,
    output [3:0] s
    );
    wire [3:0] p,g;
    wire [2:0] c;
    assign p[0] = a[0]^b[0],
                p[1] = a[1]^b[1],
                p[2] = a[2]^b[2],
                p[3] = a[3]^b[3],
                g[0] = a[0]&b[0],
                g[1] = a[1]&b[1],
                g[2] = a[2]&b[2],
                g[3] = a[3]&b[3];
    assign c[0] = (p[0]&cin)|g[0],
                c[1] = (p[1]&p[0]&cin)|(p[1]&g[0])|g[1],
                c[2] = (p[2]&p[1]&p[0]&cin)|(p[2]&p[1]&g[0])|(p[2]&g[1])|g[2],
                cout = (p[3]&p[2]&p[1]&p[0]&cin)|(p[3]&p[2]&p[1]&g[0])|(p[3]&p[2]&g[1])|(p[3]&g[2])|g[3];
    assign s[0] = p[0]^cin,
                s[1] = p[1]^c[0],
                s[2] = p[2]^c[1],
                s[3] = p[3]^c[2];
    
endmodule
