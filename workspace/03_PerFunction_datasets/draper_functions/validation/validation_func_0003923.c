KillDead(Location * l)
{
	if (!l->unit->IsAlive()) {
		l->region->Kill(l->unit);
	} else {
		if (l->unit->advancefrom) {
			l->unit->MoveUnit( l->unit->advancefrom->GetDummy() );
		}
	}
}
