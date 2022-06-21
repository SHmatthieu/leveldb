test: testLevel.cc leveldb/*
	$(WASI_SDK_PATH)/bin/clang++ testLevel.cc -I . ../build/libleveldb.a -Wl,--allow-undefined,--no-check-features
