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
        DEFINE_ROWKEY(name);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id, name)
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

DEFINE_METHOD(MyTable, get) {
    xchain::Context* ctx = self.context();
    const std::string& name = ctx->arg("name");
    MyTable::entity ent;
    if (self.get_entity().find({{"name", name}}, &ent)) {
        ctx->ok(ent.to_str());
        return;
    }
    ctx->error("can not find " + name);
}

DEFINE_METHOD(MyTable, set) {
    xchain::Context* ctx = self.context();
    const std::string mytableStr= ctx->arg("mytable");
    if (mytableStr.size() == 0) {
        ctx->error("missing blockHeader");
        return;
    }

    std::unique_ptr<MyTable::entity> ent(new MyTable::entity);
    bool succ = ent->ParseFromString(mytableStr);
    if (!succ) {
        ctx->error("parse from string error");
        return;
    }

    self.get_entity().put(*ent);

    ctx->ok("save ok");
}

DEFINE_METHOD(MyTable, del) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    MyTable::entity ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_entity().del(ent);

    std::string re = "{";
    re += id + ",";
    re += name + "} del success";
    ctx->ok(re);
}

DEFINE_METHOD(MyTable, scan) {
    xchain::Context* ctx = self.context();
    const std::string& name = ctx->arg("name");
    const std::string& id = ctx->arg("id");
    auto it = self.get_entity().scan({{"id", id},{"name", name}});
    MyTable::entity ent;
    int i = 0;
    std::string re = "{";
    std::map<std::string, bool> kv;
    while(it->next()) {
        if (it->get(&ent)) {
            std::string obj = "{";
            obj += std::to_string(ent.id()) + ",";
            obj += ent.name() + "}";
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

DEFINE_METHOD(MyTable, size) {
    xchain::Context* ctx = self.context();
    auto it = self.get_entity().scan({});
    int i = 0;
    std::string re = "{";
    while(it->next()) {
        MyTable::entity ent;
        if (it->get(&ent)) {
            std::string obj = "{";
            obj += std::to_string(ent.id()) + ",";
            obj += ent.name() + "}";
            re += obj;
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
