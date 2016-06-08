`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/07 10:00:04
// Design Name: 
// Module Name: lab6_1_4
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


module lab6_1_4(
    input Clk,ShiftIn,load,ShiftEn,
    input [3:0] ParallelIn,
    output ShiftOut, 
    output [3:0] RegContent
    );
    reg [3:0] shift_reg;
    always @(posedge Clk)
        if(load)
            shift_reg <= ParallelIn;
        else if (ShiftEn)
            shift_reg <= {shift_reg[2:0], ShiftIn};
    assign ShiftOut = shift_reg[3];
    assign RegContent = shift_reg;
endmodule