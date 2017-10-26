#!/bin/bash
set -e
set -x

ip netns add ns1
ip link add veth0 type veth peer name eth0 netns ns1
ip address add 10.0.0.1/24 dev veth0
ip link set veth0 up

ip netns exec ns1 ip address add 10.0.0.11/24 dev eth0
ip netns exec ns1 ip link set eth0 up
