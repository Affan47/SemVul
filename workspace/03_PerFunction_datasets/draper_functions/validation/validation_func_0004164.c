learn()
{
	ILint i,j,b,g,r;
	ILint radius,rad,alpha,step,delta,samplepixels;
	ILubyte *p;
	ILubyte *lim;

	alphadec = 30 + ((samplefac-1)/3);
	p = thepicture;
	lim = thepicture + lengthcount;
	samplepixels = lengthcount/(3*samplefac);
	delta = samplepixels/ncycles;
	alpha = initalpha;
	radius = initradius;

	rad = radius >> radiusbiasshift;
	if (rad <= 1) rad = 0;
	for (i=0; i<rad; i++)
		radpower[i] = alpha*(((rad*rad - i*i)*radbias)/(rad*rad));


	if ((lengthcount%prime1) != 0) step = 3*prime1;
	else {
		if ((lengthcount%prime2) !=0) step = 3*prime2;
		else {
			if ((lengthcount%prime3) !=0) step = 3*prime3;
			else step = 3*prime4;
		}
	}

	i = 0;
	while (i < samplepixels) {
		b = p[0] << netbiasshift;
		g = p[1] << netbiasshift;
		r = p[2] << netbiasshift;
		j = contest(b,g,r);

		altersingle(alpha,j,b,g,r);
		if (rad) alterneigh(rad,j,b,g,r);

		p += step;
		if (p >= lim) p -= lengthcount;

		i++;
		if (i%delta == 0) {
			alpha -= alpha / alphadec;
			radius -= radius / radiusdec;
			rad = radius >> radiusbiasshift;
			if (rad <= 1) rad = 0;
			for (j=0; j<rad; j++)
				radpower[j] = alpha*(((rad*rad - j*j)*radbias)/(rad*rad));
		}
	}

	return;
}
