#!/bin/bash
wget "https://www.pbinfo.ro/ajx-module/profil/json-jurnal.php?user=Eric_12" -O ./EriccT &> /dev/null && {

sed -i -e 's/,"meta".*//g' ./EriccT

diff -q ./EriccT ./Ericc || { 

	cat EriccT | sed -e 's/}/}\n/g' -e 's/:\[/\n/g';

	cp ./EriccT ./Ericc

}

rm EriccT;

};
