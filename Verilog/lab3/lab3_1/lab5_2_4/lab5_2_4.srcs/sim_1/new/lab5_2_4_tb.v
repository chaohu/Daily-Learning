`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/30 21:00:17
// Design Name: 
// Module Name: lab5_2_4_tb
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


module lab5_2_4_tb(

    );
    reg D,Clk,ce,reset;
    wire Q;
    lab5_2_4 dut(D,Clk,reset,ce,Q);
    
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
        #80 D = 0;
        #120 D = 1;
    end

    initial
    begin
        ce = 0;
        #60 ce = 1;
        #20 ce = 0;
        #100 ce = 1;
        #20 ce  = 0;
        #60 ce = 1;
        #20 ce = 0;
    end

    initial
    begin
        reset = 0;
        #120 reset = 1;
        #20 reset = 0;
    end
    
endmodule
