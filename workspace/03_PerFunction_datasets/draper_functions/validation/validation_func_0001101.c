stk1160_i2c_xfer(struct i2c_adapter *i2c_adap,
			   struct i2c_msg msgs[], int num)
{
	struct stk1160 *dev = i2c_adap->algo_data;
	int addr, rc, i;

	for (i = 0; i < num; i++) {
		addr = msgs[i].addr << 1;
		dprintk_i2c("%s: addr=%x", __func__, addr);

		if (!msgs[i].len) {

			rc = stk1160_i2c_check_for_device(dev, addr);
			if (rc < 0) {
				dprintk_i2c(" no device\n");
				return rc;
			}

		} else if (msgs[i].flags & I2C_M_RD) {

			dprintk_i2c(" subaddr not selected");
			rc = -EOPNOTSUPP;
			goto err;

		} else if (i + 1 < num && msgs[i].len <= 2 &&
			   (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr) {

			if (msgs[i].len != 1 || msgs[i + 1].len != 1) {
				dprintk_i2c(" len not supported");
				rc = -EOPNOTSUPP;
				goto err;
			}

			dprintk_i2c(" subaddr=%x", msgs[i].buf[0]);

			rc = stk1160_i2c_read_reg(dev, addr, msgs[i].buf[0],
				msgs[i + 1].buf);

			dprintk_i2c(" read=%x", *msgs[i + 1].buf);


			i++;

		} else {
			if (msgs[i].len != 2) {
				dprintk_i2c(" len not supported");
				rc = -EOPNOTSUPP;
				goto err;
			}

			dprintk_i2c(" subaddr=%x write=%x",
				msgs[i].buf[0],  msgs[i].buf[1]);

			rc = stk1160_i2c_write_reg(dev, addr, msgs[i].buf[0],
				msgs[i].buf[1]);
		}

		if (rc < 0)
			goto err;
		dprintk_i2c(" OK\n");
	}

	return num;
err:
	dprintk_i2c(" ERROR: %d\n", rc);
	return num;
}
