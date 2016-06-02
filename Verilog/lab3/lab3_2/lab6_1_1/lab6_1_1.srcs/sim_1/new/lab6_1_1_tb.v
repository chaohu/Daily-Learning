`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:37:23
// Design Name: 
// Module Name: lab6_1_1_tb
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


module lab6_1_1_tb(

    );
    reg Clk,load,reset;
    reg [3:0] D;
    wire [3:0] Q;
    lab6_1_1 dut(D,Clk,reset,load,Q);
    
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk=Clk+1)
        begin
            #10;
        end
    end
    
    initial
    begin
        #60 load = 1;
        #20 load = 0;
        #40 load = 1;
        #20 load = 0;
        #55 load = 1;
        #20 load = 0;
        #65 load = 1;
    end
    
    initial
    begin
        reset = 0;
        #155 reset = 1;
        #85 reset = 0;
    end
    
    initial
    begin
        D = 0;
        #20 D = 4'b0101;
        #60 D = 4'b1001;
    end
    
endmodule
