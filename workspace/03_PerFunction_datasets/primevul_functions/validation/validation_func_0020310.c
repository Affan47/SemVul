NewStrCat (
  IN OUT CHAR16               *Destination,
  IN     UINTN                DestMax,
  IN     CHAR16               *Source
  )
{
  UINTN Length;

  for (Length = 0; Destination[Length] != 0; Length++)
    ;


  Destination[Length] = NARROW_CHAR;
  Length++;

  StrCpyS (Destination + Length, DestMax - Length, Source);
}
