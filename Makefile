zabbix_module_perl: zabbix_module_perl.c
	rm -rf zabbix_module_perl.so /tmp/zabbix_module_perl.so 
	pkill -9 zabbix_agentd || true
	rm -rf /tmp/zabbix_agentd.pid
	> /tmp/zabbix_agentd.log
	gcc -fPIC -shared -o zabbix_module_perl.so zabbix_module_perl.c -I../../../../zabbix30/include -I/usr/lib/perl/5.18.2/CORE `perl -MExtUtils::Embed -e ccopts -e ldopts`
	cp zabbix_module_perl.so /tmp
	chmod 777 /tmp/zabbix_module_perl.so
	sleep 2
	zabbix_agentd -c /root/git/zabbix-perl-module/zabbix_agentd.conf
	ps -ef | grep zabbix_agentd



