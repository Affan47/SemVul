stv0288_set_voltage(struct dvb_frontend *fe,
			       enum fe_sec_voltage volt)
{
	dprintk("%s: %s\n", __func__,
		volt == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		volt == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" : "??");

	return 0;
}
