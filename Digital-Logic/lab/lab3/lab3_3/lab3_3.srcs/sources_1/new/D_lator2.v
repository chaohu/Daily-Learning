`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/03 10:57:48
// Design Name: 
// Module Name: D_lator2
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


module D_lator2(
    input INPUT,CLK,
    output reg Q
	);
	always @(posedge CLK)
	begin
		#1 Q = INPUT;
	end 
endmodule
