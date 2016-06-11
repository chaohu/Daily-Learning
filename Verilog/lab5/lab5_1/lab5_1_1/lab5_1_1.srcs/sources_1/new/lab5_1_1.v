`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/10 16:14:27
// Design Name: 
// Module Name: lab5_1_1
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


module lab5_1_1(
    input ain,clk,reset,
    output reg [3:0] count,
    output reg yout
    );
    reg [1:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3;
    initial
    begin
        nextstate = S2;
    end
    always @(posedge clk)
    begin
    if(reset)
    begin
        count = 4'b0000;
        state  = S0;
    end
    else
    begin
        if(ain)
        begin
            if(count == 15)
            begin
                count = 0;
                state = S0;
            end
            else
            begin
                count = count + 1;
                state = nextstate;
            end
        end
    end
    end
        
    always @(state or ain or reset)
    begin
        yout = 1'b0;
        case(state)
        S0: if((~ain) & (~reset))
            yout = 1;
        S1: if(ain & (~reset))
            yout = 1;
        default: yout = 1'b0;
        endcase
    end
    always @(state or ain)
    begin
        case(state)
        S0: 
        begin
            if(ain)
                nextstate = S2;
            else
                nextstate = S0;
        end
        S1:
        begin
            if(ain)
                nextstate = S2;
            else
                nextstate = S1;
        end
        S2:
        begin
            if(ain)
                nextstate = S3;
            else
                nextstate = S2;
        end
        S3:
        begin
            if(ain)
                nextstate = S1;
            else
                nextstate = S3;
        end    
        endcase
    end
    
endmodule
