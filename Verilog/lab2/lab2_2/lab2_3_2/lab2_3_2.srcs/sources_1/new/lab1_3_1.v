`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 14:43:03
// Design Name: 
// Module Name: lab1_3_1
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
    output s,cout
    );
    
    assign #1 s = a ^ b ^ cin;
    assign #1 cout = (a&b)|(a&cin)|(b&cin);
    
endmodule
