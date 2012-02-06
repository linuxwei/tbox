/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * \author		ruki
 * \file		aiop.h
 *
 */
#ifndef TB_AIO_REACTOR_AIOP_H
#define TB_AIO_REACTOR_AIOP_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

tb_aiop_reactor_t* tb_aiop_reactor_file_init(tb_aiop_t* aiop);
tb_aiop_reactor_t* tb_aiop_reactor_sock_init(tb_aiop_t* aiop);
tb_aiop_reactor_t* tb_aiop_reactor_http_init(tb_aiop_t* aiop);
tb_aiop_reactor_t* tb_aiop_reactor_gstm_init(tb_aiop_t* aiop);

#endif
