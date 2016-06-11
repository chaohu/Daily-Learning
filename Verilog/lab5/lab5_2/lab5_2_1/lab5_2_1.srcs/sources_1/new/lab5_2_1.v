`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 15:27:34
// Design Name: 
// Module Name: lab5_2_1
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


module lab5_2_1(
    input in,reset,clk,
    output reg z
    );
    reg [1:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3;
    always @(posedge clk or posedge reset)
    if(reset)
        state = S0;
    else
        state = nextstate;
        
    always @(state)
    begin
        case(state)
            S0: z = 0;
            S1: z = 0;
            S2: z = 0;
            S3: z = 1;
        endcase
    end
    always @(state or in)
    begin
        case(state)
            S0: 
            begin
                if(in)
                    nextstate = S1;
                else
                    nextstate = S0;
            end
            S1: 
            begin
                if(in)
                    nextstate = S2;
                else
                    nextstate = S1;
            end
            S2: 
            begin
                if(in)
                    nextstate = S3;
                else
                    nextstate = S2;
            end
            S3: 
            begin
                if(in)
                    nextstate = S1;
                else
                    nextstate = S3;
            end
        endcase
    end
endmodule
