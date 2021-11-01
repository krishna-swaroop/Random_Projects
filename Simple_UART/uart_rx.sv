// UART Receiver Module

// FSM with 4 states
// IDLE, START, DATA, STOP

// Instantiation Template

/*
	uart_rx #(.DBIT(), .SB_TICK()) receiver(
		.clk(),
		.reset_n(),
		.rx(),
		.s_tick(),
		.rx_done_tick(),
		.rx_dout()
	);
*/

module uart_rx #(
	parameter   DBIT = 8,
				SB_TICK = 16
) (
	input clk, reset_n,
	input rx, stick,
	output reg rx_done_tick,
	output [DBIT-1:0] rx_dout
	);
	
	localparam IDLE = 0, START = 1, DATA = 2, STOP = 3;
	
	reg [1:0] state_d, state_q;
	reg [3:0] s_d, s_q;					// number of baud rate ticks
	reg [$clog2(DBIT)-1:0] n_d, n_q;	// number of data bits stored
	reg [DBIT-1:0] b_d, b_q;			// number of received data bits
	
	
	//State and other registers
	always_ff @(posedge clk, negedge reset_n)
	begin
		if(~reset_n)
		begin
			state_d <= IDLE;
			s_d     <= 0;
			n_d     <= 0;
			b_d     <= 0;
		end
		else
		begin
			state_d <= state_q;
			s_d     <= s_q;
			n_d     <= n_q;
			b_d     <= b_q;
		end
	end
	
	// Next State Logic
	always_comb
	begin
		state_q = state_d;
		s_q     = s_d;
		n_q     = n_d;
		b_q     = b_d;
		rx_done_tick = 1'b0;
		case (state_reg)
			IDLE:
				if(~rx)
				begin
					s_q = 0;
					state_q = start;
				end
			START:
				if (s_tick)
					if (s_d == 7)
					begin
						s_q = 0;
						n_q = 0;
						state_q = DATA;
					end
				else
					s_q = s_d + 1;
			DATA:
				if (s_tick)
					if(s_d == 15)
					begin
						s_q = 0;
						b_q = {rx, b_d[DBIT-1:1]}; // Right Shift
						if (n_d == (DBIT-1))
							state_q = STOP;
						else
							n_q = n_d + 1;
					end
					else
						s_q = s_d + 1;
			STOP:
				if (s_tick)
					if(s_d == (SB_TICK-1))
					begin
						rx_done_tick = 1'b1;
						state_q = IDLE;
					end
					else
						s_q = s_d + 1;
			default:
				state_q = IDLE;
		endcase
	end
	
	// Output Logic
	assign rx_dout = b_d;
endmodule	
	
	
	
	
	
	
	
	
	
	