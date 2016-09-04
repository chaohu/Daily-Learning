`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/08/31 22:34:01
// Design Name: 
// Module Name: autosm
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


module autosm(
    input clk,rst,
    input op_start,coin_val,cancel_flag,
    output reg hold_ind,drinktk_ind,charge_ind,
    output reg [2:0] charge_val,all_val
    );
    reg [2:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3,S4 = 4,S5 = 5,S6 = 6;
    
    always @(posedge clk or posedge rst)            // always block to update state
    if(rst)
        state = S0;
    else
        state = nextstate;
        
    always @(state )                                                 // always block to compute output
    begin
        drinktk_ind <= 0;
        charge_ind <= 0;
        hod_ind <= 1;
        charge_val <= 3'b000;
        case(state)
            S0:
            begin
                if(cancel_flag)                     //
                begin
                    charge_ind = 1;
                    charge_val = all_val;
                end
                else
                    hold_ind = 0;
            end
            S1:
            begin
                if(cancel_flag)
                begin
                    charge_ind = 1;
                    charge_val = 3'b001;
                end
            end
            S2:
            begin
                if(cancel_flag)
                begin
                    charge_ind = 1;
                    charge_val = 3'b010;
                end
            end
            S3: 
            begin
                if(cancel_flag)
                begin
                    charge_ind = 1;
                    charge_val = 3'b011;
                end
            end
            S4:
            begin
                if(cancel_flag)
                begin
                    charge_ind = 1;
                    charge_val = 3'b100;
                end
            end
            S5:
            begin
                drinktk_ind = 1;
            end
            S6:
            begin
                drinktk_ind = 1;
                charge_ind = 1;
                charge_val = 3'b001;
            end
        endcase
    end
    
    always @(state or in)                                       // always block to compute nextstate
    begin
            case(state)
                S0: 
                begin
                    if(in)
                        nextstate = S1;
                    else
                        nextstate = S0;
                end
                S1: 
                begin
                    if(in)
                        nextstate = S2;
                    else
                        nextstate = S1;
                end
                S2: 
                begin
                    if(in)
                        nextstate = S3;
                    else
                        nextstate = S2;
                end
                S3: 
                begin
                    if(in)
                        nextstate = S1;
                    else
                        nextstate = S3;
                end
            endcase
        end
endmodule
