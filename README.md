# POC Zabbix perl module

Debian Jessie (8):

```
# Zabbix source
apt-get update
apt-get install -y install perl libperl-dev
apt-get install -y wget autoconf automake gcc subversion make pkg-config
mkdir /zabbix30
cd /zabbix30
svn co svn://svn.zabbix.com/branches/3.0 .
./bootstrap.sh
./configure --enable-agent

# Perl module
mkdir -p /root/git
cd /root/git
git clone https://github.com/jangaraj/zabbix-embedded-perl-module
cd zabbix-embedded-perl-module
cp -f echo*.pl /
make

# test
zabbix_get -s 127.0.0.1 -k perl.run[/echo.pl];
tailf /tmp/zabbix_agentd.log
export cc=1; while true; do echo $cc; cc=$((cc+1)); sleep 1;zabbix_get -s 127.0.0.1 -k perl.run[/echo.pl]; done
```
