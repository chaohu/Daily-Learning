`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 20:37:23
// Design Name: 
// Module Name: lab4_2
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


module lab4_2(
    input SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT,
    output wire [width-1:0] NEXT_ZERO
    );
    parameter width = 8;
    wire [width-1:0] SUO,NEO,SE1O,SE2O,SE3O,MEMO,ADD1O,ADD2O;
    e_fulladder #(width) 
        add1(SUO,MEMO,ADD1O),
        add2(1,NEO,ADD2O);
    multiplexer #(width) 
        mu1(ADD1O,0,SUM_SEL,SE1O),
        mu2(MEMO,0,NEXT_SEL,SE2O),
        mu3(NEO,ADD2O,A_SEL,SE3O);
    register #(width) 
        re1(SE1O,LD_SUM,SUO),
        re2(SE2O,LD_NEXT,NEO);
    memory #(width) 
        me1(SE3O,MEMO);
    comparator #(width) 
        co1(SE2O,NEXT_ZERO);
endmodule
