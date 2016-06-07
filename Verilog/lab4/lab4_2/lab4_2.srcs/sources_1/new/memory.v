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
    input [7:0] A,
    output [7:0] Z
    );
    reg [7:0] MEM [255:0];    // defining 255x7 ROM
    assign Z = MEM [A];        // reading ROM content at the address ROM_addr
    initial $readmemb  ("mem_data.txt", MEM, 0, 7);
endmodule
