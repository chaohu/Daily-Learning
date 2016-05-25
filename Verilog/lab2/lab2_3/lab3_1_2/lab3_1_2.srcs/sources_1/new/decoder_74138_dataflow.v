`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/25 22:53:19
// Design Name: 
// Module Name: decoder_74138_dataflow
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


module decoder_74138_dataflow(
    input [2:0] x,
    input g1,g2a_n,g2b_n
    );
    assign y[7] = g2a_n|g2b_n|(~g1)|x[0]|x[1]|x[2];
    assign y[6] = g2a_n|g2b_n|(~g1)|x[0]|x[1]|(~x[2]);
    assign y[5] = g2a_n|g2b_n|(~g1)|x[0]|(~x[1])|x[2];
    assign y[4] = g2a_n|g2b_n|(~g1)|x[0]|(~x[1])|(~x[2]);
    assign  y[3] = g2a_n|g2b_n|(~g1)|x[1]|x[2];
    assign y[2] = g2a_n|g2b_n|(~g1)|(~x[0])&x[1]&(~x[2]);
    assign y[1] = g2a_n|g2b_n|(~g1)|(~x[0])|(~x[1])|x[2];
    assign y[0] = g2a_n|g2b_n|(~g1)|(~x[0])|(~x[1])|(~x[2]);
   
    
endmodule
