`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/06 17:02:42
// Design Name: 
// Module Name: check101
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


module check101(
    input x,CP,reset,
    output wire z
    );
    wire y1,ybar1,y2,ybar2,k1,j2,k2;
    jk_ff
        jk1_ff(x,k1,CP,reset,y1,ybar1),
        jk2_ff(j2,k2,CP,reset,y2,ybar2);
    not
        un1(k1,x);
    xor
        ux1(k2,y1,k1);
    and
        ua1(j2,y1,k1),
        ua2(z,y1,y2);
endmodule
