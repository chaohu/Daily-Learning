`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/09/20 20:50:16
// Design Name: 
// Module Name: autosm_tb
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


module autosm_tb(

    );
    reg clk,rst;
    reg op_start,cancel_flag;
    reg [1:0] coin_val;
    wire hold_ind,drinktk_ind,charge_ind;
    wire [2:0] charge_val;
    
    autosm dut(clk,rst,op_start,cancel_flag,coin_val,hold_ind,drinktk_ind,charge_ind,charge_val);
    
    initial
    begin
        for(clk = 0;clk >= 0;clk = clk + 1)
        begin
            #5;
        end
    end
    
    initial
    begin
        rst = 1;cancel_flag = 0;op_start = 0;coin_val = 2'b00;
        #5 rst = 0;
        #5 op_start = 1;coin_val = 2'b01;
        #20 cancel_flag = 1;
    end
    
endmodule
