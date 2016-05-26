`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 16:07:35
// Design Name: 
// Module Name: lab3_2_1
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


module lab3_2_1(
    input [7:0] v,
    input en_in_n,
    output reg [2:0] y,
    output reg en_out,gs
    );

    always
        @(v or en_in_n)
            if(en_in_n == 1)
                begin
                y=7;
                en_out = 1;
                gs = 1;
                end
            else if(en_in_n == 0&&v == 255)
                begin
                y = 7;
                en_out = 0;
                gs = 1;
                end
            else if(en_in_n == 0&&v[7] == 0)
                begin
                y = 0;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[6] == 0)
                begin
                y = 1;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[5] == 0)
                begin
                y = 2;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[4] == 0)
                begin
                y = 3;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[3] == 0)
                begin
                y = 4;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[2] == 0)
                begin
                y = 5;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[1] == 0)
                begin
                y = 6;
                en_out = 1;
                gs = 0;
                end
            else if(en_in_n == 0&&v[0] == 0)
                begin
                y = 7;
                en_out = 1;
                gs = 0;
                end
endmodule
