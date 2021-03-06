#!/usr/bin/python3

# requirements: nfs server dist exporting path dist


from storage import *
from storageitu import *


set_logger(get_logfile_logger())

environment = Environment(False)

storage = Storage(environment)
storage.probe()

staging = storage.get_staging()

print(staging)

nfs = Nfs.create(staging, "dist", "/dist")

mount_point = nfs.create_mount_point("/test")

print(staging)

commit(storage)

