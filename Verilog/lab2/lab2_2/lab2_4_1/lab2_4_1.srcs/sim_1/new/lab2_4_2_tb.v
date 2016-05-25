`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 21:50:35
// Design Name: 
// Module Name: lab2_4_2_tb
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
    reg cin;
    wire [3:0] s;
    wire cout;
    
    integer i,j,k;
    
    lab2_4_1 DUT (a,b,cin,cout,s);
    
 
    initial
    begin
      a = 0; b = 0;k = 0;
      for(i=0;i<=15;i=i+1)
      begin
        for(j=0;j<=15;j=j+1)
        begin
            for(k=0;k<=1;k=k+1)
            begin
                #5 a = i;b = j;cin = k;
            end
        end
      end
    end

endmodule
