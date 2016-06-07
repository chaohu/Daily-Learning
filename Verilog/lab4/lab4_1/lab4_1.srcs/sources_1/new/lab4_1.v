`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:01:31
// Design Name: 
// Module Name: lab4_1
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


module lab4_1(
    input S0,S1,S2,S3,Clk
    );
    wire [7:0] S0O,S1O,S2O,S3O,R0O,R1O,ADDO,ACCO;
    multiplexer 
        s0(S3O,R0O,S0,S0O),
        s1(S3O,R1O,S1,S1O),
        s2(R0O,R1O,S2,S2O),
        s3(S2O,ACCO,S3,S3O);
    register
        r0(S0O,Clk,R0O),
        r1(S1O,Clk,R1O),
        acc(ADDO,Clk,ACCO); 
    e_fulladder e_add(S2O,ACCO,ADDO);
endmodule
