`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:56:31
// Design Name: 
// Module Name: memory
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


module memory(
    input [width-1:0] A,
    output [width-1:0] Z
    );
    parameter width = 8;
    reg [width-1:0] MEM [2**width:0];    // defining 255x7 ROM
    assign Z = MEM [A];        // reading ROM content at the address ROM_addr
    initial $readmemb  ("mem_data.txt", MEM, 0, width-1);
endmodule
