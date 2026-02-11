AddVariable (char *variable, char *value)
{
  if (this->Declarations == NULL)
    {
    this->SetVariable (variable, value);
    }
  else
    {
    char *newVariable = new char [strlen ("Declare ") +
                                  strlen (variable) +
                                  strlen (value) +
                                  8];

    sprintf (newVariable, "Declare \"%s\" \"%s\"\n", variable, value);
    char *oldDeclarations = this->Declarations;

    this->Declarations = new char [strlen (oldDeclarations) + strlen (newVariable) + 1];
    strcpy (this->Declarations, oldDeclarations);
    strcat (this->Declarations, newVariable);
    delete [] oldDeclarations;
    delete [] newVariable;
    this->Modified ();
    }
}
