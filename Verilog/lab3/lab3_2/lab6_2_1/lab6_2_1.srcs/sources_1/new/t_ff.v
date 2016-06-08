`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 10:59:21
// Design Name: 
// Module Name: t_ff
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


module t_ff(
    input t,Clk,Clear,
    output reg q,qbar
    );
    always @(posedge Clk or negedge Clear)
    begin
        if(Clear == 0)
        begin
            q <= 0;
            qbar <= 1;
        end
        else if(Clk == 1)
        begin
            q = q ^ t;
            qbar = ~q;
        end
    end
endmodule
