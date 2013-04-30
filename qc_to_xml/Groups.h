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

#pragma once

#include <string>
#include <vector>
#include <map>

#include <boost/any.hpp>

struct Index
{
	int numDefs;
	int numGroups;
	std::string models_path;
};

struct Group
{
	typedef std::map<std::string, boost::any> Attribute;
	struct Key
	{
		//TODO: must be enum
		std::string type;
		std::string key_name;
		std::string display_name;
		std::string description;
	};

	std::string name;
};

class Groups
{
public:
	Groups(const std::string& groups_file);
	void operator()(Index& index, std::vector<Group>& groups);

	~Groups(void);

private:
	std::string		m_fileContent;
};

