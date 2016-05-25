`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 14:53:43
// Design Name: 
// Module Name: lab1_3_2_tb
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


module lab2_3_2_tb(

    );
        
    reg [3:0] a, b;
    wire [6:0] seg;
    wire cout;
    
    integer i,j;
    
    lab1_3_2 DUT (a,b,cout,seg);
    
 
    initial
    begin
      a = 0; b = 0;
      for(i=0;i<=9;i=i+1)
      begin
        for(j=0;j<=9;j=j+1)
        begin
            #10 a = i;b=j;
        end
      end
    end

endmodule
