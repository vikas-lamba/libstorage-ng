#ifndef DEVICE_H
#define DEVICE_H


#include <stdint.h>
#include <libxml/tree.h>
#include <string>
#include <vector>
#include <map>
#include <memory>


namespace storage
{
    class Devicegraph;


    // The storage id (sid) is used to identify devices.  The sid is copied
    // when copying the device graph.  When adding a device it gets a unique
    // sid (across all device graphs).  By using the storage id instead of a
    // device name we can easily identify devices where the device name
    // changed, e.g. renumbered logical partitions or renamed logical volumes.
    // Also some devices do not have a intrinsic device name, e.g. btrfs.  We
    // could even have objects for unused space, e.g. space between partitions
    // or unallocated space of a volume group.

    typedef uint32_t sid_t;


    // The Device class does not have a device name since some device types do
    // not have a intrinsic device name, e.g. btrfs.  Instead most devices are
    // derived from BlkDevice which has a device name, major and minor number,
    // udev id and udev path.


    // abstract class

    class Device
    {

    public:

	virtual ~Device();

	sid_t get_sid() const;

	bool operator==(const Device& rhs) const;
	bool operator!=(const Device& rhs) const;

	virtual std::string get_displayname() const = 0;

	virtual void check() const;

	size_t num_children() const;
	size_t num_parents() const;

	// TODO check if we can somehow return a iterator. getting rid of the
	// ptr would also allow to use references instead of pointer in the
	// interface.
	std::vector<const Device*> get_children() const;
	std::vector<const Device*> get_parents() const;
	std::vector<const Device*> get_siblings(bool itself) const;
	std::vector<const Device*> get_descendants(bool itself) const;
	std::vector<const Device*> get_ancestors(bool itself) const;
	std::vector<const Device*> get_leafs(bool itself) const;
	std::vector<const Device*> get_roots(bool itself) const;

	const std::map<std::string, std::string>& get_userdata() const;
	void set_userdata(const std::map<std::string, std::string>& userdata);

	friend std::ostream& operator<<(std::ostream& out, const Device& device);

    public:

	class Impl;

	Impl& get_impl() { return *impl; }
	const Impl& get_impl() const { return *impl; }

	virtual const char* get_classname() const = 0;

	virtual Device* clone() const = 0;

	void save(xmlNode* node) const;

    protected:

	Device(Impl* impl);

	void create(Devicegraph* devicegraph);
	void load(Devicegraph* devicegraph);

	virtual void print(std::ostream& out) const = 0;

    private:

	void add_to_devicegraph(Devicegraph* devicegraph);

	std::shared_ptr<Impl> impl;

    };

}

#endif
