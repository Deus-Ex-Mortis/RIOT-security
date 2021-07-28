# RIOT-AKA MODEL
Questo è un server coap utilizzato per testare l'autenticazione tramite il modello RIOT-AKA su dispositivi IOT.
## Configurazione dispositivo
Può essere utilizzato esclusivamente su una board fisica ed è stato testato su nrf52840dk, altre schede potrebbero non avere abbastanza RAM e/o memoria flash.
Posizionarsi all'interno della cartella RIOT e digitare il seguente comando:

`sudo dist/tools/ethos/setup_network.sh riot0 2001:db8::/64`

Questo creerà un'interfaccia tap chiamata riot0, di proprietà dell'utente. Eseguirà anche un'istanza di uhcpcd, che inizia a servire il prefisso `2001:db8::/64`. Tenere la shell aperta finché serve la rete.
Successivamente, in un altro terminale, digitare:

`sudo ip address add 2001:db8::1/128 dev riot0`

Il quale aggiunge un indirizzo instradabile sull'interfaccia host riot0.
## Avvio del server
Posizionarsi all'interno della cartella `/RIOT/examples/gcoap_server` e compilare il server col seguente comando:

`sudo BOARD=nrf52840dk make clean flash all term -j4`

A questo punto il server coap sarà avviato e per testarlo sarà necessario utilizzare [aiocoap](https://github.com/Deus-Ex-Mortis/Aiocoap).
