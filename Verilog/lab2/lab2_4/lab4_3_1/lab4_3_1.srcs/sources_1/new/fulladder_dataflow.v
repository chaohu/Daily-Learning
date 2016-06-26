`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 19:27:04
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
    output wire s,cout
    );
    
    assign #2 s = a ^ b ^ cin;
    assign #2 cout = (a&b)|(a&cin)|(b&cin);
    
endmodule
