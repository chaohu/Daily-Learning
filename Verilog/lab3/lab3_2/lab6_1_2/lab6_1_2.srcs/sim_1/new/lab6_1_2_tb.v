`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:49:46
// Design Name: 
// Module Name: lab6_1_2_tb
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


module lab6_1_2_tb(

    );
    reg Clk,reset,set,load;
    reg [3:0] D,S;
    wire [3:0] Q;
    lab6_1_2 dut(Clk,reset,set,load,D,S,Q);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk = Clk + 1)
        begin
            #5;
        end
    end
    initial
    begin
        S = 3;
        D = 0;
        load = 1;
        #10 D = 2;
        #10 load = 0;reset = 1;
        #10 reset = 0;set = 1;
        #10 set = 0;load = 1;
    end
endmodule
