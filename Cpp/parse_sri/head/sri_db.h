
#ifndef _SRI_DB_H_
#define _SRI_DB_H_

#include <string>
#include <sqlite3.h>

#include "sri_handler.h"

void create_db(string &db_file_name);
void close_db(void);
void write_sri_to_db(sri_t& sri_desc);


extern sqlite3 *sri_db;

#endif //_SRI_DB_H_ 
