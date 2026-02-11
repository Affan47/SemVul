Cbc_problemName(Cbc_Model * model, int maxNumberCharacters, char * array)
{
    const char prefix[] = "Cbc_C_Interface::Cbc_problemName(): ";

    if (VERBOSE > 0) printf("%s begin\n", prefix);

    std::string name;
    model->model_->solver()->getStrParam(OsiProbName, name);
    maxNumberCharacters = CoinMin(maxNumberCharacters, (int)strlen(name.c_str()));
    strncpy(array, name.c_str(), maxNumberCharacters - 1);
    array[maxNumberCharacters-1] = '\0';

    if (VERBOSE > 0) printf("%s return\n", prefix);
}
