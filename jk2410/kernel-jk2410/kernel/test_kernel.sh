#!/bin/sh

make dep
make Image
chmod a+x mkimage
./mkimage -A arm -O linux -T kernel -C none -a 0x30008000 -e 0x30008000 -n linux -d arch/arm/boot/Image uimage.img
cp uimage.img ../qemu-jk2410-prebuilt/jk2410/uimage.img
cd ../qemu-jk2410-prebuilt/
./run.sh
