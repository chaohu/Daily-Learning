`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 11:06:22
// Design Name: 
// Module Name: lab1_2_1_tb
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


module lab1_2_1_tb(

    );
    reg [7:0] x_in;
    wire [7:0] y_out;
    reg [7:0] e_y_out;
        
    integer i;
        
    lab1_2_1 dut(.x_in(x_in),.y_out(y_out));
     
    function [7:0] expected_y_out;
        input [7:0] x_in;
    begin      
        expected_y_out[0] = x_in[0];
        expected_y_out[1] = x_in[1];
        expected_y_out[2] = x_in[2];
        expected_y_out[3] = x_in[3];
        expected_y_out[4] = x_in[4];
        expected_y_out[5] = x_in[5];
        expected_y_out[6] = x_in[6];
        expected_y_out[7] = x_in[7];
        end   
        endfunction   
        
        initial
        begin
            for (i=0; i < 255; i=i+2)
            begin
                #50 x_in=i;
                #10 e_y_out = expected_y_out(x_in);
                if(y_out == e_y_out)
                    $display("output matched at", $time);
                else
                    $display("output mis-matched at ",$time,": expected: %b, actual: %b", e_y_out, y_out);
            end
        end
endmodule
