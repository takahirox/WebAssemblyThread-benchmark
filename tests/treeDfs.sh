emcc treeDfs.cpp \
  -O2 \
  -g \
  -s ASSERTIONS=1 \
  -s DEMANGLE_SUPPORT=1 \
  -s WASM=1 \
  -s TOTAL_MEMORY=128MB \
  -s EXPORTED_FUNCTIONS="[ \
    '_traverse', \
    '_traverseThread', \
    '_sizeofNode', \
    '_NodeInit', \
    '_NodeDelete', \
    '_NodeAdd']" \
  -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" \
  -o treeDfs.js \
  -s USE_PTHREADS=1 \
  -s PTHREAD_POOL_SIZE=2
