borg_spell_okay(int book, int what)
{
    int reserve_mana = 0;

    borg_magic *as = &borg_magics[book][what];


    if (no_light()) return (FALSE);


    if (borg_class == CLASS_MAGE) reserve_mana = 6;
    if (borg_class == CLASS_RANGER) reserve_mana = 22;
    if (borg_class == CLASS_ROGUE) reserve_mana = 20;


    if (borg_skill[BI_CLEVEL] < 35) reserve_mana = 0;


    if (!borg_spell_legal(book, what)) return (FALSE);


    if (borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED]) return (FALSE);


    if (as->power > borg_skill[BI_CURSP]) return (FALSE);


    if (borg_skill[BI_CURSP] - as->power < reserve_mana)
    {

        if (book == 0 && what == 2) return (TRUE);


        if (book == 1 && what == 5) return (TRUE);


        if (book == 2 && what == 0) return (TRUE);


        if (book == 0 && what == 0 && borg_skill[BI_CDEPTH] <= 35) return (TRUE);


        return (FALSE);
    }


    return (TRUE);
}
