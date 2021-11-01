// Simple UART Module

module uart #(
	parameter DBIT = 8;			//data bits
	parameter SB_TICK = 16;		//stop bit ticks
) (
	input clk, reset_n,
	
	// Receiver Port
	output [DBIT-1:0]	r_data,
	input rd_uart,
	output rx_empty
	input rx,
	
	// Transmitter Port
	input [DBIT-1:0]	w_data,
	input wr_uart,
	output tx_full,
	output tx,
	
	// Baud Rate Generator
	input [10:0] TIMER_FINAL_VALUE
);

	// Timer as baud rate generator
	/*
		(FINAL_VALUE +1)*T = 1/(16*b)
		FINAL_VALUE = (1/(16*b*T)) - 1
	*/
	logic tick;
	timer_input #(.BITS(11)) baud_rate_generator (
		.clk(clk),
		.reset_n(reset_n),
		.enable(1'b1),
		.FINAL_VALUE(TIMER_FINAL_VALUE),
		.done(tick)
	);
	
	// Receiver
	logic rx_done_tick;
	logic [DBIT-1:0] rx_dout;
	uart_rx #(.DBIT(DBIT), .SB_TICK(SB_TICK)) receiver(
		.clk(clk),
		.reset_n(reset_n),
		.rx(rx),
		.s_tick(tick),
		.rx_done_tick(rx_done_tick),
		.rx_dout(rx_dout)
	);
	
	fifo_generator_0 rx_FIFO (
		.clk(clk),
		.srst(~reset_n),
		.din(rx_dout),
		.wr_en(rx_done_tick),
		.rd_en(rd_uart),
		.dout(r_data),
		.full(),
		.empty(rx_empty)
	);
	
	//Transmitter
	logic tx_fifo_empty, tx_done_tick;
	logic [DBIT-1:0] tx_din;
	
	uart_tx #(.DBIT(DBIT), .SB_TICK(SB_TICK)) transmitter (
		.clk(clk),
		.reset_n(reset_n),
		.tx_start(~tx_fifo_empty),
		.s_tick(tick),
		.tx_din(tx_din),
		.tx_done_tick(tx_done_tick),
		.tx(tx)
	);
	
	fifo_generator_0 tx_FIFO (
		.clk(clk),
		.srst(~reset_n),
		.din(w_data),
		.wr_en(wr_uart),
		.rd_en(tx_done_tick),
		.dout(tx_din),
		.full(tx_full),
		.empty(tx_fifo_empty)
	);
endmodule
