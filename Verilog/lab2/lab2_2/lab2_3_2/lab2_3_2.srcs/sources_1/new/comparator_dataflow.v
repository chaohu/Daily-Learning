`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 15:30:40
// Design Name: 
// Module Name: comparator_dataflow
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


module comparator_dataflow(
    input [3:0] v,
    input cin,
    output z,
    output [3:0] s2
    );
    wire [3:0] m;
    
    assign z = ((cin ==1) | (v > 9)) ? 1 : 0;
    assign m = (v > 9) ? (v-10) : v;
    assign s2 = (cin == 1) ? (m+6) : m;
    
endmodule
