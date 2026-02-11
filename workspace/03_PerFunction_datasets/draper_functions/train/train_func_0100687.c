ReadFirstChild( GDALJP2Box *poSuperBox )

{
    szBoxType[0] = '\0';
    if( !poSuperBox->IsSuperBox() )
        return FALSE;

    return SetOffset( poSuperBox->nDataOffset ) && ReadBox();
}
