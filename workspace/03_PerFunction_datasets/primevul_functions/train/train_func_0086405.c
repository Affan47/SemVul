AP4_SampleEntry::Inspect(AP4_AtomInspector& inspector)
{

    InspectHeader(inspector);


    InspectFields(inspector);


    m_Children.Apply(AP4_AtomListInspector(inspector));


    inspector.EndAtom();

    return AP4_SUCCESS;
}
