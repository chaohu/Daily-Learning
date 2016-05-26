`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 18:12:49
// Design Name: 
// Module Name: calc_ones_function
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


module calc_ones_function(
    input [7:0] x,
    output reg [2:0] z
    );
    task calc_ones;
        input [7:0] x;
        output reg [2:0] z;
        begin
            z = calc_ones_f(x);
        end
    endtask
    function [2:0] calc_ones_f;
        input [7:0] x;
        begin
            calc_ones_f = x[7]+x[6]+x[5]+x[4]+x[3]+x[2]+x[1]+x[0];
         end
     endfunction
     always
        @(x)
        begin
            calc_ones(x,z);
        end
        
endmodule
