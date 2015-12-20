#include <stdio.h>
//#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// GNUのstdio.hが読み込めないので・・・
extern int printf(const char *format, ...);

// テスト対象ファイル
#include "../lib/vsprintk.c"

static char buffer[256];

/**
 *
 */
static int test1(void)
{
	int len, ret;
	const static char *TEST_DATA = "abcdefghijklmn";
	const static char *ANS_DATA  = "abcdefghijklmn";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 可変引数なし
	len = sprintk(buffer, TEST_DATA);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test2(void)
{
	int len, ret;
	const static char *TEST_DATA = "abcdefghijklmn";
	const static char *ANS_DATA  = "-abcdefghijklmn-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-%s-", TEST_DATA);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test3(void)
{
	int len, ret;
	const static char *TEST_DATA = "100";
	const static char *ANS_DATA = "--100-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-%d-", -100);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		printf("%s", buffer);
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test4(void)
{
	int len, ret;
	const static char *TEST_DATA = "0xC10F";
	const static char *ANS_DATA = "-0xC10F-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-0x%X-", 0xC10F);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test5(void)
{
	int len, ret;
	const static char *TEST_DATA = "0xc10f";
	const static char *ANS_DATA = "-0xc10f-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-0x%x-", 0xC10F);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test6(void)
{
	int len, ret;
	const static char *TEST_DATA = "1234567989%";
	const static char *ANS_DATA = "-123456789%-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-123456789%%-");

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test7(void)
{
	int len, ret;
	const static char *TEST_DATA = "ab$";
	const static char *ANS_DATA = "-ab$-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-%c%c%c-", 'a', 'b', '$');

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
static int test8(void)
{
	int len, ret;
	const static char *TEST_DATA = "ab$";
	const static char *ANS_DATA = "-01234567-";

	printf("  %s - ", __FUNCTION__);

	// 初期化
	memset(buffer, 0, sizeof(buffer));

	// 文字列引数
	len = sprintk(buffer, "-0%o-", 01234567);

	// 結果判定
	if (strcmp(buffer, ANS_DATA) == 0 && len == strlen(ANS_DATA)) {
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

/**
 *
 */
struct TEST_CASE
{
	int (*test)(void);
} test [] =
{
		test1,
		test2,
		test3,
		test4,
		test5,
		test6,
		test7,
		test8,
		NULL,
};

/**
 *
 */
void test_vprintk_main(void)
{
	struct TEST_CASE *p = test;
	int count = 0, ok = 0, ret;

	printf("uint8_t  : %d\n", sizeof(uint8_t));
	printf("uint16_t : %d\n", sizeof(uint16_t));
	printf("uint32_t : %d\n", sizeof(uint32_t));

	printf("int       : %d\n", sizeof(int));
	printf("long      : %d\n", sizeof(long));
	printf("long int  : %d\n", sizeof(long int));
	printf("long long : %d\n", sizeof(long long));


	printf("vprintk\n");

	while (p->test) {
		count++;
		ret = p->test();
		if (ret == 0) {
			printf("OK\n", __FUNCTION__);
			ok++;
		} else {
			printf("NG\n", __FUNCTION__);
		}
		p++;
	}

	// 結果表示
	printf("TestCount : %d, OK : %d, NG : %d\n", count, ok, count - ok);
}


