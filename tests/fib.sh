emcc fib.c \
  -O2 \
  -s WASM=1 \
  -s EXPORTED_FUNCTIONS="['_fib', '_fibThread']" \
  -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" \
  -o fib.js \
  -s USE_PTHREADS=1 \
  -s PTHREAD_POOL_SIZE=2
