/*
** Zabbix
** Copyright (C) 2001-2016 Zabbix SIA
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#include "common.h"
#include "sysinc.h"
#include "module.h"
#include "log.h"

/* 1 = clean out filename's symbol table after each request,
0 = don't
*/
#ifndef DO_CLEAN
#define DO_CLEAN 0
#endif

#include <EXTERN.h>               /* from the Perl distribution     */
#include <perl.h>                 /* from the Perl distribution     */

static PerlInterpreter *my_perl;  /***    The Perl interpreter    ***/

/* the variable keeps timeout setting for item processing */
static int	item_timeout = 0;

int	zbx_module_perl_run(AGENT_REQUEST *request, AGENT_RESULT *result);

static ZBX_METRIC keys[] =
/*      KEY                     FLAG		FUNCTION        	TEST PARAMETERS */
{
	{"perl.run",		CF_HAVEPARAMS,	zbx_module_perl_run, 	"/script.pl"},
	{NULL}
};

/******************************************************************************
 *                                                                            *
 * Function: zbx_module_api_version                                           *
 *                                                                            *
 * Purpose: returns version number of the module interface                    *
 *                                                                            *
 * Return value: ZBX_MODULE_API_VERSION_ONE - the only version supported by   *
 *               Zabbix currently                                             *
 *                                                                            *
 ******************************************************************************/
int	zbx_module_api_version()
{
	return ZBX_MODULE_API_VERSION_ONE;
}

/******************************************************************************
 *                                                                            *
 * Function: zbx_module_item_timeout                                          *
 *                                                                            *
 * Purpose: set timeout value for processing of items                         *
 *                                                                            *
 * Parameters: timeout - timeout in seconds, 0 - no timeout set               *
 *                                                                            *
 ******************************************************************************/
void	zbx_module_item_timeout(int timeout)
{
	item_timeout = timeout;
}

/******************************************************************************
 *                                                                            *
 * Function: zbx_module_item_list                                             *
 *                                                                            *
 * Purpose: returns list of item keys supported by the module                 *
 *                                                                            *
 * Return value: list of item keys                                            *
 *                                                                            *
 ******************************************************************************/
ZBX_METRIC	*zbx_module_item_list()
{
	return keys;
}

