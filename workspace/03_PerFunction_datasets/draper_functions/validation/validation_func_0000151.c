buildin_getskilllist(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int i,j=0,k=0;

	if(!sd)
		return 0;
	for(i=0;i<MAX_PCSKILL;i++){
		if(sd->status.skill[i].id <= 0 || sd->status.skill[i].lv <= 0)
			continue;
		if(j >= 128) {
			j=0;
			k++;
		}
		if(k == 0) {
			pc_setreg(sd,add_str("@skilllist_id")+(j<<24),sd->status.skill[i].id);
			pc_setreg(sd,add_str("@skilllist_lv")+(j<<24),sd->status.skill[i].lv);
			pc_setreg(sd,add_str("@skilllist_flag")+(j<<24),sd->status.skill[i].flag);
		} else {
			char buf[32];
			sprintf(buf,"@skilllist_id[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].id);
			sprintf(buf,"@skilllist_lv[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].lv);
			sprintf(buf,"@skilllist_flag[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].flag);
		}
		j++;
	}
	pc_setreg(sd,add_str("@skilllist_count"),k*128+j);
	return 0;
}
