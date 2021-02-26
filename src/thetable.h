#ifndef _THE_TABLE_
#define _THE_TABLE_

#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "mytable.pb.h"

class thetable: public mytable::MyTable {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(0)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, name)
    DEFINE_INDEX_END();

    std::string to_string() ;

};

#endif //_THE_TABLE_