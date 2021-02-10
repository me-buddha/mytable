#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "mytable.pb.h"
#include <iostream>

using namespace std;

//data mytableing
struct MyTable : public xchain::Contract {
public:
    MyTable(): _entity(this->context(), "entity") {}

    // 1. rowkey can not be same with index
    struct entity: public mytable::MyTable {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(0)
            DEFINE_INDEX_ADD(0, id)
            DEFINE_INDEX_ADD(1, name)
        DEFINE_INDEX_END();


        std::string to_string() {
            std::string str ;
            str += "{" ;
            str += std::to_string(id()) + ",";
            str += name();
            str += "}";
            return str;
        }
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

        re += ent.to_string();
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

    cout << __func__ << "[" << __LINE__ << "] " << "id=" << id << endl;

    MyTable::entity ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_entity().put(ent);

    ctx->ok(ent.to_string());
}

DEFINE_METHOD(MyTable, del) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    MyTable::entity ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_entity().del(ent);

    ctx->ok(ent.to_string());
}

// DEFINE_METHOD(MyTable, scan) {
//     xchain::Context* ctx = self.context();
//     const std::string& name = ctx->arg("name");
//     auto it = self.get_entity().scan({{"name", name}});
//     MyTable::entity ent;
//     int i = 0;
//     std::string re ;
//     std::map<std::string, bool> kv;
//     while(it->next()) {
//         if (it->get(&ent)) {
//             std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
//             re += obj;

//             if (kv.find(ent.name()) != kv.end()) {
//                 ctx->error("find duplicated key");
//                 return;
//             }
//             kv[ent.name()] = true;
//             i += 1;
//         } else {
//             std::cout << "get error" << std::endl;
//         }
//     }
//     std::cout << i << std::endl;
//     if (it->error()) {
//         std::cout << it->error(true) << std::endl;
//     }
//     re += "}";
//     ctx->ok(std::to_string(i) + " -> " + re);
// }



DEFINE_METHOD(MyTable, scan) {
    xchain::Context* ctx = self.context();
    // auto it = self.get_entity().scan({});
    // auto it = self.get_entity().scan({{"id", "1"}});
    // int i = 0;
    // while(it->next()) 
    //     i++;
    // ctx->ok(std::to_string(i));

    auto it = self.get_entity().scan({{"name", ctx->arg("name").c_str()}});
    int i = 0;
    // std::string ret;
    while(it->next()) {
        MyTable::entity ent;
        if (it->get(&ent)) {
            std::cout << __LINE__ << " run" << std::endl;
            i++;
            // ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    // ctx->ok(std::to_string(i) + ret);
    ctx->ok(std::to_string(i));
}

