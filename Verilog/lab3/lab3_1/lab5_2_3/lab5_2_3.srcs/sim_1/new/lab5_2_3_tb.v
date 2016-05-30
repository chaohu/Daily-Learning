`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 20:46:50
// Design Name: 
// Module Name: lab5_2_3_tb
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


module lab5_2_3_tb(

    );
    reg Clk,D,reset;
    wire Q;
    lab5_2_3 dut(Clk,D,reset,Q);
    initial
    begin
        for(Clk = 0;Clk >= 0;Clk=Clk+1)
        begin
            #10;
        end
    end
    
    initial
    begin
        D = 0;
        #20 D = 1;
        #65 D = 0;
    end
    initial
    begin
        reset = 0;
        #35 reset = 1;
        #5 reset = 0;
        #5 reset = 1;
        #10 reset = 0;
        #32 reset = 1;
        #5 reset = 0;
    end
endmodule
