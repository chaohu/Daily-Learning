`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 17:37:19
// Design Name: 
// Module Name: add_two_values_task_tb
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


module add_two_values_task_tb(

    );
    reg [3:0] ain, bin;
    wire [3:0] sum;
    wire cout;
    integer k;
    
    add_two_values_task DUT (.x(ain), .y(bin), .cout(cout), .z(sum));
     
    initial
    begin
      ain = 4'h6; bin = 4'ha;
    $display("ain=%b, bin=%b, cout=%b, sum=%b at time=%t",ain, bin, cout, sum, $time);
    for (k=0; k < 5; k=k+1)
    begin
        #5 ain = ain + k; bin = bin + k;
        $display("ain=%b, bin=%b, cout=%b, sum=%b at time=%t",ain, bin, cout, sum, $time);
    end
    $display("Simulation Done");
    end
    
endmodule
