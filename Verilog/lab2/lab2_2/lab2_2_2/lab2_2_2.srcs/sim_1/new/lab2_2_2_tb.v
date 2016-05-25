`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 14:03:14
// Design Name: 
// Module Name: lab2_2_2_tb
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


module lab2_2_2_tb(

    );
    
    reg [3:0] x;
    integer k;
    wire [4:0] y;
    
    lab2_2_2 DUT (x,y);
    
 
    initial
    begin
      x = 0;
    for(k=0; k < 16; k=k+1)
        #10 x = k;
    #30;
    end

    
endmodule
