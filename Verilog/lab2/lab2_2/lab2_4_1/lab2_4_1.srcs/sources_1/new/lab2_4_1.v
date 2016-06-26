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
    fulladder_dataflow fa0(a[0],b[0],cin,s[0],p[0],g[0]);
    fulladder_dataflow fa1(a[1],b[1],c[0],s[1],p[1],g[1]);
    fulladder_dataflow fa2(a[2],b[2],c[1],s[2],p[2],g[2]);
    fulladder_dataflow fa3(a[3],b[3],c[2],s[3],p[3],g[3]);
    CLA cla1(cin,p,g,c,cout);
endmodule
