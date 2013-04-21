// Copyright (C) 2013 Samuel Ghinet
//

// This file is part of qc_to_xml.

// qc_to_xml is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// qc_to_xml is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with qc_to_xml.  If not, see <http://www.gnu.org/licenses/>.

#include "QCParser.h"

#include <algorithm>

std::string QCParser::s_tag_begin, QCParser::s_tag_end;

std::vector<std::string> QCParser::operator()()
{
	std::vector<Entry> entries = findEntries();

	std::vector<std::string> xml_entries = toXml(entries);
	return xml_entries;
}

std::vector<std::string> QCParser::toXml(const std::vector<Entry>& entries)
{
	std::vector<std::string> xml_entries;

	std::for_each(entries.begin(), entries.end(), [&xml_entries, this](const Entry& entry){ xml_entries.push_back(toXml(entry));});

	return xml_entries;
}

std::string QCParser::toXml(const Entry& entry)
{
	//std::string begin_point = "<point name=" + light + " color=" + 0.7 0.4 0.7 + " box=" + -8 -8 -8 8 8 8 + ">";
	return "";

	/*<point name="light" color="0.7 0.4 0.7" box="-8 -8 -8 8 8 8"> Static light (used for vertex lighting, lightmap and lightgrid calculation)

 --- Keys --- 
<integer key="light" name="Light level">light level, affects radius and brightness of light. Default is 200.</integer>
<color key="_color" name="Light color">Weighted RGB value of light color. Default is 1 1 1.</color>
<integer key="_deviance" name="Deviance angle">Non-point light simulation for softer shadows, this is a degree of penumbra. Default is 0.</integer>
<integer key="_samples" name="Deviance samples">How many 'deviance' lights to spawn, good value is 6 or more. Default is 1.</integer>
<string key="target" name="Spotlight target">Lights pointed at a target will be spotlights. Use info_null as targets.</string>
<real key="radius" name="Spotlight radius">Overrides radius (in units) of a spotlight at the target point. Default is 64.</real>
<boolean key="_sun" name="Infinite sun light">Set this key to Yes on a spotlight to make an infinite sun light.</boolean>

 --- Flags --- 
<flag key="LINEAR_FALLOFF" name="Linear falloff" bit="0">Use a linear falloff. Default is inverse distance squared (more realistic)</flag>
<flag key="NO_ANGLE_FALLOFF" name="No angle attenuation" bit="1">Ignore angle attenuation</flag>
<flag key="NO_GRID" name="No Grid" bit="4">Lighting from this light does not appear in lightgrid</flag>
<flag key="UNNORMALIZED_COLOR" name="Unnormalized color" bit="5">Color of light are not normalized onload</flag>
<flag key="DISTANCE_FALLOFF" name="Distance attenuation" bit="6">Use distance-based linear attenuation (normally sun has that). May be useful for ambient area lights</flag>

</point> */
}

std::string QCParser::findOneEntry(/*inout*/ int& pos)
{
	std::string result;

	size_t posB = m_content.find(s_tag_begin, pos);

	if (posB == -1)
		return std::string();

	size_t posE = m_content.find(s_tag_end, posB + s_tag_begin.size());

	if (posE == -1)
		return std::string();

	int first = posB + s_tag_begin.size();
	int count = posE - first;
	result = m_content.substr(first, count);

	pos = posE + s_tag_end.size();

	return result;
}

std::vector<Entry> QCParser::findEntries()
{
	int pos = 0;
	std::vector<Entry> entries;

	do {
		std::string s = findOneEntry(pos);
		if (s.empty()) break;

		Entry entry;
		parse(s, entry);

		if (entry.haveKeyOrFlag())
			entries.push_back(entry);
	}while(1);

	m_content.clear();

	return entries;
}

void QCParser::parse(const std::string& s,/*out*/ Entry& entry)
{
	int pos = 0;
	while (true) {
		int eol = s.find('\n', pos);
		if (eol == -1)
			break;

		std::string line = s.substr(pos, eol - pos);

		entry.readItem(line);

		pos = eol + 1;
	}
}