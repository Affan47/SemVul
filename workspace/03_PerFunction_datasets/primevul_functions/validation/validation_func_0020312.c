PasswordInvalid (
  VOID
  )
{
  EFI_INPUT_KEY  Key;


  do {
    CreateDialog (&Key, gEmptyString, gPassowordInvalid, gPressEnter, gEmptyString, NULL);
  } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);
}
