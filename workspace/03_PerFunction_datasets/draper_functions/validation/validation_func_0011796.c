genus(int mndx, int mode)
{
    switch (mndx)
    {

    case PM_STUDENT:     mndx = mode ? PM_ARCHEOLOGIST  : PM_HUMAN; break;
    case PM_CHIEFTAIN:   mndx = mode ? PM_BARBARIAN : PM_HUMAN; break;
    case PM_NEANDERTHAL: mndx = mode ? PM_CAVEMAN   : PM_HUMAN; break;
    case PM_ATTENDANT:   mndx = mode ? PM_HEALER    : PM_HUMAN; break;
    case PM_PAGE:        mndx = mode ? PM_KNIGHT    : PM_HUMAN; break;
    case PM_ABBOT:       mndx = mode ? PM_MONK      : PM_HUMAN; break;
    case PM_ACOLYTE:     mndx = mode ? PM_PRIEST    : PM_HUMAN; break;
    case PM_HUNTER:      mndx = mode ? PM_RANGER    : PM_HUMAN; break;
    case PM_THUG:        mndx = mode ? PM_ROGUE     : PM_HUMAN; break;
    case PM_ROSHI:       mndx = mode ? PM_SAMURAI   : PM_HUMAN; break;
    case PM_GUIDE:       mndx = mode ? PM_TOURIST   : PM_HUMAN; break;
    case PM_APPRENTICE:  mndx = mode ? PM_WIZARD    : PM_HUMAN; break;
    case PM_WARRIOR:     mndx = mode ? PM_VALKYRIE  : PM_HUMAN; break;
    default:
                         if (mndx >= LOW_PM && mndx < NUMMONS)
                         {
                             struct permonst *ptr = &mons[mndx];
                             if (is_human(ptr))      mndx = PM_HUMAN;
                             else if (is_elf(ptr))   mndx = PM_ELF;
                             else if (is_dwarf(ptr)) mndx = PM_DWARF;
                             else if (is_gnome(ptr)) mndx = PM_GNOME;
                             else if (is_orc(ptr))   mndx = PM_ORC;
                         }
                         break;
    }
    return mndx;
}
