#!/bin/sh
set -x
ip netns del ns1
ip netns del ns2
ip netns del ns3
ip link del br0
ip link del veth0
ip link del vxlan0
iptables -t nat -F
sysctl -w net.ipv4.ip_forward=0
