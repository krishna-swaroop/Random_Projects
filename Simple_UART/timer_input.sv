// Timer Input Module Description

module timer_input #(
	parameter BITS = 4
) (
	input clk,
	input reset_n,
	input enable,
	input [BITS-1:0] FINAL_VALUE,
	// output [BITS-1:0] Q,
	output done
	);
	
	logic [BITS-1:0] Q_d, Q_q;
	
	always @(posedge clk, negedge reset_n)
	begin
		if(~reset_n)
			Q_d <= 1'b0l;
		else if(enable)
			Q_d <= Q_q;
		else 
			Q_d <= Q_d;
	end
	
	// Next State Logic
	assign done = (Q_d == FINAL_VALUE);
	
	always_comb
	begin
		Q_q = done? 'b0: Q_d + 1;
	end
	
endmodule

