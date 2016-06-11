`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 22:07:06
// Design Name: 
// Module Name: lab4_3_1
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


module lab4_3_1(
    input m,clk,
    output reg [3:0] Z
    );
    reg n;
    reg [1:0] state,nextstate;
    parameter S0 = 2'b00,S1 = 2'b01,S2 = 2'b11,S3 = 2'b10;
    initial
    begin
        state = S0;
        n = 0;
    end
    always @(posedge clk)
    begin
        if(n == 10000000)
        begin
            state = nextstate;
            n = 0;
        end
        else
        begin
            n = n + 1;
        end
    end
    always @(state)
    begin
        case(state)
        S0:Z = 4'b0001;
        S1:Z = 4'b0010;
        S2:Z = 4'b0100;
        S3:Z = 4'b1000;
        endcase
    end
    always @(state)
    begin
        if(m)
        begin
            case(state)
            S0: nextstate = S1;
            S1: nextstate = S2;
            S2: nextstate = S3;
            S3: nextstate = S0;
            endcase
        end
        else
        begin
            case(state)
            S0: nextstate = S3;
            S1: nextstate = S0;
            S2: nextstate = S1;
            S3: nextstate = S2;
            endcase
        end
    end
endmodule
