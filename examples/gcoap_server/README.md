# RIOT-AKA MODEL
This is a coap server used to test authentication via the RIOT-AKA model on IOT devices.

## Device configuration
It can only be used on a physical board and has been tested on nrf52840dk, other boards may not have enough RAM and/or flash memory.
Go inside the folder `/RIOT/examples/gcoap_server` and:

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
