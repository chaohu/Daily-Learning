`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/08 15:16:59
// Design Name: 
// Module Name: lab6_2_3
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


module lab6_2_3(
    input Clock,Enable,Clear,Load,
    output [3:0] Q
    );
    reg [3:0] count;
    wire cnt_done;
    assign cnt_done = ~| count;
    assign Q = count;
    always @(posedge Clock)
    if (Clear)
    begin
        count <= 0;
    end
    else if (Enable)
    begin
        if (Load | cnt_done)
        count <= 4'b1010;   // decimal 10
        else
        count <= count - 1;
    end
endmodule
