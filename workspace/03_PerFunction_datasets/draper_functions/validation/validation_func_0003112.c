ltc_encoder_set_filter(LTCEncoder *e, double rise_time) {


	if (rise_time <= 0)
		e->filter_const = 0;
	else
		e->filter_const = 1.0 - exp( -1.0 / (e->sample_rate * rise_time / 2000000.0 / exp(1.0)) );
}
