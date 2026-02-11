Letter(size_t vl, size_t vr, int i) const{
		char l;
		if(i==1){
			l = (char)csa->getT(vl);
			return l;
		}

		size_t p1 = vl+1;
		for(size_t j=0; j<(size_t)(i-1); j++)
			p1 = csa->getPsi(p1);


		return Letter(p1, p1,1);
	}
