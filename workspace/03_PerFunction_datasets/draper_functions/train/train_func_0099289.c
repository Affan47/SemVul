A_BeastPuff(mobj_t * actor)
{
    if (P_Random() > 64)
    {
        P_SpawnMobj(actor->x + ((P_Random() - P_Random()) << 10),
                    actor->y + ((P_Random() - P_Random()) << 10),
                    actor->z + ((P_Random() - P_Random()) << 10), MT_PUFFY);
    }
}
