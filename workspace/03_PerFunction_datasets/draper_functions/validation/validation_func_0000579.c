resort(int start)
{
	int newpos;
	TRANSLATION moveme=badcache[start];

	if(maxbad<2)
		return;


	if(start>0){
		newpos=start-1;
		while(newpos>=0){
			if(badcache[newpos]->incorrect < moveme->incorrect){
				newpos-=1;
			} else break;
		}
		if(newpos < start-1){
			insert(newpos+1, start, badcache[start]);
			maxbad--;
			return;
		}
	}


	newpos=start+1;
	while(newpos<maxbad){
		if(badcache[newpos]->incorrect >= moveme->incorrect){
			newpos++;
		} else break;
	}
	if(newpos>start+1){
		deletepos(start, newpos);
		newpos-=1;
		badcache[newpos]=moveme;
	}
}
