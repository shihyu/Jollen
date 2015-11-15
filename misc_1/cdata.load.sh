#!/bin/sh
module="cdata"
device="cdata"
mode="777"

# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
insmod ./$module.ko $* || exit 1

# Group: since distributions do it differently, look for wheel or use staff
if grep -q '^staff:' /etc/group; then
   group="staff"
else
   group="wheel"
fi

#retrieve major number
#major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

major=122
echo "major number= $major"


# remove stale nodes
rm -f /dev/${device}
mknod /dev/${device}  c $major 0
echo mknod /dev/${device}  c $major 0
#ln -sf ${device} /dev/${device}

chgrp $group /dev/${device} 
chmod $mode  /dev/${device}

lsmod | grep ${device}
ls -l /dev/${device}
