`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 17:05:09
// Design Name: 
// Module Name: jk_ff
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


module jk_ff(
    input j,k,CP,reset,
    output reg y,ybar
    );
    always @(reset)
    begin
        if(reset == 1)
        y = 0;
        ybar = 1;
    end
    always @(negedge CP)
    begin 
        y = (j&(~y))|((~k)&y);
        ybar = ~y;
    end
endmodule
