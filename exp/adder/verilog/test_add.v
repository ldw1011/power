
module test_add();
reg [31:0] a;
reg [31:0] b;
wire [31:0] s;
reg clk, reset;
integer ifile;
adder U_0(clk, reset,a,b,s);
always
begin
#5 clk=~clk;
end
initial
begin
    clk=1;
    reset=1;
    ifile=$fopen("ivector.txt","r");
#20 reset=0;
  forever 
  begin
#5  $fscanf(ifile,"%d %d",a,b);
    $display("%d %d %d",a,b,s);
  end
end

initial
begin
  #10000 $finish;
  $fclose(ifile);
end
endmodule
