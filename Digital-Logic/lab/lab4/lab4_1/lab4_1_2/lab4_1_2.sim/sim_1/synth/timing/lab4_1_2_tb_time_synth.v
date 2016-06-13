// Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2015.2 (win64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
// Date        : Sun Jun 12 16:30:48 2016
// Host        : 804-066 running 64-bit Service Pack 1  (build 7601)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/Users/Administrator/Desktop/huchao/lab4/lab4_1/lab4_1_2/lab4_1_2.sim/sim_1/synth/timing/lab4_1_2_tb_time_synth.v
// Design      : lab4_1_2
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module fb_count
   (Qc_OBUF,
    Qb_OBUF,
    Qa_OBUF,
    Qd_OBUF,
    LD_reg_inv,
    Z_reg,
    CP_IBUF_BUFG,
    LD_reg_inv_0,
    M_IBUF);
  output Qc_OBUF;
  output Qb_OBUF;
  output Qa_OBUF;
  output Qd_OBUF;
  output LD_reg_inv;
  output Z_reg;
  input CP_IBUF_BUFG;
  input LD_reg_inv_0;
  input M_IBUF;

  wire CP_IBUF_BUFG;
  wire LD_reg_inv;
  wire LD_reg_inv_0;
  wire M_IBUF;
  wire Qa_OBUF;
  wire Qa_i_1_n_0;
  wire Qb_OBUF;
  wire Qb_i_1_n_0;
  wire Qc_OBUF;
  wire Qc_i_1_n_0;
  wire Qd_OBUF;
  wire Qd_i_1_n_0;
  wire Z_reg;

  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00000080)) 
    LD_inv_i_1
       (.I0(Qb_OBUF),
        .I1(Qa_OBUF),
        .I2(Qd_OBUF),
        .I3(Qc_OBUF),
        .I4(M_IBUF),
        .O(LD_reg_inv));
  LUT1 #(
    .INIT(2'h1)) 
    Qa_i_1
       (.I0(Qa_OBUF),
        .O(Qa_i_1_n_0));
  FDCE #(
    .INIT(1'b0)) 
    Qa_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(LD_reg_inv_0),
        .D(Qa_i_1_n_0),
        .Q(Qa_OBUF));
  LUT3 #(
    .INIT(8'h69)) 
    Qb_i_1
       (.I0(M_IBUF),
        .I1(Qb_OBUF),
        .I2(Qa_OBUF),
        .O(Qb_i_1_n_0));
  FDPE #(
    .INIT(1'b1)) 
    Qb_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(Qb_i_1_n_0),
        .PRE(LD_reg_inv_0),
        .Q(Qb_OBUF));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h6CC9)) 
    Qc_i_1
       (.I0(M_IBUF),
        .I1(Qc_OBUF),
        .I2(Qa_OBUF),
        .I3(Qb_OBUF),
        .O(Qc_i_1_n_0));
  FDCE #(
    .INIT(1'b0)) 
    Qc_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(LD_reg_inv_0),
        .D(Qc_i_1_n_0),
        .Q(Qc_OBUF));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h6CCCCCC9)) 
    Qd_i_1
       (.I0(M_IBUF),
        .I1(Qd_OBUF),
        .I2(Qb_OBUF),
        .I3(Qa_OBUF),
        .I4(Qc_OBUF),
        .O(Qd_i_1_n_0));
  FDCE #(
    .INIT(1'b0)) 
    Qd_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(LD_reg_inv_0),
        .D(Qd_i_1_n_0),
        .Q(Qd_OBUF));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00400080)) 
    Z_i_1
       (.I0(Qb_OBUF),
        .I1(Qa_OBUF),
        .I2(Qd_OBUF),
        .I3(Qc_OBUF),
        .I4(M_IBUF),
        .O(Z_reg));
endmodule

(* NotValidForBitStream *)
module lab4_1_2
   (CP,
    M,
    Qd,
    Qc,
    Qb,
    Qa,
    Z);
  input CP;
  input M;
  output Qd;
  output Qc;
  output Qb;
  output Qa;
  output Z;

  wire CP;
  wire CP_IBUF;
  wire CP_IBUF_BUFG;
  wire LD_reg_inv_n_0;
  wire M;
  wire M_IBUF;
  wire Qa;
  wire Qa_OBUF;
  wire Qb;
  wire Qb_OBUF;
  wire Qc;
  wire Qc_OBUF;
  wire Qd;
  wire Qd_OBUF;
  wire Z;
  wire Z_OBUF;
  wire cou1_n_4;
  wire cou1_n_5;

initial begin
 $sdf_annotate("lab4_1_2_tb_time_synth.sdf",,,,"tool_control");
end
  BUFG CP_IBUF_BUFG_inst
       (.I(CP_IBUF),
        .O(CP_IBUF_BUFG));
  IBUF CP_IBUF_inst
       (.I(CP),
        .O(CP_IBUF));
  FDRE #(
    .INIT(1'b0)) 
    LD_reg_inv
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(cou1_n_4),
        .Q(LD_reg_inv_n_0),
        .R(1'b0));
  IBUF M_IBUF_inst
       (.I(M),
        .O(M_IBUF));
  OBUF Qa_OBUF_inst
       (.I(Qa_OBUF),
        .O(Qa));
  OBUF Qb_OBUF_inst
       (.I(Qb_OBUF),
        .O(Qb));
  OBUF Qc_OBUF_inst
       (.I(Qc_OBUF),
        .O(Qc));
  OBUF Qd_OBUF_inst
       (.I(Qd_OBUF),
        .O(Qd));
  OBUF Z_OBUF_inst
       (.I(Z_OBUF),
        .O(Z));
  FDRE #(
    .INIT(1'b0)) 
    Z_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(cou1_n_5),
        .Q(Z_OBUF),
        .R(1'b0));
  fb_count cou1
       (.CP_IBUF_BUFG(CP_IBUF_BUFG),
        .LD_reg_inv(cou1_n_4),
        .LD_reg_inv_0(LD_reg_inv_n_0),
        .M_IBUF(M_IBUF),
        .Qa_OBUF(Qa_OBUF),
        .Qb_OBUF(Qb_OBUF),
        .Qc_OBUF(Qc_OBUF),
        .Qd_OBUF(Qd_OBUF),
        .Z_reg(cou1_n_5));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
