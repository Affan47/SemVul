setEditableParams(EditableParams params)
{
    ui->editor->setLabelVisible(params.testFlag(Label));
    ui->editor->setCategoryVisible(params.testFlag(Category));
    ui->editor->setDescriptionVisible(params.testFlag(Description));
    ui->editor->setIconVisible(params.testFlag(Icon));
    ui->editor->setRelationVisible(params.testFlag(Relation));
    ui->editor->setViewTypeVisible(params.testFlag(ViewType));
    ui->editor->setContentTypeVisible(params.testFlag(ContentType));
    ui->editor->setPriorityVisible(params.testFlag(Priority));
    ui->editor->setOverridingCommentVisible(params.testFlag(OverrideNeedsComment));
    if (!(params.testFlag(Timing)))
        ui->editor->hideTimingTab();
    if (!(params.testFlag(CSS)))
        ui->editor->hideStyleSheetTab();
    if (!(params.testFlag(ExtraXml)))
        ui->editor->hideExtraXmlTab();
    if (!(params.testFlag(Scripts)))
        ui->editor->hideScriptsTab();
}
