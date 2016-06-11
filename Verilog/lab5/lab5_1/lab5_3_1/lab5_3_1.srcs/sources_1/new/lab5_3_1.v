`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 11:43:11
// Design Name: 
// Module Name: lab5_3_1
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


module lab5_3_1(
    input ain,reset,clk,
    output reg yout
    );
    reg [2:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 3,S3 = 5,S4 = 7,S5 = 2;
    reg [3:0] ROM [5:0];
    initial $readmemb ("/home/huchao/Daily-Learning/Verilog/lab5/lab5_1/lab5_3_1/data.txt", ROM, 0, 5);
    always @(posedge clk or posedge reset)
    if(reset)
    begin
        {state,yout} = ROM[0];
        yout = 0;
    end
    else
        state <= nextstate;
        
    always @(state or ain)
    begin
        case(state)
        S0: 
        begin
            if(ain)
                {nextstate,yout} = ROM[1];
            else
                nextstate = S0;
        end
        S1:
        begin
            if(ain)
                {nextstate,yout} = ROM[2];
            else
                nextstate = S1;
        end
        S2:
        begin
            if(ain)
                {nextstate,yout} = ROM[3];
            else
                nextstate = S2;
        end
        S3:
        begin
            if(ain)
                {nextstate,yout} = ROM[4];
            else
                nextstate = S3;
        end    
        S4:
        begin
            if(ain)
                {nextstate,yout} = ROM[5];
            else
                nextstate = S4;
        end    
        S5:
        begin
            if(ain)
                {nextstate,yout} = ROM[0];
            else
                nextstate = S5;
       end   
       endcase
    end

endmodule
