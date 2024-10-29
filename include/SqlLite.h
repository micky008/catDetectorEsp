#ifndef __MYSQLLITE__H__
#define __MYSQLLITE__H__

#include <SPI.h>
#include <sqlite3.h>
#include <vfs.h>

#include "interfaces/Initialisation.h"

class Sql : public Initialisation {
   public:
    void init();


   private:
    sqlite3 *dbLink;
    void createTable();
};

#endif