baseCmp(unsigned char c1, unsigned char c2)


{
#define COMPARABLE_BASES 5

    if (c1==c2) return 0;

    if (c2<c1)
    {
        int c3 = c1;

        c1 = c2;
        c2 = c3;
    }

    if (c2<=COMPARABLE_BASES)
    {
        awtc_assert(c1<=COMPARABLE_BASES);

        switch(c1)
        {
            case 0: return 2;
            case 1: return cheap_if(c2==3);
            case 2: return cheap_if(c2==4 || c2==5);
            case 3: return cheap_if(c2==1);
            case 4: if (c2==5) return 0;
            case 5: if (c2==4) return 0;
                return cheap_if(c2==2);
            default: awtc_assert(0);
        }
    }

    int i;
    int bestMatch = 3;

    if (c1<=COMPARABLE_BASES)
    {
        for (i=1; i<=COMPARABLE_BASES; i++)
        {
            if (isalpha(nucleic_maybe[i][c2]))
            {
                int match = baseCmp(c1,i);
                if (match<bestMatch) bestMatch = match;
            }
        }
    }
    else
    {
        for (i=1; i<=COMPARABLE_BASES; i++)
        {
            if (isalpha(nucleic_maybe[i][c1]))
            {
                int match = baseCmp(i,c2);
                if (match<bestMatch) bestMatch = match;
            }
        }
    }

    awtc_assert(bestMatch>=0 && bestMatch<=2);
    return bestMatch;
}
