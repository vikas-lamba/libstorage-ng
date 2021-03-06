/*
 * Copyright (c) [2014-2015] Novell, Inc.
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


#ifndef STORAGE_EXT3_IMPL_H
#define STORAGE_EXT3_IMPL_H


#include "storage/Filesystems/Ext3.h"
#include "storage/Filesystems/ExtImpl.h"
#include "storage/Utils/HumanString.h"


namespace storage
{

    using namespace std;


    template <> struct DeviceTraits<Ext3> { static const char* classname; };


    class Ext3::Impl : public Ext::Impl
    {
    public:

	Impl()
	    : Ext::Impl() {}

	Impl(const xmlNode* node);

	virtual unsigned long long min_size() const override { return 10 * MiB; }
	virtual unsigned long long max_size() const override { return 4 * TiB; }

	virtual bool supports_external_journal() const override { return true; }

	virtual FsType get_type() const override { return FsType::EXT3; }

	virtual const char* get_classname() const override { return DeviceTraits<Ext3>::classname; }

	virtual string get_pretty_classname() const override;

	virtual string get_displayname() const override { return "ext3"; }

	virtual Impl* clone() const override { return new Impl(*this); }

	virtual uint64_t used_features() const override;

    };

}

#endif
