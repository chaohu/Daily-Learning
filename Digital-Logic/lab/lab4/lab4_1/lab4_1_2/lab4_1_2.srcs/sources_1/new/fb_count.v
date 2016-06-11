`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/06/11 20:22:04
// Design Name: 
// Module Name: fb_count
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


module fb_count(
    input CP,M,D,C,B,A,LD,CLR,
    output reg Qd,Qc,Qb,Qa,Qcc
    );
    reg [3:0] count;
    always @(posedge CP or negedge CLR or negedge LD)
    begin
        if(CLR == 0)
        begin
            count = 0;
            {Qd,Qc,Qb,Qa} = count;
            Qcc = 1;
        end
        else if(LD == 0)
        begin
            count = {D,C,B,A};
            {Qd,Qc,Qb,Qa} = count;
            Qcc = 1;
        end
        else if(M == 1)
        begin
            if(count ==15)
            begin
                count = 0;
                {Qd,Qc,Qb,Qa} = count;
                Qcc = 0;
            end
            else
            begin
                count  = count + 1;
                {Qd,Qc,Qb,Qa} = count;
                Qcc = 1;
            end
        end
        else
        begin
            if(count == 0)
            begin
                count = 15;
                {Qd,Qc,Qb,Qa} = count;
                Qcc = 0;
            end
            else
            begin
                count =count - 1;
                {Qd,Qc,Qb,Qa} = count;
                Qcc = 1;
            end
        end 
    end
endmodule
