`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 23:44:56
// Design Name: 
// Module Name: lab2_2_1_partA_tb
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


module lab2_2_1_partA_tb(
    );
    
    reg [3:0] v;
	integer k;
    wire [6:0] seg0;
    
    lab2_2_1 DUT (.v(v),.seg0(seg0));
    
 
    initial
    begin
      v = 0;
	for(k=0; k < 16; k=k+1)
		#10 v = k;
	#20;
    end

endmodule
