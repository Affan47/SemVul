clickday()
{
    if(!ui->label->text().isNull())
    {
        emit day(ui->label->text());

    }
}
