# UCI API

Test Config - /etc/config

```
config info artwork
	option name   '#Ghostkeepers'
	option artist 'LEE Tzu-Tung'
	option year   '2018'
```

```
# uci show test
test.artwork=info
test.artwork.name='#Ghostkeepers'
test.artwork.artist='LEE Tzu-Tung'
test.artwork.year='2018'
```

Ref: [uci_x86](https://github.com/andrewintw/uci_x86)

Build:

```
# make
rm -rf obj bin
gcc -g -Wall -Iinc -MMD -c src/main.c -o obj/main.o
gcc -g -Wall -Iinc -MMD -c src/uci_api.c -o obj/uci_api.o
gcc -g -Wall -Iinc -MMD obj/main.o obj/uci_api.o -o bin/uci_program -luci
```

Test:

```
# ./bin/uci_program test.artwork.name
UCI Value: #Ghostkeepers

# ./bin/uci_program test.artwork.year
UCI Value: 2018

# ./bin/uci_program test.artwork.artist
UCI Value: LEE Tzu-Tung

# ./bin/uci_program test.artwork.artist "Tzu-Tung Lee"
Successfully set UCI value.

# ./bin/uci_program test.artwork.artist
UCI Value: Tzu-Tung Lee

# cat /etc/config/test

config info 'artwork'
	option name '#Ghostkeepers'
	option year '2018'
	option artist 'Tzu-Tung Lee'
```
