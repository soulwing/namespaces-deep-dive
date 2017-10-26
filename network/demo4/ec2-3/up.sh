#!/bin/bash
set -e
set -x

ip netns add ns1

ip link add bp1 type veth peer name eth0 netns ns1
ip link add vxlan0 type vxlan id 100 dev eth0 dstport 4789 ttl 255

ip link add br0 type bridge
ip link set bp1 master br0
ip link set vxlan0 master br0

ip link set br0 up
ip link set bp1 up
ip link set vxlan0 up

bridge fdb append 00:00:00:00:00:00 dev vxlan0 dst 172.31.27.141
bridge fdb append 00:00:00:00:00:00 dev vxlan0 dst 172.31.2.13

ip netns exec ns1 ip address add 10.0.0.15/24 dev eth0
ip netns exec ns1 ip link set eth0 up
ip netns exec ns1 ip route add default via 10.0.0.1
