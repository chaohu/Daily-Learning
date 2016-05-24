`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 21:03:30
// Design Name: 
// Module Name: lab2_2_1_partA
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


module lab2_2_1_partA(
    input [3:0] v,
    output wire z,
    output [3:0] m
    );
    wire [3:0] c;
    comparator_dataflow dut1(v,z);
    
    lab2_circuitA_dataflow dut2(v,c);
    
    lab1_1_1 sel1(v[0],c[0],z,m[0]);
    lab1_1_1 sel2(v[1],c[1],z,m[1]);
    lab1_1_1 sel3(v[2],c[2],z,m[2]);
    lab1_1_1 sel4(v[3],c[3],z,m[3]);
    
endmodule
