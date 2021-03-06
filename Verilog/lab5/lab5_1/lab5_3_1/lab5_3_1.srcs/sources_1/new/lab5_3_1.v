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
    output reg [2:0] yout,
    output reg [2:0] state,nextstate
    );

    parameter S0 = 0,S1 = 1,S2 = 3,S3 = 5,S4 = 7,S5 = 2;
    reg [5:0] ROM [7:0];
    initial $readmemb ("/home/huchao/Daily-Learning/Verilog/lab5/lab5_1/lab5_3_1/data.txt", ROM, 0, 7);
    always @(posedge clk or posedge reset)
    begin
        if(reset)
        begin
            {state,yout} = ROM[0];
        end
        else
        begin
            state <= nextstate;
        end
    end
        
    always @(state or ain)
    begin
        case(state)
        S0: 
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S0;
        end
        S1:
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S1;
        end
        S2:
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S2;
        end
        S3:
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S3;
        end    
        S4:
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S4;
        end    
        S5:
        begin
            if(ain)
                {nextstate,yout} = ROM[state];
            else
                nextstate = S5;
       end   
       endcase
    end

endmodule
