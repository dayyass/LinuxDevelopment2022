CFLAGS = -Wall -O0 -g

bin_PROGRAMS=esub
esub_SOURCES=esub.c

TESTS=test_empty_regex.sh test_incorrect_regex.sh test_unknown_escaped_character.sh \
test_not_enough_groups.sh test_not_closed_escape_symbol.sh test_no_match.sh \
test_ok_1.sh test_ok_2.sh test_ok_3.sh test_ok_4.sh test_ok_5.sh

test_empty_regex.sh:
	echo 'test "`./esub \"\" \"\" \"\" 2>&1`" = "Could not compile regex: empty (sub)expression."' > $@
	chmod +x $@

test_incorrect_regex.sh:
	echo 'test "`./esub \"][\" \"\" \"\" 2>&1`" = "Could not compile regex: brackets ([ ]) not balanced."' > $@
	chmod +x $@

test_unknown_escaped_character.sh:
	echo 'test "`./esub \".\" \"\\a\" \"abcd\" 2>&1`" = "Unknown escaped character in substitution in position 2: a."' > $@
	chmod +x $@

test_not_enough_groups.sh:
	echo 'test "`./esub \"(.)(.)\" \"\\1\\2\\3\" \"abcd\" 2>&1`" = "Not enough groups in regular expression for group number 3."' > $@
	chmod +x $@

test_not_closed_escape_symbol.sh:
	echo 'test "`./esub \"(.)(.)\" \\\\\\\\ \"abcd\" 2>&1`" = "Not closed escape symbol found in the end of substitution."' > $@
	chmod +x $@

test_no_match.sh:
	echo 'test "`./esub \"(abcd)\" \\1 abcefaasdhiuhwi 2>&1`" = "`echo abcefaasdhiuhwi | sed -E '"'"'s/(abcd)/\\1/'"'"'`"' > $@
	chmod +x $@

test_ok_1.sh:
	echo 'test "`./esub \"a(.*)b(.*)c(.*)\" \"|\\1|\\2|\\3|\" \"jasdqhiuweb qwoec\" 2>&1`" = "`echo \"jasdqhiuweb qwoec\" | sed -E '"'"'s/a(.*)b(.*)c(.*)/|\\1|\\2|\\3|/'"'"'`"' > $@
	chmod +x $@

test_ok_2.sh:
	echo 'test "`./esub \"a(.*)b(.*)c(.*)\" \"|\\1|\\2|\" \"jasdqhiuweb qwoec\" 2>&1`" = "`echo \"jasdqhiuweb qwoec\" | sed -E '"'"'s/a(.*)b(.*)c(.*)/|\\1|\\2|/'"'"'`"' > $@
	chmod +x $@

test_ok_3.sh:
	echo 'test "`./esub \"([0-9]{3}).*([0-9]{4}).*([0-9]{2}).*([0-9]{2}).*([0-9]{4})\" \"\\5-\\4-\\3-\\2-\\1\" \"123.2345 + 11 ? 12.1523\" 2>&1`" = "`echo \"123.2345 + 11 ? 12.1523\" | sed -E '"'"'s/([0-9]{3}).*([0-9]{4}).*([0-9]{2}).*([0-9]{2}).*([0-9]{4})/\\5-\\4-\\3-\\2-\\1/'"'"'`"' > $@
	chmod +x $@

test_ok_4.sh:
	echo 'test "`./esub \"([0-9]{2}) \\? ([0-9]{2})\" \"\\2 * \\1\" \"123.2345 + 11 ? 12.1523\" 2>&1`" = "`echo \"123.2345 + 11 ? 12.1523\" | sed -E '"'"'s/([0-9]{2}) \\? ([0-9]{2})/\\2 * \\1/'"'"'`"' > $@
	chmod +x $@

test_ok_5.sh:
	echo 'test "`./esub \"11(.*)$\" \"\\1,\\1,\\1,\\1\" \"123.2345 + 11 ? 12.1523\" 2>&1`" = "`echo \"123.2345 + 11 ? 12.1523\" | sed -E '"'"'s/11(.*)$$/\\1,\\1,\\1,\\1/'"'"'`"' > $@
	chmod +x $@

remove_tests:
	rm -rf $(TESTS)

clean: maintainer-clean remove_tests
