#include <check.h>
#include "../src/crc.h"

START_TEST(test_crc16)
{
	char *in_string = "123456789";

	crc c;
	int i;

	c.c = 0;
	for (i = 0; i < strlen(in_string; i++)
		c = update_crc(c, in_string[i]);

	ck_assert(c.bytes.byte1 == 0xBB);
	ck_assert(c.bytes.byte2 == 0x3D);
}
END_TEST

Suite * crc_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("crc");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_crc16);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = crc_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}