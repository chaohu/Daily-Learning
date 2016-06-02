`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/02 17:13:10
// Design Name: 
// Module Name: lab3_1_tb
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


module lab3_1_tb(

    );
    reg Ai,Bi,Cin;
    wire Si,Ci,F;
    integer i;
    
    lab3_1 dut(Ai,Bi,Cin,Si,Ci,F);
    
    initial
    begin
        for (i=0; i < 8; i=i+1)
        begin
            #10 {Cin,Bi,Ai} = i;
        end
    end
endmodule
