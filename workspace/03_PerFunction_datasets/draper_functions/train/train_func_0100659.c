OnStartEditing (gcpOrbitalProps *dlg)
{
	if (dlg->m_Node)
		xmlFree (dlg->m_Node);
	dlg->m_Coef = dlg->m_Orbital->GetCoef ();
	dlg->m_Rotation = dlg->m_Orbital->GetRotation ();
	dlg->m_Type = dlg->m_Orbital->GetType ();
	gcu::Object *obj = dlg->m_Orbital->GetGroup ();
	dlg->m_Node = obj->Save (gcp::pXmlDoc);
}
