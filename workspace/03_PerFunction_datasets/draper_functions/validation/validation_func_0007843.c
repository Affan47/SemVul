Close(void) {


    if ( IsOpen ) {
        fclose(Stream);
        IsOpen = false;
    }


    if ( HasIndex && IsIndexOpen ) {
        fclose(IndexStream);
        HasIndex = false;
        IsIndexOpen = false;
    }


    return true;
}
