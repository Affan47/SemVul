ivtake()
{
	int anobj,item;

	anobj = 0;
	for(item=1;item<MAXOBJ;++item) {
		if(place[item]==loc) {
			if(anobj != 0) {
				needobj();
				return;
			}
			anobj = item;
		}
	}
	if(anobj==0|| (dcheck() && dflag>=2)) {
		needobj();
		return;
	}
	object = anobj;
	vtake();
}
