IsGuarded()
{
	forlist (&objects) {
		Object *o = (Object *) elem;
		forlist (&o->units) {
			Unit *u = (Unit *) elem;
			if (u->guard == GUARD_GUARD) return 1;
		}
	}
	return 0;
}
