HoverRowSlot(const int row)
{
    if (row > -1)
    {
        GamesListModel* glm = GetCurModel();
        if (glm != NULL)
        {
            SetGameProperties(glm->GetGameAt(row));
        }
        else
        {
            SetGameProperties(NULL);
        }
    }
    else
    {
        SetGameProperties(NULL);
    }
}