int	zbx_module_perl_run(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	char	*param;

	if (1 != request->nparam)
	{
		/* set optional error message */
		SET_MSG_RESULT(result, strdup("Invalid number of parameters."));
		return SYSINFO_RET_FAIL;
	}

	param = get_rparam(request, 0);

    //char *embedding[] = { "", "persistent.pl" };
    //char *args[] = { "", DO_CLEAN, NULL };

	//char *paramm = "print 'dddd'";
	//zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, request->nparam, &paramm, (char **)NULL));
	//call_argv("showtime", G_DISCARD | G_NOARGS, args);
    //zabbix_log(LOG_LEVEL_DEBUG, "perl_parse(%d, %s)", request->nparam, paramm);
    //zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, request->nparam, &paramm, (char **)NULL));
/*
# test perl script
cat /echo.pl
use strict;
use warnings;
print 'test perl output';
*/
/*
    printf("Concept 1: parse and run - how to catch output?");
    char *private_argv[] = { "", "/echo.pl"};
    zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, 2, private_argv, NULL));
    zabbix_log(LOG_LEVEL_DEBUG, "perl_run: %d", perl_run(my_perl));
    SET_STR_RESULT(result, zbx_strdup(NULL, "testok"));
    return SYSINFO_RET_OK;
*/
/*
 21652:20160409:013708.316 Requested [perl.run[/echo.pl]]
 21652:20160409:013708.322 perl_parse: 0
 21652:20160409:013708.322 perl_run: 0
 21652:20160409:013708.322 Sending back [testok]
*/

    //printf("Concept 2: parse and run - customized stdout/stderr");
    //zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, 333, private_argv, NULL));
    //zabbix_log(LOG_LEVEL_DEBUG, "perl_run: %d", perl_run(my_perl));
    //zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, 2, embedding, NULL));
    ///zabbix_log(LOG_LEVEL_DEBUG, "perl_eval: %d", perl_eval_pv(&paramm, 0));
    //args[0] = "/echo.pl";
    //call_argv("Embed::Persistent::eval_file", G_DISCARD | G_EVAL, args);
    //zabbix_log(LOG_LEVEL_ERR, "stderr restore");
    //dup2(serr,fileno(stderr));
    //zabbix_log(LOG_LEVEL_ERR, "stdout restore");
    //dup2(sout,fileno(stdout));

/*
# test perl script 222222
cat /echosub.pl
use strict;
use warnings;
print "I shan't be printed.";
sub subroutine {
    333 + 111;
}
*/
    printf("Concept 3: parse and call_argv (subroutine)");
    char *private_argv[] = { "", "/echosub.pl"};
    zabbix_log(LOG_LEVEL_DEBUG, "perl_parse: %d", perl_parse(my_perl, NULL, 2, private_argv, NULL));
    dSP;
    PUSHMARK(SP);
    int count;
    count = call_pv("subroutine", G_SCALAR | G_NOARGS);
    zabbix_log(LOG_LEVEL_DEBUG, "count: %d", count);
    SPAGAIN;
    count = POPi;
    zabbix_log(LOG_LEVEL_DEBUG, "Output from subroutine: %d", count);
    SET_DBL_RESULT(result, count);
    PUTBACK;
    FREETMPS;
    LEAVE;
    //zabbix_log(LOG_LEVEL_DEBUG, "call_argv: %d", call_argv("subroutine", G_DISCARD | G_NOARGS, private_argv));
    // zabbix_log(LOG_LEVEL_DEBUG, "call_pv: %d", call_pv("subroutine", G_SCALAR | G_NOARGS));
    return SYSINFO_RET_OK;

	return SYSINFO_RET_OK;
}


/******************************************************************************
 *                                                                            *
 * Function: zbx_module_init                                                  *
 *                                                                            *
 * Purpose: the function is called on agent startup                           *
 *          It should be used to call any initialization routines             *
 *                                                                            *
 * Return value: ZBX_MODULE_OK - success                                      *
 *               ZBX_MODULE_FAIL - module initialization failed               *
 *                                                                            *
 * Comment: the module won't be loaded in case of ZBX_MODULE_FAIL             *
 *                                                                            *
 ******************************************************************************/
int     zbx_module_init()
{
        zabbix_log(LOG_LEVEL_ERR, "zbx_module_init()");

    int sout = dup(fileno(stdout));
    int serr = dup(fileno(stderr));

    int out, errr;
    out = open("/tmp/out.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    dup2(out, 1);
    close(out);
    // stderr -> stdout
    dup2(fileno(stdout), fileno(stderr));
    errr = open("/tmp/err.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    dup2(errr, 2);
    close(errr);


    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

        int *first = 0;
        char ***second = NULL;
        char ***third = NULL;
        PERL_SYS_INIT3(first, second, third);
        my_perl = perl_alloc();
        perl_construct(my_perl);
        PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
        return ZBX_MODULE_OK;
}

/******************************************************************************
 *                                                                            *
 * Function: zbx_module_uninit                                                *
 *                                                                            *
 * Purpose: the function is called on agent shutdown                          *
 *          It should be used to cleanup used resources if there are any      *
 *                                                                            *
 * Return value: ZBX_MODULE_OK - success                                      *
 *               ZBX_MODULE_FAIL - function failed                            *
 *                                                                            *
 ******************************************************************************/
int     zbx_module_uninit()
{
        perl_destruct(my_perl);
        perl_free(my_perl);
        PERL_SYS_TERM();
        return ZBX_MODULE_OK;
}


