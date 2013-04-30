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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#include "QCParser.h"
#include "Groups.h"

//usage:
//<source_file> <target_file>

void showUsage()
{
	std::cout << "usage: qc_to_xml <src_file> <target_file>\n";
}

void scan_directory(const std::string& src_name, /*out*/ std::vector<std::string>& file_names)
{
	boost::filesystem::directory_iterator dir_iter(src_name);

	while (dir_iter != boost::filesystem::directory_iterator()) {
		//boost::filesystem::directory_iterator::value_type::
		boost::filesystem::directory_entry e = *dir_iter;
		if (boost::filesystem::is_regular_file(e.path())) {
			file_names.push_back(e.path().string());
		}

		++dir_iter;
	}
}

void scan_directory_recursive(const std::string& src_name, /*out*/ std::vector<std::string>& file_names)
{
	boost::filesystem::recursive_directory_iterator dir_iter(src_name);

	while (dir_iter != boost::filesystem::recursive_directory_iterator()) {
		//boost::filesystem::directory_iterator::value_type::
		boost::filesystem::directory_entry e = *dir_iter;
		if (boost::filesystem::is_regular_file(e.path())) {
			file_names.push_back(e.path().string());
		}
	}

	++dir_iter;
}


int main(int argc, char** argv)
{
	std::string groups_filename = "D:/Projects/blood_omnicide/devkit/quakec/q3map2.ss";

	std::ifstream src_file(groups_filename, std::ios_base::in, _SH_DENYWR);
	std::string str((std::istreambuf_iterator<char>(src_file)), std::istreambuf_iterator<char>());

	Groups g(str);
	Index index;
	std::vector<Group> groups;

	g(index, groups);

	return 0;

	if (argc < 3)
		showUsage();

	QCParser::setTags("/*SS", "*/");

	std::string src_name = argv[1];
	std::string target_name = argv[2];

	std::vector<std::string> file_names;

	if (boost::filesystem::is_directory(src_name)) {
		scan_directory(src_name, file_names);

		boost::filesystem::create_directory(target_name);

		for (std::vector<std::string>::const_iterator I = file_names.begin(); I != file_names.end(); ++I) {
			std::string new_path = *I;
			new_path.replace(new_path.begin(), new_path.begin() + src_name.size(), target_name.begin(), target_name.end());

			//read file of path *I
			std::ifstream src_file(*I);
			std::string str((std::istreambuf_iterator<char>(src_file)), std::istreambuf_iterator<char>());

			//write file of path new_path
			std::ofstream dest_file(new_path, std::ios_base::trunc | std::ios_base::out);
			QCParser parser(str);
			parser();

			int x= 0;
			++x;
		}

	} else {
		std::ifstream src_file(src_name, std::ios_base::in, _SH_DENYWR);
		std::string str((std::istreambuf_iterator<char>(src_file)), std::istreambuf_iterator<char>());

		QCParser parser(str);
		parser();
	}

	return 0;
}