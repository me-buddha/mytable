CXXFLAGS ?= -std=c++11 -Os -I/usr/local/include -Isrc -Werror=vla -I/root/xuperchain/core/contractsdk/cpp/src
LDFLAGS ?= -Oz -s TOTAL_STACK=256KB -s TOTAL_MEMORY=1MB -s DETERMINISTIC=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["stackAlloc"] -L/usr/local/lib -lprotobuf-lite -lpthread --js-library /root/xuperchain/core/contractsdk/cpp/src/xchain/exports.js

.PHONY: all build clean

all: build

clean: 
	$(RM) -r build

/root/.xdev-cache/22/22f4cdb9dd94f40d.o: /root/mytable/src/mytable.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/e1/e18aab093f366daf.o: /root/mytable/src/mytable.pb.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/54/5483f1dd2ea0f0ea.o: /root/mytable/src/thetable.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/f7/f7a346506baf3c18.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/account.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/a4/a40f048dee03eaf8.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/basic_iterator.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/9c/9cfcfca62a9662f6.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/block.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/ec/ecbb5cc223f25341.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/context_impl.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/83/832fb0a0f7ba0e99.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/contract.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/58/586638b75bfd932b.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/contract.pb.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/f2/f2a8cc87f3c8b6d4.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/crypto.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/e6/e680c780ff7430ae.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/syscall.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/.xdev-cache/41/41ad0191c39ce959.o: /root/xuperchain/core/contractsdk/cpp/src/xchain/transaction.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

/root/mytable/mytable.wasm: /root/.xdev-cache/22/22f4cdb9dd94f40d.o /root/.xdev-cache/e1/e18aab093f366daf.o /root/.xdev-cache/54/5483f1dd2ea0f0ea.o /root/.xdev-cache/f7/f7a346506baf3c18.o /root/.xdev-cache/a4/a40f048dee03eaf8.o /root/.xdev-cache/9c/9cfcfca62a9662f6.o /root/.xdev-cache/ec/ecbb5cc223f25341.o /root/.xdev-cache/83/832fb0a0f7ba0e99.o /root/.xdev-cache/58/586638b75bfd932b.o /root/.xdev-cache/f2/f2a8cc87f3c8b6d4.o /root/.xdev-cache/e6/e680c780ff7430ae.o /root/.xdev-cache/41/41ad0191c39ce959.o
	@echo LD wasm
	@$(CXX) -o $@ $^ $(LDFLAGS)

build: /root/mytable/mytable.wasm


-include /root/.xdev-cache/22/22f4cdb9dd94f40d.d /root/.xdev-cache/e1/e18aab093f366daf.d /root/.xdev-cache/54/5483f1dd2ea0f0ea.d /root/.xdev-cache/f7/f7a346506baf3c18.d /root/.xdev-cache/a4/a40f048dee03eaf8.d /root/.xdev-cache/9c/9cfcfca62a9662f6.d /root/.xdev-cache/ec/ecbb5cc223f25341.d /root/.xdev-cache/83/832fb0a0f7ba0e99.d /root/.xdev-cache/58/586638b75bfd932b.d /root/.xdev-cache/f2/f2a8cc87f3c8b6d4.d /root/.xdev-cache/e6/e680c780ff7430ae.d /root/.xdev-cache/41/41ad0191c39ce959.d
