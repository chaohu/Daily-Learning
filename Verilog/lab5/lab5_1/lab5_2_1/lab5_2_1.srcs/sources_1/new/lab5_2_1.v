`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 11:02:56
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
    input [1:0] ain,
    input clk,reset,
    output reg yout
    );
    reg [2:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3,S4 = 4,S5 = 5,S6 = 6;
    always @(posedge clk or posedge reset)
    if(reset)
    begin
        state <= S0;
        yout <= 0;
    end
    else
        state <= nextstate;
        
    always @(state)
    begin
        case(state)
            S0:yout = yout;
            S1:yout = yout;
            S2:yout = yout;
            S3:yout = yout;
            S4:yout = 0;
            S5:yout = 1;
            S6:yout = ~yout;
        endcase
    end
    always @(state or ain)
    begin
        case(state)
            S0:
            begin
                if(ain == 0)
                    nextstate = S0;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S1:
            begin
                if(ain == 0)
                    nextstate = S4;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S2:
            begin
                if(ain == 0)
                    nextstate = S5;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S3:
            begin
                if(ain == 0)
                    nextstate = S6;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S4:
            begin
                if(ain == 0)
                    nextstate = S0;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S5:
            begin
                if(ain == 0)
                    nextstate = S0;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
            S6:
            begin
                if(ain == 0)
                    nextstate = S0;
                else if(ain == 1)
                    nextstate = S1;
                else if(ain == 3)
                    nextstate = S2;
                else
                    nextstate = S3;
            end
        endcase
    end
endmodule
