GetEditor(int index)
{
    wxCHECK_MSG((index >= 0) && (index < int(m_typeInfo.GetCount())), wxNullSheetCellEditor,
                wxT("Invalid index in wxSheetTypeRegistry::GetEditor"));
    return ((wxSheetDataTypeInfo*)m_typeInfo[index])->m_editor;
}
