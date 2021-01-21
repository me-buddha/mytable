#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "mytable.pb.h"

//data mytableing
struct MyTable : public xchain::Contract {
public:
    MyTable(): _entity(this->context(), "entity") {}

    // 1. rowkey can not be same with index
    struct entity: public mytable::MyTable {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };
private:
    xchain::cdt::Table<entity> _entity;

public:
    decltype(_entity)& get_entity() {
        return _entity;
    }
};

//初始化
DEFINE_METHOD(MyTable, initialize) {
    xchain::Context* ctx = self.context();
    ctx->ok("initialize succeed");
}

DEFINE_METHOD(MyTable, count) {
    xchain::Context* ctx = self.context();
    
    auto it = self.get_entity().scan({{"id","1"}});
    int i = 0;
    std::string re ;
    while(it->next()) {
        MyTable::entity ent;
        if (!it->get(&ent))
            break;

        std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
        re += obj;
        i += 1;
    }
    // if (it->error()) 
    //     ctx->ok(std::to_string(i) + " ++> " + re + " > " + it->error(true));
    ctx->ok(std::to_string(i) + " -> " + re + " > " + it->error(true));
}

DEFINE_METHOD(MyTable, findid) {
    xchain::Context* ctx = self.context();
    const std::string& id = ctx->arg("id");
    MyTable::entity ent;
    if (self.get_entity().find({{"id", id}}, &ent)) {
        std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
        ctx->ok(obj);
        return;
    }
    ctx->error("can not find " + id);
}

DEFINE_METHOD(MyTable, findname) {
    xchain::Context* ctx = self.context();
    const std::string& name = ctx->arg("name");
    MyTable::entity ent;
    if (self.get_entity().find({{"name", name}}, &ent)) {
        std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
        ctx->ok(obj);
        return;
    }
    ctx->error("can not find " + name);
}

DEFINE_METHOD(MyTable, add) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    MyTable::entity ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_entity().put(ent);

    std::string obj ; obj += "{" +id() + "," + name + "}";
    ctx->ok(re);
}

DEFINE_METHOD(MyTable, del) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    MyTable::entity ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_entity().del(ent);

    std::string obj ; obj += "{" +id() + "," + name + "}";
    ctx->ok(obj);
}

DEFINE_METHOD(MyTable, scan) {
    xchain::Context* ctx = self.context();
    const std::string& name = ctx->arg("name");
    auto it = self.get_entity().scan({{"name", name}});
    MyTable::entity ent;
    int i = 0;
    std::string re ;
    std::map<std::string, bool> kv;
    while(it->next()) {
        if (it->get(&ent)) {
            std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
            re += obj;

            if (kv.find(ent.name()) != kv.end()) {
                ctx->error("find duplicated key");
                return;
            }
            kv[ent.name()] = true;
            i += 1;
        } else {
            std::cout << "get error" << std::endl;
        }
    }
    std::cout << i << std::endl;
    if (it->error()) {
        std::cout << it->error(true) << std::endl;
    }
    re += "}";
    ctx->ok(std::to_string(i) + " -> " + re);
}



DEFINE_METHOD(MyTable, clear) {
    xchain::Context* ctx = self.context();
    auto it = self.get_entity().scan({});
    int i = 0;
    while(it->next()) {
        MyTable::entity ent;
        if (it->get(&ent)) {
            self.get_entity().del(ent);
            i += 1;
        } else {
            std::cout << "get error" << std::endl;
        }
    }
    std::cout << i << std::endl;
    if (it->error()) {
        std::cout << it->error(true) << std::endl;
    }
    ctx->ok(std::to_string(i));
}
