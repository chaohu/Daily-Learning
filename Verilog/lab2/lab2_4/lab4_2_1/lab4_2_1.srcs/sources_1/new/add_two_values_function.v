`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 18:01:56
// Design Name: 
// Module Name: add_two_values_function
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


module add_two_values_function(
    input [3:0] x,y,
    output reg [4:0] z
    );
    function [4:0] add_two_values;
        input [3:0] x,y;
        begin
            add_two_values = x+y;
        end
    endfunction
    always
        @(x or y)
        begin
            z = add_two_values(x,y);
        end 
    
endmodule
