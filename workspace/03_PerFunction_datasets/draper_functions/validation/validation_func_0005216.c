save(KConfigGroup* group)
{
	group->writeEntry("grade", m_grade);
	group->writeEntry("reversed", m_reversed);
	group->writeEntry("stuckOnGround", m_stuckOnGround);
	group->writeEntry("gradient", g_slopeData->gradientKeys.value(m_type));
	const QSizeF size = Tagaro::SpriteObjectItem::size();
	group->writeEntry("width", size.width());
	group->writeEntry("height", size.height());
}
