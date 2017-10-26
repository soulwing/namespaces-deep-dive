#!/bin/sh
set -e
set -x
ip netns del ns1
ip netns del ns2
ip netns del ns3
ip link del br0
