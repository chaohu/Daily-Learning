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
    input Clk,ShiftIn,out,ShiftEn,
    output ShiftOut, 
    output [3:0] RegContent,
    output reg [3:0] ParallelOut
    );
    reg [3:0] shift_reg;
    initial
    begin
        shift_reg = 4'b1010;
    end
    
    always @(posedge Clk)
        if(out)
            ParallelOut <= shift_reg;
        else if (ShiftEn)
            shift_reg <= {shift_reg[2:0], ShiftIn};
    assign ShiftOut = shift_reg[3];
    assign RegContent = shift_reg;
endmodule