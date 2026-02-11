_comedi_get_hardcal_converter(
	comedi_t *dev, unsigned subdevice, unsigned channel, unsigned range,
	enum comedi_conversion_direction direction,
	comedi_polynomial_t* polynomial)
{
	comedi_range *range_ptr = comedi_get_range(dev, subdevice, channel, range);
	lsampl_t maxdata;

	if(range_ptr == NULL)
	{
		return -1;
	}
	maxdata = comedi_get_maxdata(dev, subdevice, channel);
	if(maxdata == 0)
	{
		return -1;
	}
	polynomial->order = 1;
	switch(direction)
	{
	case COMEDI_TO_PHYSICAL:
		polynomial->expansion_origin = 0.;
		polynomial->coefficients[0] = range_ptr->min;
		polynomial->coefficients[1] = (range_ptr->max - range_ptr->min) / maxdata;
		break;
	case COMEDI_FROM_PHYSICAL:
		polynomial->expansion_origin = range_ptr->min;
		polynomial->coefficients[0] = 0.;
		polynomial->coefficients[1] =  maxdata / (range_ptr->max - range_ptr->min);
		break;
	}
	return 0;
}
