nvkm_fantog_create(struct nvkm_therm *therm, struct dcb_gpio_func *func)
{
	struct nvkm_fantog *fan;
	int ret;

	if (therm->func->pwm_ctrl) {
		ret = therm->func->pwm_ctrl(therm, func->line, false);
		if (ret)
			return ret;
	}

	fan = kzalloc(sizeof(*fan), GFP_KERNEL);
	therm->fan = &fan->base;
	if (!fan)
		return -ENOMEM;

	fan->base.type = "toggle";
	fan->base.get = nvkm_fantog_get;
	fan->base.set = nvkm_fantog_set;
	nvkm_alarm_init(&fan->alarm, nvkm_fantog_alarm);
	fan->period_us = 100000;
	fan->percent = 100;
	fan->func = *func;
	spin_lock_init(&fan->lock);
	return 0;
}
