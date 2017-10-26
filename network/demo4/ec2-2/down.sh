#!/bin/sh
set -x
ip netns del ns1
ip link del br0
ip link del vxlan0
