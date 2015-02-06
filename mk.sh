## add executable permissions
chmod -f +x ./examples/nph-test.cgi
chmod -f +x ./examples/resolver.pl
chmod -f +x ./examples/cgi-test.cgi
chmod -f +x ./src/configure
chmod -f +x ./src/webindex.pl
chmod -f +x ./src/boa_indexer
chmod -f +x ./src/config.status
chmod -f +x ./src/boa


compile="arm-2440-linux-gnueabi-"
ssl_inc="/home/vince/workspace/code_reading/openssl-1.0.2/include"
ssl_libdir="/home/vince/workspace/code_reading/openssl-1.0.2"


cd ./src
if [ "x"$1 == "xclean" ];
then
	make -j16 clean
	exit $?
elif [ "x"$1 == "xdistclean" ];
then
	make -j16 distclean
	exit $?
elif [ "x"$1 == "xall" ];
then
	make -j16 distclean
	./configure
	make -j16 "CC=$compile'gcc'" "CFLAGS+=-I$ssl_inc" "LDFLAGS+=-L$ssl_libdir"\
				 "LDFLAGS+=-lssl -lcrypto"
else
	make -j16 "CC=$compile'gcc'" "CFLAGS+=-I$ssl_inc" "LDFLAGS+=-L$ssl_libdir"\
				 "LDFLAGS+=-lssl -lcrypto"
fi



## output result
if [ -x boa ];
then
$CROSS_COMPILE"strip" -s boa
echo ""
echo "-----------------------------      builed boa succeed        ------------------------------"
echo ""
exit 0
else 
echo ""
echo "-----------------------------      builed boa failed       ------------------------------"
echo ""
exit 1
fi
