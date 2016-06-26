`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/24 09:30:14
// Design Name: 
// Module Name: fulladder_dataflow
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


module fulladder_dataflow(
    input a,b,cin,
    output s,p,g
    );
    assign s = a ^ b ^ cin;
    assign p = a ^ b;
    assign g = a & b;
endmodule
