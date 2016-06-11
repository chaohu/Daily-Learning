`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/02 19:59:26
// Design Name: 
// Module Name: lab3_2
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


module lab3_2(
    input x,
    output wire q1,q2,q3,q4,z
    );
    wire j2,j4;
    
    jk_ff
        q1_jk(q1,x,1,1),
        q2_jk(q2,q1,j2,1),
        q3_jk(q3,q2,1,1),
        q4_jk(q4,q1,j4,1);
        
    not
            un1(j2,q4);
    and
        ua1(j4,q2,q3),
        ua2(z,x,q1,q4);

endmodule

