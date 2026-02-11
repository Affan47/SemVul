mondied(struct monst *mdef)
{
    mondead(mdef);
    if (mdef->mhp > 0) return;

    if (corpse_chance(mdef, (struct monst *)0, false) &&
        (accessible(mdef->mx, mdef->my) || is_pool(mdef->mx, mdef->my)))
            make_corpse(mdef);
}
