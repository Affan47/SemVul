sig_i2c_proxy_clock_after_falling_flank(struct sig_i2c_bus_member *m)
{
	struct sig_i2c_bus *b = (struct sig_i2c_bus *)m->bus;

	switch (m->state) {
	case SIG_I2C_SLAVE_ACK:
		m->state = SIG_I2C_SLAVE_ACK_DOWN;

		sig_i2c_bus_set_data(b, m, false);
		break;

	case SIG_I2C_SLAVE_ACK_DOWN:
		m->state = SIG_I2C_DATA;

		sig_i2c_bus_set_data(b, m, true);

		if (m->read_mode) {
			sig_i2c_proxy_write_next(m);
		}

		break;

	case SIG_I2C_DATA:
		if (m->read_mode) {


			sig_i2c_bus_set_data(b, m,
				(m->shift_register & 0x80) == 0x80);
		}
		break;

	case SIG_I2C_MASTER_ACK:
		m->state = SIG_I2C_MASTER_ACK_DOWN;

		sig_i2c_bus_set_data(b, m, true);
		break;

	case SIG_I2C_MASTER_ACK_DOWN:
		if (m->read_mode) {
			sig_i2c_proxy_write_next(m);
		}
		m->state = SIG_I2C_DATA;
		break;

	default:

		break;
	}
}
