nvkm_i2c_aux_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	struct nvkm_i2c_aux *aux = container_of(adap, typeof(*aux), i2c);
	struct i2c_msg *msg = msgs;
	int ret, mcnt = num;

	ret = nvkm_i2c_aux_acquire(aux);
	if (ret)
		return ret;

	while (mcnt--) {
		u8 remaining = msg->len;
		u8 *ptr = msg->buf;

		while (remaining) {
			u8 cnt = (remaining > 16) ? 16 : remaining;
			u8 cmd;

			if (msg->flags & I2C_M_RD)
				cmd = 1;
			else
				cmd = 0;

			if (mcnt || remaining > 16)
				cmd |= 4;

			ret = aux->func->xfer(aux, true, cmd, msg->addr, ptr, cnt);
			if (ret < 0) {
				nvkm_i2c_aux_release(aux);
				return ret;
			}

			ptr += cnt;
			remaining -= cnt;
		}

		msg++;
	}

	nvkm_i2c_aux_release(aux);
	return num;
}
