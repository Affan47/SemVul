lwcompound_deserialize(uchar *serialized)
{
        LWCOMPOUND *result;
        LWGEOM_INSPECTED *insp;
        int type = lwgeom_getType(serialized[0]);
        int i;

        if(type != COMPOUNDTYPE)
        {
                lwerror("lwcompound_deserialize called on non compound: %d", type);
                return NULL;
        }

        insp = lwgeom_inspect(serialized);

        result = lwalloc(sizeof(LWCOMPOUND));
        result->type = insp->type;
        result->SRID = insp->SRID;
        result->ngeoms = insp->ngeometries;
        result->geoms = lwalloc(sizeof(LWGEOM *)*insp->ngeometries);

        if(lwgeom_hasBBOX(serialized[0]))
        {
                result->bbox = lwalloc(sizeof(BOX2DFLOAT4));
                memcpy(result->bbox, serialized + 1, sizeof(BOX2DFLOAT4));
        }
        else result->bbox = NULL;

        for(i = 0; i < insp->ngeometries; i++)
        {
                if(lwgeom_getType(insp->sub_geoms[i][0]) == LINETYPE)
                        result->geoms[i] = (LWGEOM *)lwline_deserialize(insp->sub_geoms[i]);
                else
                        result->geoms[i] = (LWGEOM *)lwcircstring_deserialize(insp->sub_geoms[i]);
                if(TYPE_NDIMS(result->geoms[i]->type) != TYPE_NDIMS(result->type))
                {
                        lwerror("Mixed dimensions (compound: %d, line/circularstring %d:%d)",
                            TYPE_NDIMS(result->type), i,
                            TYPE_NDIMS(result->geoms[i]->type)
                        );
                        lwfree(result);
                        return NULL;
                }
        }
        return result;
}
