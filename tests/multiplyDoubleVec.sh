emcc multiplyDoubleVec.c \
  -O2 \
  -s WASM=1 \
  -s TOTAL_MEMORY=1024MB \
  -s EXPORTED_FUNCTIONS="['_multiplyDoubleVec', '_multiplyDoubleVecThread']" \
  -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" \
  -o multiplyDoubleVec.js \
  -s USE_PTHREADS=1 \
  -s PTHREAD_POOL_SIZE=2
