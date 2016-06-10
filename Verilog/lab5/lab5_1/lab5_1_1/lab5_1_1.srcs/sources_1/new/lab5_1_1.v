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
    input [3:0] count,
    output reg yout
    );
    reg state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,s3 = 3;
    always @(posedge clk)
    if(reset)
        count <= 0;
    else
        count = count + 1;
        
    always @(state or ain or reset)
    begin
        yout = 1'b0;
        case(state)
        S0: if((~ain) & (~reset))
            yout = 1;
        S1: if(ain & (~reset))
            yout = 1;
        default:  
        endcase
    end
    always @(state or ain)
    begin
        case(state)
        S0: 
        if(ain)
            nextstate = S2;
        else
            nextstate = S0;
        S1:
        if(ain)
            nextstate = S0;
        else
            nextstate = S1;
            
            
        endcase
    end
    
endmodule
