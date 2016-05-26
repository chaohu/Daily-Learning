`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/26 19:35:42
// Design Name: 
// Module Name: fulladder_dataflow_tb
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

module fulladder_dataflow_tb();
    reg a, b, cin;
	wire cout, s;
	reg e_cout,e_s;
    integer i;
    
    fulladder_dataflow DUT (.a(a), .b(b), .cin(cin), .cout(cout), .s(s));
    
    function expected_s;
        input a,b,cin;
        begin
            expected_s = a ^ b ^ cin;
        end
    endfunction
    function expected_cout;
        input a,b,cin;
        begin
            expected_cout = ((a ^ b)&cin) | (a & b);
        end
    endfunction
    
    initial
    begin
        for(i=0;i<=8;i=i+1)
        begin
            #50 {cin,b,a} = i;
            #10 e_cout = expected_cout(a,b,cin);e_s = expected_s(a,b,cin);
            if((cout == e_cout) &&(s == e_s))
                $display("Test Passed");
            else
                $display("Test Failed");
        end
    end

endmodule
