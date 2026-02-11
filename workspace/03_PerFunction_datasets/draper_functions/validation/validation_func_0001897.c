rhash(const int_ugid_t uid, const int had)
{
	struct	huid	*rp, **rpp;

	for  (rpp = &uhash[(ULONG) uid % HASHMOD]; (rp = *rpp);  rpp = &rp->next)
		if  (uid == rp->uid)  {
			rp->wanted |= had;
			return  rp;
		}
	if  (!(rp = (struct huid *) malloc(sizeof(struct huid))))
		nomem();
	rp->next = (struct huid *) 0;
	rp->uid = uid;
	rp->uname = (char *) 0;
	rp->wanted = had;
	rp->charge = 0;
	*rpp = rp;
	hashed_users++;
	return  rp;
}
