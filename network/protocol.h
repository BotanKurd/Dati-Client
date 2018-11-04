//
// Created by Botan on 27/10/18.
//

#ifndef DATI_PROTOCOL_H
#define DATI_PROTOCOL_H

#include "client.h"
#include "query.h"


/** @Message_id : 0 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0)
**/
unsigned char login(struct client *client);


/*** DATABASES **/

/** @Message_id : 1 **
 *  @Response : *char[] : list of databases
**/
container get_databases(struct client client);

/** @Message_id : 2 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char create_database(struct client client, char *name);

/** @Message_id : 3 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char remove_database(struct client client, char *name);

/** @Message_id : 4 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char rename_database(struct client client, char *database, char *new_name);


/*** TABLES ***/
/** @Message_id : 5 **
 *  @Response : *char[] : list of tables of specified database
**/
container get_tables(struct client client, char *database);

/** @Message_id : 6 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char create_table(struct client client, char *database, char *name);

/** @Message_id : 7 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char remove_table(struct client client, char *database, char *name);

/** @Message_id : 8 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char rename_table(struct client client, char *database, char *last_name, char *new_name);


/*** QUERY ***/

/** @Message_id : 9 **
 *  @_uuid : unique id of inserted statement
*  @Response : insert_result { @_uuid, @error_code }
**/
insert_result insert(struct client client, char *database, char *table, insert_query);

#endif //DATI_PROTOCOL_H
