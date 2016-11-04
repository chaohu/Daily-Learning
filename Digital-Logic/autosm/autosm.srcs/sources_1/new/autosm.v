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
    input op_start,cancel_flag,
    input [1:0] coin_val,
    output reg hold_ind,drinktk_ind,charge_ind,
    output reg [2:0] charge_val
    );
    reg [2:0] state,nextstate;
    parameter S0 = 0,S1 = 1,S2 = 2,S3 = 3,S4 = 4,S5 = 5,S6 = 6;
    
    always @(posedge clk or posedge rst)            // always block to update state
    if(rst)
        state = S0;
    else
        state = nextstate;
        
    always @(state or cancel_flag)                                                 // always block to compute output
    begin
        drinktk_ind = 0;
        charge_ind = 0;
        hold_ind = 1;
        charge_val = 3'b000;
        case(state)
            S0:
            begin
                hold_ind = 0;
            end
            S1:
            begin
                if(cancel_flag == 1)
                begin
                    charge_ind = 1;
                end 
                charge_val = 3'b001;
            end
            S2:
            begin
                if(cancel_flag == 1)
                begin
                    charge_ind = 1;
                end 
                charge_val = 3'b010;
            end
            S3: 
            begin
                if(cancel_flag == 1)
                begin
                    charge_ind = 1;
                end 
                charge_val = 3'b011;
            end
            S4:
            begin
                if(cancel_flag == 1)
                begin
                    charge_ind = 1;
                end
                charge_val = 3'b100;
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
    
    always @(state or coin_val or cancel_flag or hold_ind or op_start)                                       // always block to compute nextstate
    begin
            case(state)
                S0: 
                begin
                    if(hold_ind == 0)
                    begin
                        if(op_start)
                        begin
                            if(coin_val == 2'b01)
                                nextstate = S1;
                            else if(coin_val == 2'b10)
                                nextstate = S2;
                            else
                                nextstate = S0;
                        end
                        else
                            nextstate = S0;
                    end
                    else
                        nextstate = S0;
                end
                S1: 
                begin
                    if(cancel_flag ==1)
                        nextstate = S0;
                    else 
                    begin
                        if(coin_val == 2'b01)
                            nextstate = S2;
                        else if(coin_val == 2'b10)
                            nextstate = S3;
                        else
                            nextstate = S0;
                    end
                end
                S2: 
                begin
                    if(cancel_flag ==1)
                        nextstate = S0;
                    else 
                    begin
                        if(coin_val == 2'b01)
                            nextstate = S3;
                        else if(coin_val == 2'b10)
                            nextstate = S4;
                        else
                            nextstate = S0;
                    end
                end
                S3: 
                begin
                    if(cancel_flag ==1)
                        nextstate = S0;
                    else 
                    begin
                        if(coin_val == 2'b01)
                            nextstate = S4;
                        else if(coin_val == 2'b10)
                            nextstate = S5;
                        else
                            nextstate = S0;
                    end
                end
                S4:
                begin
                    if(cancel_flag ==1)
                        nextstate = S0;
                    else 
                    begin
                        if(coin_val == 2'b01)
                            nextstate = S5;
                        else if(coin_val == 2'b10)
                            nextstate = S6;
                        else
                            nextstate = S0;
                    end
                end
                S5:
                begin
                    nextstate = S0;
                end
                S6:
                begin
                    nextstate = S0;
                end
            endcase
        end
endmodule
