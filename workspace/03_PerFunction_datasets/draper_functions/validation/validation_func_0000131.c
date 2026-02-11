sv_measure_l(comedi_sv_t *it,double *data)
{
	comedi_trig t;
	int ret=0;
	lsampl_t *val;
	unsigned int chan;
	comedi_range *rng;
	double sum;
	int i;
	int n;

	val=malloc(sizeof(*val)*it->n);

	chan=CR_PACK(it->chan,it->range,it->aref);

	t.subdev=it->subdevice;
	t.mode=0;
	t.flags=TRIG_DITHER;
	t.n_chan=1;
	t.chanlist=&chan;
	t.trigsrc=0;
	t.trigvar=0;
	t.trigvar1=0;

	rng=comedi_get_range(it->dev,it->subdevice,it->chan,it->range);

	for(n=0;n<it->n;){
		t.data=(void *)(val+n);
		t.n=it->n-n;
		i = comedi_ioctl(it->dev->fd, COMEDI_TRIG, &t);
		if(i<=0){
			ret=i;
			goto out;
		}
		n+=i;
	}

	sum=0;
	for(i=0;i<it->n;i++){
		sum+=comedi_to_phys(val[i],rng,it->maxdata);
	}
	*data=sum/it->n;

out:
	free(val);

	return ret;
}
