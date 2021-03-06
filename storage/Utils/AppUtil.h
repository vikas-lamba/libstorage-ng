/*
 * Copyright (c) [2004-2015] Novell, Inc.
 * Copyright (c) [2016-2018] SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef STORAGE_APP_UTIL_H
#define STORAGE_APP_UTIL_H


#include <sys/time.h>
#include <sys/types.h>
#include <sstream>
#include <locale>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <regex>


namespace storage
{
    using std::string;
    using std::vector;
    using std::list;
    using std::map;
    using std::regex;

    class Arch;


void createPath(const string& Path_Cv);
bool checkNormalFile(const string& Path_Cv);
bool checkDir(const string& Path_Cv);
void checkBinPaths(const Arch& arch, bool instsys);
bool getStatMode(const string& Path_Cv, mode_t& val );
bool setStatMode(const string& Path_Cv, mode_t val );

    string dirname(const string& name);
    string basename(const string& name);

    string make_dev_block_name(dev_t majorminor);

    std::pair<string, unsigned int> device_to_name_and_number(const string& full_name);
    string name_and_number_to_device(const string& name, unsigned int number);

    vector<string> glob(const string& path, int flags);

    struct StatVfs
    {
	unsigned long long size;
	unsigned long long free;
    };

    StatVfs detect_stat_vfs(const string& path);


string extractNthWord(int Num_iv, const string& Line_Cv, bool GetRest_bi = false);

std::list<string> splitString( const string& s, const string& delChars=" \t\n",
                          bool multipleDelim=true, bool skipEmpty=true,
			  const string& quotes="" );

std::map<string,string> makeMap( const std::list<string>& l,
                                 const string& delim = "=",
				 const string& removeSur = " \t\n" );

    string udev_encode(const string&);
    string udev_decode(const string&);

    string normalizeDevice(const string& dev);


template<class StreamType>
void classic(StreamType& stream)
{
    stream.imbue(std::locale::classic());
}


    string hostname();
    string datetime(time_t t1, bool utc = true);


    /**
     * Return a string with the time in various forms, e.g. uptime and UTC, to
     * allow easy synchronisation between different logs, e.g. dmesg.
     */
    string timestamp();

    string generated_string();

    string sformat(const string& format, va_list ap);

    string sformat(const string& format, ...);


    /**
     * Pads the string s to at least width w with char c at the front.
     */
    string
    pad_front(const string& s, size_t w, char c);


    /**
     * Definition of a name schema used by format_to_name_schemata().
     */
    struct NameSchema
    {
	NameSchema(regex re, size_t w, char c) : re(re), w(w), c(c) {}

	/**
	 * Regular expression matching the name schema.
	 */
	const regex re;

	/**
	 * Width to which the sub-match will be padded.
	 */
	const size_t w;

	/**
	 * Char with which the sub-match will be padded.
	 */
	const char c;
    };


    /**
     * Formats the string s to the first matching name schema: All sub-matchs
     * will be padded as defined in the name schema.
     */
    string
    format_to_name_schemata(const string& s, const vector<NameSchema>& name_schemata);


extern const string app_ws;

}

#endif
