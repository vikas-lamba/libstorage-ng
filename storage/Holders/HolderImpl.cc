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


#include "storage/Holders/HolderImpl.h"
#include "storage/Devicegraph.h"
#include "storage/Utils/XmlFile.h"


namespace storage
{

    Holder::Impl::Impl()
	: devicegraph(nullptr)
    {
    }


    Holder::Impl::Impl(const xmlNode* node)
	: devicegraph(nullptr)
    {
    }


    bool
    Holder::Impl::operator==(const Impl& rhs) const
    {
	if (typeid(*this) != typeid(rhs))
	    return false;

	return equal(rhs);
    }


    Holder*
    Holder::Impl::copy_to_devicegraph(Devicegraph* devicegraph) const
    {
	sid_t source_sid = get_source_sid();
	sid_t target_sid = get_target_sid();

	if (!devicegraph->device_exists(source_sid))
	    ST_THROW(Exception("source device does not exist"));

	if (!devicegraph->device_exists(target_sid))
	    ST_THROW(Exception("target device does not exist"));

	if (devicegraph->holder_exists(source_sid, target_sid))
	    ST_THROW(Exception("holder already exists"));

	Devicegraph::Impl::vertex_descriptor source = devicegraph->get_impl().find_vertex(source_sid);
	Devicegraph::Impl::vertex_descriptor target = devicegraph->get_impl().find_vertex(target_sid);

	Holder* holder = get_non_impl()->clone();

	Devicegraph::Impl::edge_descriptor edge = devicegraph->get_impl().add_edge(source, target, holder);
	holder->get_impl().set_devicegraph_and_edge(devicegraph, edge);

	return holder;
    }


    void
    Holder::Impl::set_devicegraph_and_edge(Devicegraph* devicegraph,
					   Devicegraph::Impl::edge_descriptor edge)
    {
	Impl::devicegraph = devicegraph;
	Impl::edge = edge;

	const Holder* holder = devicegraph->get_impl()[edge];
	if (&holder->get_impl() != this)
	    ST_THROW(LogicException("wrong edge for back references"));
    }


    void
    Holder::Impl::set_edge(Devicegraph::Impl::edge_descriptor edge)
    {
	Impl::edge = edge;

	const Holder* holder = devicegraph->get_impl()[edge];
	if (&holder->get_impl() != this)
	    ST_THROW(LogicException("wrong edge for back references"));
    }


    Device*
    Holder::Impl::get_source()
    {
	Devicegraph::Impl::vertex_descriptor source = devicegraph->get_impl().source(edge);
	return devicegraph->get_impl()[source];
    }


    const Device*
    Holder::Impl::get_source() const
    {
	Devicegraph::Impl::vertex_descriptor source = devicegraph->get_impl().source(edge);
	return devicegraph->get_impl()[source];
    }


    sid_t
    Holder::Impl::get_source_sid() const
    {
	return get_source()->get_sid();
    }


    Device*
    Holder::Impl::get_target()
    {
	Devicegraph::Impl::vertex_descriptor target = devicegraph->get_impl().target(edge);
	return devicegraph->get_impl()[target];
    }


    const Device*
    Holder::Impl::get_target() const
    {
	Devicegraph::Impl::vertex_descriptor target = devicegraph->get_impl().target(edge);
	return devicegraph->get_impl()[target];
    }


    sid_t
    Holder::Impl::get_target_sid() const
    {
	return get_target()->get_sid();
    }


    void
    Holder::Impl::save(xmlNode* node) const
    {
	setChildValue(node, "source-sid", get_source_sid());
	setChildValue(node, "target-sid", get_target_sid());
    }


    bool
    Holder::Impl::equal(const Impl& rhs) const
    {
	// TODO handle source and target sid here?

	return true;
    }


    void
    Holder::Impl::log_diff(std::ostream& log, const Impl& rhs) const
    {
	// TODO handle source and target sid here?
    }


    void
    Holder::Impl::print(std::ostream& out) const
    {
	out << get_classname() << " source-sid:" << get_source_sid()
	    << " target-sid:" << get_target_sid();
    }

}
