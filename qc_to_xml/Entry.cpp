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

#include "Entry.h"
//#include "string.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

void Entry::readItem(const std::string& line)
{
	int equal_pos = line.find('=', 0);
	if (equal_pos == -1)
		return;

	std::string left = line.substr(0, equal_pos);
	boost::trim(left);

	std::string right = line.substr(equal_pos + 1);
	boost::trim(right);

	if (*right.rbegin() == ';') {
		right.pop_back();
	}

	if (left == "key") {
		Key key;
		readKey(right, /*out*/ key);
		keys.insert(std::make_pair(left, key));

	} else if (left == "flag") {
		Flag flag;
		readFlag(right, /*out*/ flag);
		flags.insert(std::make_pair(left, flag));
	} else if (!left.empty()) {
		std::pair<std::string, std::string> pair(left, right);
		normal_keys.insert(pair);
	}
}

void Entry::readKey(const std::string& value, /*out*/ Key& key)
{
	// type
	int pos = value.find('\\');
	if (pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	key.type = value.substr(0, pos);

	//name
	int old_pos = pos + 1;
	int new_pos = value.find('\\', old_pos);
	if (new_pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	key.name = value.substr(old_pos, new_pos);

	//default value
	old_pos = new_pos + 1;
	new_pos = value.find('\\', old_pos);
	if (new_pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	key.default_value = value.substr(old_pos, new_pos);

	//description
	old_pos = new_pos + 1;

	key.default_value = value.substr(old_pos);
}

void Entry::readFlag(const std::string& value, /*out*/ Flag& flag)
{
	// bit
	int pos = value.find('\\');
	if (pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	flag.bit = value.substr(0, pos);

	//key
	int old_pos = pos + 1;
	int new_pos = value.find('\\', old_pos);
	if (new_pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	flag.key = value.substr(old_pos, new_pos);

	//name
	old_pos = new_pos + 1;
	new_pos = value.find('\\', old_pos);
	if (new_pos < 0)
		std::cerr << "error: expected \\\\" << std::endl;

	flag.name = value.substr(old_pos, new_pos);

	//description
	old_pos = new_pos + 1;

	flag.description = value.substr(old_pos);
}