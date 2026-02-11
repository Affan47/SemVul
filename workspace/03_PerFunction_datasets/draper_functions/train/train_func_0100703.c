parse_device(tuple_t *tuple, cistpl_device_t *device)
{
	int i;
	u_char scale;
	u_char *p, *q;

	p = (u_char *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	device->ndev = 0;
	for (i = 0; i < CISTPL_MAX_DEVICES; i++) {

		if (*p == 0xff)
			break;
		device->dev[i].type = (*p >> 4);
		device->dev[i].wp = (*p & 0x08) ? 1 : 0;
		switch (*p & 0x07) {
		case 0:
			device->dev[i].speed = 0;
			break;
		case 1:
			device->dev[i].speed = 250;
			break;
		case 2:
			device->dev[i].speed = 200;
			break;
		case 3:
			device->dev[i].speed = 150;
			break;
		case 4:
			device->dev[i].speed = 100;
			break;
		case 7:
			if (++p == q)
				return -EINVAL;
			device->dev[i].speed = SPEED_CVT(*p);
			while (*p & 0x80)
				if (++p == q)
					return -EINVAL;
			break;
		default:
			return -EINVAL;
		}

		if (++p == q)
			return -EINVAL;
		if (*p == 0xff)
			break;
		scale = *p & 7;
		if (scale == 7)
			return -EINVAL;
		device->dev[i].size = ((*p >> 3) + 1) * (512 << (scale*2));
		device->ndev++;
		if (++p == q)
			break;
	}

	return 0;
}
