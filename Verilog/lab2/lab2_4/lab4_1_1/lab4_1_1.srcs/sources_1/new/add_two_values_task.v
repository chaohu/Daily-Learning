`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 16:50:44
// Design Name: 
// Module Name: add_two_values_task
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


module add_two_values_task(
    input [3:0] x,y,
    output reg [3:0] z,
    output reg cout
    );
    task add_two_values;
        input [3:0] x,y;
        output [3:0] z;
        output cout;
        reg [4:0] k;
        begin
            k = x + y;
            {cout,z} = k;
        end
    endtask
    always
        @(x or y)
        begin
            add_two_values(x,y,z,cout);
        end
        
endmodule
