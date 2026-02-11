buildin_mobuseskill_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	struct block_list *tbl;
	int mob_id   = va_arg(ap,int);
	int skillid  = va_arg(ap,int);
	int skilllv  = va_arg(ap,int);
	int casttime = va_arg(ap,int);
	int cancel   = va_arg(ap,int);
	int eff_id   = va_arg(ap,int);
	int target   = va_arg(ap,int);

	nullpo_retr(0, md = (struct mob_data *)bl);

	if(mob_id > 0 && md->class_ != mob_id)
		return 0;
	if(skillid <= 0 || skilllv <= 0)
		return 0;

	switch(target) {
		case 0:  tbl = map_id2bl(md->bl.id); break;
		case 1:  tbl = map_id2bl(md->target_id); break;
		case 2:  tbl = map_id2bl(md->master_id); break;
		default: tbl = mob_selecttarget(md, skill_get_fixed_range(&md->bl,skillid,skilllv)); break;
	}

	if(!tbl)
		return 0;

	if(md->ud.skilltimer != -1)
		unit_skillcastcancel(bl,0);

	if(skill_get_inf(skillid) & INF_GROUND)
		unit_skilluse_pos2(&md->bl, tbl->x, tbl->y, skillid, skilllv, casttime, cancel);
	else
		unit_skilluse_id2(&md->bl, tbl->id, skillid, skilllv, casttime, cancel);

	if(eff_id > 0)
		mob_talk(md, eff_id);
	else
		clif_emotion(&md->bl, -1 * eff_id);

	return 0;
}
