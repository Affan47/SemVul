sec_pkcs5_v2_get_v2_param(PLArenaPool *arena, SECAlgorithmID *algid)
{
    PLArenaPool *localArena = NULL;
    sec_pkcs5V2Parameter *pbeV2_param;
    SECStatus rv;

    if (arena == NULL) {
	localArena = arena = PORT_NewArena(SEC_ASN1_DEFAULT_ARENA_SIZE);
	if (arena == NULL) {
	    return NULL;
	}
    }
    pbeV2_param = PORT_ArenaZNew(arena, sec_pkcs5V2Parameter);
    if (pbeV2_param == NULL) {
	goto loser;
    }

    rv = SEC_ASN1DecodeItem(arena, pbeV2_param,
		SEC_PKCS5V2ParameterTemplate, &algid->parameters);
    if (rv == SECFailure) {
	goto loser;
    }

    pbeV2_param->poolp = arena;
    return pbeV2_param;
loser:
    if (localArena) {
	PORT_FreeArena(arena, PR_FALSE);
    }
    return NULL;
}
