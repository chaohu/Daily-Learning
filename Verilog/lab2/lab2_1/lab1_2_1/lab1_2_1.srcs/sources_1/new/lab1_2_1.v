`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 11:06:04
// Design Name: 
// Module Name: lab1_2_1
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


module lab1_2_1(
    x_in,
    y_out
    );
    input [7:0] x_in;
    output [7:0] y_out;
    
    assign #1 y_out[0] = x_in[0];
    assign #1 y_out[1] = x_in[1];
    assign #1 y_out[2] = x_in[2];
    assign #1 y_out[3] = x_in[3];
    assign #1 y_out[4] = x_in[4];
    assign #1 y_out[5] = x_in[5];
    assign #1 y_out[6] = x_in[6];
    assign #1 y_out[7] = x_in[7];
endmodule
