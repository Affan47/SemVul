set_abs(struct input_dev *input, unsigned int code,
		    const struct bcm5974_param *p)
{
	int fuzz = p->snratio ? (p->max - p->min) / p->snratio : 0;
	input_set_abs_params(input, code, p->min, p->max, fuzz, 0);
}
