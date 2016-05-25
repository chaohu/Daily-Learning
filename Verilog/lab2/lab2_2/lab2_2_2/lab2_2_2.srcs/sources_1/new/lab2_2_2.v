`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 13:34:36
// Design Name: 
// Module Name: lab2_2_2
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


module lab2_2_2(
    input [3:0] x,
    output wire [4:0] y
    );
    wire z;
    wire [3:0] m;
    
    lab2_2_1_partA par(x,z,m);
    
    assign #1 y[4] = z;
    assign #1 y[3] = m[3];
    assign #1 y[2] = m[2];
    assign #1 y[1] = m[1];
    assign #1 y[0] = m[0];
    
endmodule
