# RIOT-AKA MODEL
This is a coap server used to test authentication via the RIOT-AKA model on IOT devices.

## Device configuration
It can only be used on a physical board and has been tested on nrf52840dk, other boards may not have enough RAM and/or flash memory.
Go inside the folder `/RIOT/examples/riot_aka` and:

### On natives ONLY:


Compile the application:


```bash
make clean all -j4
```

Create a tap interface:


```bash
sudo ip tuntap add tap0 mode tap user ${USER}
sudo ip link set tap0 up
```

Start the application:

```bash
PORT=tap0 make term
```

To verify that there is connectivity between RIOT and Linux, go to the
RIOT console and run `ifconfig`:

    > ifconfig
    Iface  7   HWaddr: ce:f5:e1:c5:f7:5a
               inet6 addr: ff02::1/128  scope: local [multicast]
               inet6 addr: fe80::ccf5:e1ff:fec5:f75a/64  scope: local
               inet6 addr: ff02::1:ffc5:f75a/128  scope: local [multicast]

Copy the link-local address of the RIOT node (prefixed with `fe80`) and
try to ping it **from the Linux node**:

    ping6 fe80::ccf5:e1ff:fec5:f75a%tap0


### On nrf52840dk ONLY:

Build `ethos` and `uhcpd` with the following commands:

```bash
make -C ../../dist/tools/ethos clean all
make -C ../../dist/tools/uhcpd clean all
```

To start the tap interface type:

```bash
sudo ../../dist/tools/ethos/setup_network.sh riot0 2001:db8::/64
```

This will create a tap interface called riot0, owned by the user. It will also run an instance of uhcpcd, which starts serving the prefix `2001: db8 :: / 64`. Keep the shell running as long as you need the network.

Next, in another terminal, type:

```bash
sudo ip address add 2001:db8::1/128 dev riot0
```

Which adds a routable address on the riot0 host interface.

## Starting the server
First you have to compile the application. If you want to enable SRAM-PUF key generation support please de-comment those two lines in the Makefile:

```
FEATURES_REQUIRED += puf_sram
CFLAGS += -DPUF_SRAM
```

In any case, just type the following command to compile and flash the nrf board:

```bash
sudo BOARD=nrf52840dk make clean flash all term -j4
```

At this point the coap server will be started and to test it you will need to use [aiocoap](https://github.com/Deus-Ex-Mortis/Aiocoap).
