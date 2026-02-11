HasSpell(uint32 spellid)
{
    for(std::vector<SpellBookEntry>::iterator i=_spells.begin(); i != _spells.end(); i++)
        if(i->id == spellid)
            return true;
    return false;
}
