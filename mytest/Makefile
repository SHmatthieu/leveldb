test: test.cc leveldb/*
	$(WASI_SDK_PATH)/bin/clang++ test.cc -I . ../build/libleveldb.a -Wl,--allow-undefined,--no-check-features -lwasi-emulated-mman -pthread -O3 -Wl,--shared-memory,--max-memory=4294967296 -Wl,--allow-undefined,--no-check-features -Wl,--export=__heap_base,--export=__data_end

write: writeTest.cc leveldb/*
	$(WASI_SDK_PATH)/bin/clang++ writeTest.cc -I . ../build/libleveldb.a -Wl,--allow-undefined,--no-check-features -lwasi-emulated-mman -pthread -O3 -Wl,--shared-memory,--max-memory=4294967296 -Wl,--allow-undefined,--no-check-features -Wl,--export=__heap_base,--export=__data_end

read: readTest.cc leveldb/*
	$(WASI_SDK_PATH)/bin/clang++ readTest.cc -I . ../build/libleveldb.a -Wl,--allow-undefined,--no-check-features -lwasi-emulated-mman -pthread -O3 -Wl,--shared-memory,--max-memory=4294967296 -Wl,--allow-undefined,--no-check-features -Wl,--export=__heap_base,--export=__data_end

bench: bench.cc leveldb/*
	$(WASI_SDK_PATH)/bin/clang++ bench.cc -I . ../build/libleveldb.a -Wl,--allow-undefined,--no-check-features -lwasi-emulated-mman -pthread -O3 -Wl,--shared-memory,--max-memory=4294967296 -Wl,--allow-undefined,--no-check-features -Wl,--export=__heap_base,--export=__data_end
