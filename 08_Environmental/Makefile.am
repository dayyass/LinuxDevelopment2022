CFLAGS = -Wall -O0 -g

bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c

TESTS=test_no_alg_name.sh test_no_msg.sh test_unknown_hash_name.sh test_no_file.sh \
test_md5_base64.sh test_md5_hex.sh test_md5_file.sh \
test_sha1_base64.sh test_sha1_hex.sh test_sha1_file.sh \
test_tth_base64.sh test_tth_hex.sh test_tth_file.sh

test_no_alg_name.sh:
	echo 'test "`echo | ./rhasher 2>&1`" = "Error occurred while parsing hash algorithm name."' > $@
	chmod +x $@

test_no_msg.sh:
	echo 'test "`echo md5 | ./rhasher 2>&1`" = "Error occurred while parsing message to hash."' > $@
	chmod +x $@

test_unknown_hash_name.sh:
	echo 'test "`echo qwqqwe \\\"123 | ./rhasher 2>&1`" = "Unknown name of hash algorithm."' > $@
	chmod +x $@

test_no_file.sh:
	echo 'test "`echo md5 11232qwew23 | ./rhasher 2>&1`" = "LibRHash error: 11232qwew23: No such file or directory."' > $@
	chmod +x $@

test_md5_base64.sh:
	echo 'test "`echo md5 \\\"123 | ./rhasher 2>&1`" = "4TdS017y31Cp/XYs+3roLQ=="' > $@
	chmod +x $@

test_md5_hex.sh:
	echo 'test "`echo MD5 \\\"123 | ./rhasher 2>&1`" = "`md5 -q -s \\\"123`"' > $@
	chmod +x $@

test_md5_file.sh:
	echo 'test "`echo MD5 configure.ac | ./rhasher 2>&1`" = "`md5 -q configure.ac`"' > $@
	chmod +x $@

test_sha1_base64.sh:
	echo 'test "`echo sha1 \\\"123 | ./rhasher 2>&1`" = "Y5wXHwhIg/Rs4sOoc6NBkfN5RbQ="' > $@
	chmod +x $@

test_sha1_hex.sh:
	echo 'test "`echo SHA1 \\\"123 | ./rhasher 2>&1`" = "`printf \\\"123 | shasum | cut -d \" \" -f1`"' > $@
	chmod +x $@

test_sha1_file.sh:
	echo 'test "`echo SHA1 configure.ac | ./rhasher 2>&1`" = "`shasum configure.ac | cut -d \" \" -f1`"' > $@
	chmod +x $@

test_tth_base64.sh:
	echo 'test "`echo tth \\\"123 | ./rhasher 2>&1`" = "9h1uzp/TmYm+q8YBW+MQawAYpKTS1QKU"' > $@
	chmod +x $@

test_tth_hex.sh:
	echo 'test "`echo TTH \\\"123 | ./rhasher 2>&1`" = "f61d6ece9fd39989beabc6015be3106b0018a4a4d2d50294"' > $@
	chmod +x $@

test_tth_file.sh:
	echo 'test "`echo TTH configure.ac | ./rhasher 2>&1`" = "69fade628306cc2dd02686c644b11cde335e7ffd91c229b6"' > $@
	chmod +x $@

clean: maintainer-clean
	rm -rf $(TESTS)
