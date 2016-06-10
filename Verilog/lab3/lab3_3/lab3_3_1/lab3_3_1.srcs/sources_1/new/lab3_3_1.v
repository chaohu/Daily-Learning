`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/08 15:39:47
// Design Name: 
// Module Name: lab3_3_1
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


module lab3_3_1(
    input a,b,
    output reg lt,gt,eq
    );
    reg [1:0] com;
    reg [2:0] ROM [2:0];
    initial $readmemb ("/home/huchao/Daily-Learning/Verilog/lab3/lab3_3/lab3_3_1/com_data.txt", ROM, 0, 2);
    always @(a or b)
    begin
        begin
        if(a > b)
            com = 0;
        else if(a == b)
            com = 1;
        else if(a < b)
            com = 2;
        end
        {lt,gt,eq} = ROM[com];
    end
endmodule
