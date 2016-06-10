`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/09 13:16:30
// Design Name: 
// Module Name: lab3_3_2
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


module lab3_3_2(
    input [1:0] a,b,
    output reg [3:0] z
    );
    reg [3:0] addr;
    reg [3:0] ROM [15:0];
    initial $readmemb ("/home/huchao/Daily-Learning/Verilog/lab3/lab3_3/lab3_3_2/data.txt", ROM, 0, 15);
    always @(a or b)
    begin
        addr[0] = a[0] & b[0];
        addr[1] = (a[1] & b[0])^(a[0] & b[1]);
        addr[2] = (a[1] & b[1])^( (a[1] & b[0])&(a[0] & b[1]));
        addr[3] = (a[1] & b[1])&( (a[1] & b[0])&(a[0] & b[1]));
        z = ROM[addr];
    end
endmodule
