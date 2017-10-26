#!/bin/bash
set -e
set -x

ip netns add ns1
ip netns add ns2
ip netns add ns3

ip link add bp1 type veth peer name eth0 netns ns1
ip link add bp2 type veth peer name eth0 netns ns2
ip link add bp3 type veth peer name eth0 netns ns3

ip link add br0 type bridge
ip link set bp1 master br0
ip link set bp2 master br0
ip link set bp3 master br0

ip link set br0 up
ip link set bp1 up
ip link set bp2 up
ip link set bp3 up

ip netns exec ns1 ip address add 10.0.0.11/24 dev eth0
ip netns exec ns1 ip link set eth0 up
ip netns exec ns2 ip address add 10.0.0.12/24 dev eth0
ip netns exec ns2 ip link set eth0 up
ip netns exec ns3 ip address add 10.0.0.13/24 dev eth0
ip netns exec ns3 ip link set eth0 up
