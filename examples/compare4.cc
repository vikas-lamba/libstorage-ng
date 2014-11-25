

#include "storage/Devices/Disk.h"
#include "storage/Devices/Gpt.h"
#include "storage/Devices/Partition.h"
#include "storage/Devices/LvmVg.h"
#include "storage/DeviceGraph.h"
#include "storage/Action.h"


using namespace storage;


int
main()
{
    DeviceGraph lhs;

    new Disk(lhs, "/dev/sda");

    DeviceGraph rhs;
    lhs.copy(rhs);

    Disk* rhs_sda = dynamic_cast<Disk*>(BlkDevice::find(rhs, "/dev/sda"));

    Gpt* rhs_gpt = new Gpt(rhs);
    new Subdevice(rhs, rhs_sda, rhs_gpt);

    Partition* rhs_sda1 = new Partition(rhs, "/dev/sda1");
    new Subdevice(rhs, rhs_gpt, rhs_sda1);

    Partition* rhs_sda2 = new Partition(rhs, "/dev/sda2");
    new Subdevice(rhs, rhs_gpt, rhs_sda2);

    Partition* rhs_sda3 = new Partition(rhs, "/dev/sda3");
    new Subdevice(rhs, rhs_gpt, rhs_sda3);

    LvmVg* rhs_system = new LvmVg(rhs, "/dev/system");
    new Subdevice(rhs, rhs_sda1, rhs_system);
    new Subdevice(rhs, rhs_sda2, rhs_system);
    new Subdevice(rhs, rhs_sda3, rhs_system);

    rhs.write_graphviz("compare4-device-rhs");

    ActionGraph action_graph(lhs, rhs);

    action_graph.write_graphviz("compare4-action");
}
