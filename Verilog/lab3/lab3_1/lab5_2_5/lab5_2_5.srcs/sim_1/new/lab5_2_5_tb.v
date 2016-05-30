`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:09:18
// Design Name: 
// Module Name: lab5_2_5_tb
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


module lab5_2_5_tb(

    );
    reg Clk,reset_n, T;
    wire Q;
    lab5_2_5 dut(Clk,reset_n, T,Q);

    initial
    begin
        for(Clk = 0;Clk >= 0;Clk=Clk+1)
        begin
            #10;
        end
    end
    
    initial
    begin
        T = 0;
        #20 T = 1;
        #80 T = 0;
        #120 T = 1;
    end
    
    initial
    begin
        reset_n = 0;
        #120 reset_n = 1;
        #20 reset_n = 0;
    end
    
endmodule
