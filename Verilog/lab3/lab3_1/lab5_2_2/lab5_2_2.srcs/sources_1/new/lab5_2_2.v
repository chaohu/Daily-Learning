`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/27 21:54:35
// Design Name: 
// Module Name: lab5_2_2
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


module lab5_2_2(Clock,D,Qa,Qb,Qc);
    input Clock;
    input D;
    output reg Qa,Qb,Qc;
        
    always @ (Clock or D)
    if(Clock)
    begin
        Qa <= D & Clock;
    end
    
    always @ (posedge Clock)
    if(Clock)
    begin
        Qb <= D;
    end
    
    always @ (negedge Clock)
    if( ~Clock)
    begin
        Qc <= D;
    end
endmodule