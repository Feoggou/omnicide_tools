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
#include <map>

struct Key
{
	//TODO: enum?
	std::string type;

	std::string name;
	std::string default_value;
	std::string description;
};

struct Flag
{
	//TODO: int?
	std::string bit;

	std::string key;
	std::string name;
	std::string description;
};

struct Entry
{
	std::map<std::string, std::string> normal_keys;
	std::map<std::string, Key> keys;
	std::map<std::string, Flag> flags;

	void readItem(const std::string& line);
	bool haveKeyOrFlag() const {return !keys.empty() || !flags.empty();}

private:
	void readKey(const std::string& value, /*out*/ Key& key);
	void readFlag(const std::string& value, /*out*/ Flag& flag);
};