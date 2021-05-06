#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "mytable.pb.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 


class mytable: public MyTable {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, name)
    DEFINE_INDEX_END();

public:
    xchain::json to_json() {
        xchain::json j = {
            {"id", id()},
            {"name", name()},
        };

        return j;
    }
};
    
class Main : public xchain::Contract {
public:
    Main(): _entity(this->context(), "mytable") {}

private:
    xchain::cdt::Table<mytable> _entity;

public:
    decltype(_entity)& get_entity() {
        return _entity;
    }

};

//初始化
DEFINE_METHOD(Main, initialize) {
    xchain::Context* ctx = self.context();
    ctx->ok("initialize succeed");
}

DEFINE_METHOD(Main, set) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    mytable ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name);
    self.get_entity().put(ent);

    ctx->ok(ent.to_json().dump());
}

DEFINE_METHOD(Main, get) {
    xchain::Context* ctx = self.context();
    const std::string& id = ctx->arg("id");
    mytable ent;
    if (self.get_entity().find({{"id", id}}, &ent)) {
        ctx->ok(ent.to_json().dump());
        return;
    }
    ctx->error("can not find " + id);
}
