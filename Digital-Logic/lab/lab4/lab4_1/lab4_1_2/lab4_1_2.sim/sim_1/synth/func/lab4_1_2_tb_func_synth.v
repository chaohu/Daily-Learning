// Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2015.2 (lin64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
// Date        : Sat Jun 11 20:42:34 2016
// Host        : ajay running 64-bit Ubuntu 14.04.4 LTS
// Command     : write_verilog -mode funcsim -nolib -force -file
//               /home/huchao/Daily-Learning/Digital-Logic/lab/lab4/lab4_1_2/lab4_1_2.sim/sim_1/synth/func/lab4_1_2_tb_func_synth.v
// Design      : fb_count
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* NotValidForBitStream *)
module fb_count
   (CP,
    M,
    D,
    C,
    B,
    A,
    LD,
    CLR,
    Qd,
    Qc,
    Qb,
    Qa,
    Qcc);
  input CP;
  input M;
  input D;
  input C;
  input B;
  input A;
  input LD;
  input CLR;
  output Qd;
  output Qc;
  output Qb;
  output Qa;
  output Qcc;

  wire A;
  wire A_IBUF;
  wire B;
  wire B_IBUF;
  wire C;
  wire CLR;
  wire CLR_IBUF;
  wire CP;
  wire CP_IBUF;
  wire CP_IBUF_BUFG;
  wire C_IBUF;
  wire D;
  wire D_IBUF;
  wire LD;
  wire LD_IBUF;
  wire M;
  wire M_IBUF;
  wire Qa;
  wire Qa_OBUF;
  wire Qa_reg_C_n_0;
  wire Qa_reg_LDC_i_1_n_0;
  wire Qa_reg_LDC_n_0;
  wire Qa_reg_P_n_0;
  wire Qb;
  wire Qb_OBUF;
  wire Qb_reg_C_n_0;
  wire Qb_reg_LDC_i_1_n_0;
  wire Qb_reg_LDC_n_0;
  wire Qb_reg_P_n_0;
  wire Qc;
  wire Qc_OBUF;
  wire Qc_reg_C_n_0;
  wire Qc_reg_LDC_i_1_n_0;
  wire Qc_reg_LDC_n_0;
  wire Qc_reg_P_n_0;
  wire Qcc;
  wire Qcc_OBUF;
  wire Qcc_i_1_n_0;
  wire Qcc_i_2_n_0;
  wire Qd;
  wire Qd_OBUF;
  wire Qd_reg_C_n_0;
  wire Qd_reg_LDC_i_1_n_0;
  wire Qd_reg_LDC_n_0;
  wire Qd_reg_P_n_0;
  wire [3:0]count;
  wire \count[0]_C_i_1_n_0 ;
  wire \count[1]_C_i_1_n_0 ;
  wire \count[2]_C_i_1_n_0 ;
  wire \count[3]_C_i_1_n_0 ;
  wire \count_reg[0]_C_n_0 ;
  wire \count_reg[0]_LDC_i_1_n_0 ;
  wire \count_reg[0]_LDC_i_2_n_0 ;
  wire \count_reg[0]_LDC_n_0 ;
  wire \count_reg[1]_C_n_0 ;
  wire \count_reg[1]_LDC_i_1_n_0 ;
  wire \count_reg[1]_LDC_i_2_n_0 ;
  wire \count_reg[1]_LDC_n_0 ;
  wire \count_reg[2]_C_n_0 ;
  wire \count_reg[2]_LDC_i_1_n_0 ;
  wire \count_reg[2]_LDC_i_2_n_0 ;
  wire \count_reg[2]_LDC_n_0 ;
  wire \count_reg[3]_C_n_0 ;
  wire \count_reg[3]_LDC_i_1_n_0 ;
  wire \count_reg[3]_LDC_i_2_n_0 ;
  wire \count_reg[3]_LDC_n_0 ;

  IBUF A_IBUF_inst
       (.I(A),
        .O(A_IBUF));
  IBUF B_IBUF_inst
       (.I(B),
        .O(B_IBUF));
  IBUF CLR_IBUF_inst
       (.I(CLR),
        .O(CLR_IBUF));
  BUFG CP_IBUF_BUFG_inst
       (.I(CP_IBUF),
        .O(CP_IBUF_BUFG));
  IBUF CP_IBUF_inst
       (.I(CP),
        .O(CP_IBUF));
  IBUF C_IBUF_inst
       (.I(C),
        .O(C_IBUF));
  IBUF D_IBUF_inst
       (.I(D),
        .O(D_IBUF));
  IBUF LD_IBUF_inst
       (.I(LD),
        .O(LD_IBUF));
  IBUF M_IBUF_inst
       (.I(M),
        .O(M_IBUF));
  OBUF Qa_OBUF_inst
       (.I(Qa_OBUF),
        .O(Qa));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qa_OBUF_inst_i_1
       (.I0(Qa_reg_P_n_0),
        .I1(Qa_reg_LDC_n_0),
        .I2(Qa_reg_C_n_0),
        .O(Qa_OBUF));
  FDCE #(
    .INIT(1'b0)) 
    Qa_reg_C
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(Qa_reg_LDC_i_1_n_0),
        .D(\count[0]_C_i_1_n_0 ),
        .Q(Qa_reg_C_n_0));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    Qa_reg_LDC
       (.CLR(Qa_reg_LDC_i_1_n_0),
        .D(1'b1),
        .G(\count_reg[0]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(Qa_reg_LDC_n_0));
  LUT3 #(
    .INIT(8'h1F)) 
    Qa_reg_LDC_i_1
       (.I0(LD_IBUF),
        .I1(A_IBUF),
        .I2(CLR_IBUF),
        .O(Qa_reg_LDC_i_1_n_0));
  FDPE #(
    .INIT(1'b1)) 
    Qa_reg_P
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(\count[0]_C_i_1_n_0 ),
        .PRE(\count_reg[0]_LDC_i_1_n_0 ),
        .Q(Qa_reg_P_n_0));
  OBUF Qb_OBUF_inst
       (.I(Qb_OBUF),
        .O(Qb));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qb_OBUF_inst_i_1
       (.I0(Qb_reg_P_n_0),
        .I1(Qb_reg_LDC_n_0),
        .I2(Qb_reg_C_n_0),
        .O(Qb_OBUF));
  FDCE #(
    .INIT(1'b0)) 
    Qb_reg_C
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(Qb_reg_LDC_i_1_n_0),
        .D(\count[1]_C_i_1_n_0 ),
        .Q(Qb_reg_C_n_0));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    Qb_reg_LDC
       (.CLR(Qb_reg_LDC_i_1_n_0),
        .D(1'b1),
        .G(\count_reg[1]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(Qb_reg_LDC_n_0));
  LUT3 #(
    .INIT(8'h1F)) 
    Qb_reg_LDC_i_1
       (.I0(LD_IBUF),
        .I1(B_IBUF),
        .I2(CLR_IBUF),
        .O(Qb_reg_LDC_i_1_n_0));
  FDPE #(
    .INIT(1'b1)) 
    Qb_reg_P
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(\count[1]_C_i_1_n_0 ),
        .PRE(\count_reg[1]_LDC_i_1_n_0 ),
        .Q(Qb_reg_P_n_0));
  OBUF Qc_OBUF_inst
       (.I(Qc_OBUF),
        .O(Qc));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qc_OBUF_inst_i_1
       (.I0(Qc_reg_P_n_0),
        .I1(Qc_reg_LDC_n_0),
        .I2(Qc_reg_C_n_0),
        .O(Qc_OBUF));
  FDCE #(
    .INIT(1'b0)) 
    Qc_reg_C
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(Qc_reg_LDC_i_1_n_0),
        .D(\count[2]_C_i_1_n_0 ),
        .Q(Qc_reg_C_n_0));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    Qc_reg_LDC
       (.CLR(Qc_reg_LDC_i_1_n_0),
        .D(1'b1),
        .G(\count_reg[2]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(Qc_reg_LDC_n_0));
  LUT3 #(
    .INIT(8'h1F)) 
    Qc_reg_LDC_i_1
       (.I0(LD_IBUF),
        .I1(C_IBUF),
        .I2(CLR_IBUF),
        .O(Qc_reg_LDC_i_1_n_0));
  FDPE #(
    .INIT(1'b1)) 
    Qc_reg_P
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(\count[2]_C_i_1_n_0 ),
        .PRE(\count_reg[2]_LDC_i_1_n_0 ),
        .Q(Qc_reg_P_n_0));
  OBUF Qcc_OBUF_inst
       (.I(Qcc_OBUF),
        .O(Qcc));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h7FFFFFFE)) 
    Qcc_i_1
       (.I0(count[3]),
        .I1(M_IBUF),
        .I2(count[0]),
        .I3(count[2]),
        .I4(count[1]),
        .O(Qcc_i_1_n_0));
  LUT2 #(
    .INIT(4'h7)) 
    Qcc_i_2
       (.I0(LD_IBUF),
        .I1(CLR_IBUF),
        .O(Qcc_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qcc_i_3
       (.I0(Qd_reg_P_n_0),
        .I1(\count_reg[3]_LDC_n_0 ),
        .I2(\count_reg[3]_C_n_0 ),
        .O(count[3]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qcc_i_4
       (.I0(Qa_reg_P_n_0),
        .I1(\count_reg[0]_LDC_n_0 ),
        .I2(\count_reg[0]_C_n_0 ),
        .O(count[0]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qcc_i_5
       (.I0(Qc_reg_P_n_0),
        .I1(\count_reg[2]_LDC_n_0 ),
        .I2(\count_reg[2]_C_n_0 ),
        .O(count[2]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qcc_i_6
       (.I0(Qb_reg_P_n_0),
        .I1(\count_reg[1]_LDC_n_0 ),
        .I2(\count_reg[1]_C_n_0 ),
        .O(count[1]));
  FDPE #(
    .INIT(1'b1)) 
    Qcc_reg
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(Qcc_i_1_n_0),
        .PRE(Qcc_i_2_n_0),
        .Q(Qcc_OBUF));
  OBUF Qd_OBUF_inst
       (.I(Qd_OBUF),
        .O(Qd));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Qd_OBUF_inst_i_1
       (.I0(Qd_reg_P_n_0),
        .I1(Qd_reg_LDC_n_0),
        .I2(Qd_reg_C_n_0),
        .O(Qd_OBUF));
  FDCE #(
    .INIT(1'b0)) 
    Qd_reg_C
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(Qd_reg_LDC_i_1_n_0),
        .D(\count[3]_C_i_1_n_0 ),
        .Q(Qd_reg_C_n_0));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    Qd_reg_LDC
       (.CLR(Qd_reg_LDC_i_1_n_0),
        .D(1'b1),
        .G(\count_reg[3]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(Qd_reg_LDC_n_0));
  LUT3 #(
    .INIT(8'h1F)) 
    Qd_reg_LDC_i_1
       (.I0(LD_IBUF),
        .I1(D_IBUF),
        .I2(CLR_IBUF),
        .O(Qd_reg_LDC_i_1_n_0));
  FDPE #(
    .INIT(1'b1)) 
    Qd_reg_P
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .D(\count[3]_C_i_1_n_0 ),
        .PRE(\count_reg[3]_LDC_i_1_n_0 ),
        .Q(Qd_reg_P_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    \count[0]_C_i_1 
       (.I0(count[0]),
        .O(\count[0]_C_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h69)) 
    \count[1]_C_i_1 
       (.I0(M_IBUF),
        .I1(count[1]),
        .I2(count[0]),
        .O(\count[1]_C_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h7E81)) 
    \count[2]_C_i_1 
       (.I0(M_IBUF),
        .I1(count[1]),
        .I2(count[0]),
        .I3(count[2]),
        .O(\count[2]_C_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h7F80FE01)) 
    \count[3]_C_i_1 
       (.I0(M_IBUF),
        .I1(count[1]),
        .I2(count[0]),
        .I3(count[3]),
        .I4(count[2]),
        .O(\count[3]_C_i_1_n_0 ));
  FDCE #(
    .INIT(1'b0)) 
    \count_reg[0]_C 
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(\count_reg[0]_LDC_i_2_n_0 ),
        .D(\count[0]_C_i_1_n_0 ),
        .Q(\count_reg[0]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \count_reg[0]_LDC 
       (.CLR(\count_reg[0]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\count_reg[0]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\count_reg[0]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \count_reg[0]_LDC_i_1 
       (.I0(A_IBUF),
        .I1(CLR_IBUF),
        .I2(LD_IBUF),
        .O(\count_reg[0]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \count_reg[0]_LDC_i_2 
       (.I0(CLR_IBUF),
        .I1(LD_IBUF),
        .I2(A_IBUF),
        .O(\count_reg[0]_LDC_i_2_n_0 ));
  FDCE #(
    .INIT(1'b0)) 
    \count_reg[1]_C 
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(\count_reg[1]_LDC_i_2_n_0 ),
        .D(\count[1]_C_i_1_n_0 ),
        .Q(\count_reg[1]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \count_reg[1]_LDC 
       (.CLR(\count_reg[1]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\count_reg[1]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\count_reg[1]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \count_reg[1]_LDC_i_1 
       (.I0(B_IBUF),
        .I1(CLR_IBUF),
        .I2(LD_IBUF),
        .O(\count_reg[1]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \count_reg[1]_LDC_i_2 
       (.I0(CLR_IBUF),
        .I1(LD_IBUF),
        .I2(B_IBUF),
        .O(\count_reg[1]_LDC_i_2_n_0 ));
  FDCE #(
    .INIT(1'b0)) 
    \count_reg[2]_C 
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(\count_reg[2]_LDC_i_2_n_0 ),
        .D(\count[2]_C_i_1_n_0 ),
        .Q(\count_reg[2]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \count_reg[2]_LDC 
       (.CLR(\count_reg[2]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\count_reg[2]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\count_reg[2]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \count_reg[2]_LDC_i_1 
       (.I0(C_IBUF),
        .I1(CLR_IBUF),
        .I2(LD_IBUF),
        .O(\count_reg[2]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \count_reg[2]_LDC_i_2 
       (.I0(CLR_IBUF),
        .I1(LD_IBUF),
        .I2(C_IBUF),
        .O(\count_reg[2]_LDC_i_2_n_0 ));
  FDCE #(
    .INIT(1'b0)) 
    \count_reg[3]_C 
       (.C(CP_IBUF_BUFG),
        .CE(1'b1),
        .CLR(\count_reg[3]_LDC_i_2_n_0 ),
        .D(\count[3]_C_i_1_n_0 ),
        .Q(\count_reg[3]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \count_reg[3]_LDC 
       (.CLR(\count_reg[3]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\count_reg[3]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\count_reg[3]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \count_reg[3]_LDC_i_1 
       (.I0(D_IBUF),
        .I1(CLR_IBUF),
        .I2(LD_IBUF),
        .O(\count_reg[3]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \count_reg[3]_LDC_i_2 
       (.I0(CLR_IBUF),
        .I1(LD_IBUF),
        .I2(D_IBUF),
        .O(\count_reg[3]_LDC_i_2_n_0 ));
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
