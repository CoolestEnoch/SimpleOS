rm init.cpio
find . | cpio -H newc -o > init.cpio