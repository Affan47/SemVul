enable_store(struct device *child,
			    struct device_attribute *attr,
			    const char *buf, size_t size)
{
	struct pwm_device *pwm = child_to_pwm_device(child);
	int val, ret;

	ret = kstrtoint(buf, 0, &val);
	if (ret)
		return ret;

	switch (val) {
	case 0:
		pwm_disable(pwm);
		break;
	case 1:
		ret = pwm_enable(pwm);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret ? : size;
}
