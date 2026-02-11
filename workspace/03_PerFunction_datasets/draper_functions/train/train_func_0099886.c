Writeout(Aoutfile *f)
{
	if (itemtype != -1) f->PutStr(ItemDefs[itemtype].abr);
	else f->PutStr("NO_ITEM");
	f->PutInt(amount);
	f->PutInt(baseamount);
	if (itemtype == I_SILVER) {
		if (skill != -1) f->PutStr(SkillDefs[skill].abbr);
		else f->PutStr("NO_SKILL");
	}
	f->PutInt(productivity);
}
