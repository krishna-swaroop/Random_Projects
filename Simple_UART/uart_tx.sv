// UART Transmitter Module

// Instantiation Template
/*
uart_tx #(.DBIT(), .SB_TICK()) transmitter (
		.clk(),
		.reset_n(),
		.tx_start(),
		.s_tick(),
		.tx_din(),
		.tx_done_tick(),
		.tx()
	);
*/

module uart_tx #(
	parameter DBIT = 8;			// Data Bits
	parameter SB_TICK = 16;		// Stop Bit Ticks
) (
	input clk, reset_n,
	input tx_start, s_tick,
	input [DBIT-1:0] tx_din,
	output reg tx_done_tick,
	output tx
	);
	
	localparam IDLE = 0, START = 1, DATA = 2, STOP = 3;
	
	reg [1:0] state_d, state_q;
	reg [3:0] s_d, s_q;
	reg [$clog2(DBIT)-1:0] n_d, n_q;
	reg [DBIT-1:0] b_d, b_q;
	reg tx_d, tx_q;
	
	// State and other registers
	
	always_ff @(posedge clk, negedge reset_n)
	begin
		if(~reset_n)
		begin
			state_d <= IDLE;
			s_d <= 0;
			n_d <= 0;
			b_d <= 0;
			tx_d <= 1'b1;
		end
		else
		begin
			state_d <= state_q;
			s_d <= s_q;
			n_d <= n_q;
			b_d <= b_q;
			tx_d <= tx_q;
		end
	end
	
	// Next State Logic
	always_comb
	begin
		state_q = state_d;
		s_q = s_d;
		n_q = n_d;
		b_q = b_d;
		tx_done_tick = 1'b0;
		case (state_d)
			IDLE:
			begin
				tx_q = 1'b1;
				if(tx_start)
				begin
					s_q = 0;
					b_q = tx_din;
					state_q = start;
				end
			end
			START:
			begin
				tx_q = 1'b0;
				if(s_tick)
					if(s_d == 15)
					begin
						s_q = 0;
						n_q = 0;
						state_q = data;
					end
					else
						s_q =s_d + 1;
			end
			DATA:
			begin
				tx_q = b_d[0];
				if(s_tick)
					if(s_d == 15)
					begin
						s_q = 0;
						b_q = {1'b0, b_d[DBIT-1:1]}; //Right Shift
						if(n_d == (DBIT - 1))
							state_q = stop;
						else
							n_q = n_d + 1;
					end
					else
						s_q = s_d + 1;
			end
			STOP:
			begin
				tx_next = 1'b1;
				if(s_tick)
					if(s_d == (SB_TICK - 1))
					begin
						tx_done_tick = 1'b1;
						state_q = IDLE;
					end
					else
						s_q = s_d + 1;
			end
			default:
			begin
				state_q = IDLE;
			end
		endcase
	end
	// Output Logic
	assign tx_dout = b_d;
endmodule

	
	
	
	
	
	
	
	
	
	
	
	
	
	