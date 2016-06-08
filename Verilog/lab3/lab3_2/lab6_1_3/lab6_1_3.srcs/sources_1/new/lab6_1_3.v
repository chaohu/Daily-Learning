`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 09:41:10
// Design Name: 
// Module Name: lab6_1_3
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


module lab6_1_3(input Clk, input ShiftIn, output ShiftOut);
    reg [2:0] shift_reg;
    initial
    begin
        shift_reg = 3'b101;
    end
    always @(posedge Clk)
        shift_reg <= {shift_reg[1:0], ShiftIn};
    assign ShiftOut = shift_reg[2];
endmodule
