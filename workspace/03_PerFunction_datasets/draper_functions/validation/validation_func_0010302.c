brightness_default_validate(const int direction, const int value)
{
	switch (direction) {
		case SNC_VALIDATE_OUT:
			return value - 1;
		case SNC_VALIDATE_IN:
			if (value >= 0 && value < SONY_MAX_BRIGHTNESS)
				return value + 1;
	}
	return -EINVAL;
}
