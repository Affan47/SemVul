handle_deliver_response(Octstr *packet, Octstr *out, int sequence) {
	awaiting_response = 0;
	if (logging == LOG_packets)
		printf("RCV: Deliver response\n");
	deliveries++;
	if (max_deliveries > 0 && deliveries == max_deliveries) {
		time_t elapsed = time(NULL) - start_time;
		printf("LOG: %ld deliveries in %ld seconds\n",
			(long) max_deliveries, (long) elapsed);
	}

}
