/* ///////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox.h"

/* ///////////////////////////////////////////////////////////////////
 * macros
 */

/* ///////////////////////////////////////////////////////////////////
 * callback
 */
static tb_bool_t tb_http_test_hfunc(tb_http_option_t* option, tb_char_t const* line)
{
	tb_printf("head: %s\n", line);
	return TB_TRUE;
}

/* ///////////////////////////////////////////////////////////////////
 * main
 */
int main(int argc, char** argv)
{
	if (!tb_init(malloc(1024 * 1024), 1024 * 1024)) return 0;

	// init http
	tb_handle_t http = tb_http_init();
	tb_assert_and_check_goto(http, end);

	// option
	tb_http_option_t* option = tb_http_option(http);
	tb_assert_and_check_goto(option, end);

	// status
	tb_http_status_t const* status = tb_http_status(http);
	tb_assert_and_check_goto(status, end);

	// init cookies
	option->cookies = tb_cookies_init();
	tb_assert_and_check_goto(option->cookies, end);
	
	// init url
//	tb_pstring_cstrcpy(&option->host, "119.75.217.56");
//	tb_pstring_cstrcpy(&option->path, "/index.html");

	// init head func
	option->hfunc = tb_http_test_hfunc;
	option->udata = http;

	// open http
	if (!tb_http_bopen(http)) goto end;

	// read data
	tb_byte_t 		data[8192];
	tb_size_t 		read = 0;
	tb_bool_t 		wait = TB_FALSE;
	tb_uint64_t 	size = status->content_size;
	do
	{
		// read data
		tb_long_t n = tb_http_aread(http, data, 8192);
		if (n > 0)
		{
			// update read
			read += n;

			// no waiting
			wait = TB_FALSE;
		}
		else if (!n) 
		{
			// no end?
			tb_check_break(!wait);

			// wait
			tb_long_t e = tb_http_wait(http, TB_AIOO_ETYPE_READ, option->timeout);
			tb_assert_and_check_break(e >= 0);

			// timeout?
			tb_check_break(e);

			// has read?
			tb_assert_and_check_break(e & TB_AIOO_ETYPE_READ);

			// be waiting
			wait = TB_TRUE;
		}
		else break;

		// is end?
		if (size && read >= size) break;

	} while(1);

end:

	// exit cookies
	if (option && option->cookies) 
	{
		// dump cookies
#ifdef TB_DEBUG
		tb_cookies_dump(option->cookies);
#endif

		tb_cookies_exit(option->cookies);
	}

	// exit http
	if (http) tb_http_exit(http);

	// exit tbox
	tb_exit();

	return 0;
}
