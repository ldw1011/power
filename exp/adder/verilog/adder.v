module adder(clk, reset,a,b,s);
input [31:0] a;
input [31:0] b;
output [31:0] s;
input clk;
input reset;
reg [31:0] reg_a;
reg [31:0] reg_b;
reg [31:0] reg_s;
wire [31:0] n_s;
  always@(posedge clk)
  begin
    if(reset==1'b1) 
    begin
      reg_a=0;
      reg_b=0;
      reg_s=0;
    end
    else 
    begin
      reg_a=a;
      reg_b=b;
      reg_s=n_s;
    end
  end
  assign n_s=reg_a+reg_b;
  assign s=n_s;
endmodule

