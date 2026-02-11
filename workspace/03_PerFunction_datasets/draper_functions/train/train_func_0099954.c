AddQuadToHash(HashTable h, int p, int q, int r, int s, int *nQuad)
{
    struct hash hash;

    SetupQuad(p, q, r, s, &hash);

    if (_QueryHash(h, &hash))
	return OK;

    hash.index = *nQuad;
    *nQuad = *nQuad + 1;

    return DXInsertHashElement(h, (Element)&hash);
}
