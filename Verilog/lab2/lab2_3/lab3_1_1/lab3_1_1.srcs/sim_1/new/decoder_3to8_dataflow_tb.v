`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 22:21:00
// Design Name: 
// Module Name: decoder_3to8_dataflow_tb
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


module decoder_3to8_dataflow_tb(
    );
    
    reg [2:0] x;
	wire [7:0] y;
	integer k;
    
    decoder_3to8_dataflow DUT (.x(x), .y(y));   
 
    initial
    begin
      x = 0; 
	for (k=7; k >=0 ; k=k-1)
		#10 x=k;
	#20;
    end

endmodule
