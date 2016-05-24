`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/05/24 16:07:32
// Design Name: 
// Module Name: lab1_4_1_tb
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


module lab1_4_1_tb(

    );
    reg u,y,w,s0,s1;
    wire m;
    reg e_m,tra;
    reg [4:0] pro;
    
    integer i;
        
    lab1_4_1 dut(u,y,w,s0,s1,m);
     
    function expected_m;
        input u,y,w,s0,s1;
    begin      
        tra = (~s0 & u) | (s0 & y);
        expected_m = (~s1 & tra) | (s1 & w);
        end   
        endfunction   
        
        initial
        begin
            for (i=0; i < 32; i=i+1)
            begin
                #5 pro=i;
                #3 u=pro[0]; y=pro[1]; w=pro[2]; s0=pro[3]; s1=pro[4];
                #3 e_m = expected_m(u,y,w,s0,s1);
                if(m == e_m)
                    $display("output matched at", $time);
                else
                    $display("output mis-matched at ",$time,": expected: %b, actual: %b", e_m, m);
            end
        end
    
endmodule
