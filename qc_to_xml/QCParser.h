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
#include <iostream>

#include "Entry.h"

class QCParser
{
private:

public:
	explicit QCParser(const std::string& content) : m_content(content) {}
	static void setTags(const std::string& tag_begin, const std::string& tag_end) {s_tag_begin = tag_begin; s_tag_end = tag_end;}

	std::vector<std::string> operator()();
private:
	std::string findOneEntry(/*inout*/ int& pos);
	std::vector<Entry> findEntries();
	void parse(const std::string& s, /*out*/ Entry& entry);
	std::vector<std::string> toXml(const std::vector<Entry>& entries);
	std::string toXml(const Entry& entry);

private:
	std::string m_content;
	static std::string s_tag_begin, s_tag_end;
};