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

#include "Groups.h"


Groups::Groups(const std::string& groups_file)
	: m_fileContent(groups_file)
{
	boost::any a = 3;
	a = std::string("ghfhg");

	std::string s = boost::any_cast<std::string>(a);
}

Groups::~Groups(void)
{
}

void Groups::operator()(Index& index, std::vector<Group>& groups)
{
	//find group: a group is: [group name] followed by content, followed by a white line.

	size_t pos0 = 0;
	size_t pos1 = m_fileContent.find('[', pos0);

	if (pos1 == -1)
		return;

	size_t left_paran = pos1;

	pos0 = pos1 + 1;
	pos1 = m_fileContent.find(']', pos0);

	if (pos1 <= 0)
		return;

	size_t right_paran = pos1;

	std::string name = m_fileContent.substr(left_paran + 1, right_paran - 1);

	if (name == "Index") {
		//loading index now
	}
}