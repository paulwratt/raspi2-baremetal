#include	<stdio.h>
#include	<string.h>
#include	<type.h>

enum
{
	SPRINT_TYPE_NONE,
	SPRINT_TYPE_STRING,
	SPRINT_TYPE_CHAR,
	SPRINT_TYPE_INT,
	SPRINT_TYPE_UINT,
	SPRINT_TYPE_OCT,
	SPRINT_TYPE_HEX_LOWER,
	SPRINT_TYPE_HEX_UPPER,
};

struct type
{
	int type;
	char ch;
	int len;
};

static int decode(const char *buffer, struct type *type)
{
	int i = 0;
	char ch;

	memset(type, 0, sizeof(struct type));

	ch = buffer[i++];
	if (ch != '%') {
		type->type = SPRINT_TYPE_NONE;
		type->ch = ch;
		return i;
	}

	// TODO :
	ch = buffer[i++];
	if (ch == '0') {

		ch = buffer[i++];
	} else if (ch > '1' && ch <= '9') {
		type->len = ch - '0';
		ch = buffer[i++];
	}

	switch (ch) {
		case 's':
			type->type = SPRINT_TYPE_STRING;
			break;
		case 'c':
			type->type = SPRINT_TYPE_CHAR;
			break;
		case 'd':
			type->type = SPRINT_TYPE_INT;
			break;
		case 'u':
			type->type = SPRINT_TYPE_UINT;
			break;
		case 'o':
			type->type = SPRINT_TYPE_OCT;
			break;
		case 'x':
			type->type = SPRINT_TYPE_HEX_LOWER;
			break;
		case 'X':
			type->type = SPRINT_TYPE_HEX_UPPER;
			break;
		case '%':
			type->type = SPRINT_TYPE_NONE;
			type->ch = ch;
			break;
	}

	return i;
}

static char* string(char *start, char *end, struct type *type, const char *arg)
{
	int i, len;
	const char *p = arg;

	// 文字列がNULLの場合は(NULL)と表示
	if ((uint32_t) p < 4096)
		p = "(NULL)";

	// 文字列の長さを取得
	len = strlen(p);

	// 文字列コピー
	for (i = 0;i < len;i++) {
		if (start != end) {
			*start++ = *p++;
		} else {
			break;
		}
	}

	return start;
}

static char* number(char *start, char *end, struct type *type, uint32_t arg)
{
	const static char* tex_l = "0123456789abcdef";
	const static char* tex_h = "0123456789ABCDEF";
	const char *text = tex_l;
	char temp[64] = {0};
	int len =0;

	// 数字を文字列に変換(12345 -> "54321")
	switch (type->type) {
		case SPRINT_TYPE_CHAR:
			{
				int8_t val = (int8_t) arg;
				temp[len++] = val;
			}
			break;
		case SPRINT_TYPE_INT:
			{
				int32_t val = (int32_t) arg;
				int flag = 1;

				// マイナス値の場合はフラグを設定して、プラスにする
				if (val & 0x80000000) {
					val *= -1;
					flag = -1;
				}

				while (val) {
					temp[len++] = text[val % 10];
					val /= 10;
				}

				if (flag == -1) {
					temp[len++] = '-';
				}
			}
			break;
		case SPRINT_TYPE_UINT:
			{
				uint32_t val = (uint32_t) arg;
				while (val) {
					temp[len++] = text[val % 10];
					val /= 10;
				}
			}
			break;
		case SPRINT_TYPE_OCT:
			{
				int32_t val = (int32_t) arg;
				while (val) {
					temp[len++] = text[val % 8];
					val /= 8;
				}
			}
			break;
		case SPRINT_TYPE_HEX_UPPER:
			text = tex_h;
			/* no break */
		case SPRINT_TYPE_HEX_LOWER:
			{
				uint32_t val = (uint32_t) arg;
				while (val) {
					temp[len++] = text[val % 16];
					val /= 16;
				}
			}
			break;
	}

	// 文字列をバッファにコピー
	while (len) {
		*start++ = temp[--len];
	}


	return start;
}

int vsnprintk(char *buffer, int count, const char *format, va_list va)
{
	int i;
	char *start = buffer;
	char *end = buffer + count - 1;
	struct type type;

	// 引数チェック
	if (buffer == NULL || format == NULL)
		return 0;
	if (start >= end)
		return 0;

	for (i = 0;*format;i++) {
		int len = decode(format, &type);
		format += len;

		switch (type.type) {
			case SPRINT_TYPE_NONE:
				*start++ = type.ch;
				break;
			case SPRINT_TYPE_CHAR:
				/* no break */
			case SPRINT_TYPE_INT:
				/* no break */
			case SPRINT_TYPE_UINT:
				/* no break */
			case SPRINT_TYPE_OCT:
				/* no break */
			case SPRINT_TYPE_HEX_LOWER:
				/* no break */
			case SPRINT_TYPE_HEX_UPPER:
				start = number(start, end, &type, va_arg(va, uint32_t));
				break;
			case SPRINT_TYPE_STRING:
				start = string(start, end, &type, va_arg(va, char*));
				break;
		}

		// バッファがいっぱいの時は終了する
		if (start == end)
			break;
	}

	return (start - buffer);
}

int
vsprintk(char *buffer, const char *format, va_list va)
{
	return vsnprintk(buffer, 10240, format, va);
}

int
sprintk(char *buffer, const char *format, ... )
{
	int ret;
	va_list va;

	va_start(va, format);
	ret = vsprintk(buffer, format, va);
	va_end(va);

	return ret;
}


