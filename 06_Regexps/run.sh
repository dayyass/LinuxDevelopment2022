#!/bin/sh

make clean; autoreconf -fisv && ./configure && make && make check

