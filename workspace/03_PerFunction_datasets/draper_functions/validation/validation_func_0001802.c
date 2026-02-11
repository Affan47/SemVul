ensGvindividualSetFather(EnsPGvindividual gvi,
                                EnsPGvindividual father)
{
    if (!gvi)
        return ajFalse;

    if (father &&
        (ensGvindividualGetGender(father) == ensEGvindividualGenderFemale))
        ajFatal("ensGvindividualSetFather got an "
                "Ensembl Genetic Variation Individual with gender "
                "ensEGvindividualGenderFemale.");

    ensGvindividualDel(&gvi->Father);

    gvi->Father = ensGvindividualNewRef(father);

    return ajTrue;
}
